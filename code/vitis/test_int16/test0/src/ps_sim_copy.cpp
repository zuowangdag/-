//
// Created by admin on 2022/11/11.
//
#include "ps.h"
// #include "acc_quan.h"
// #include "acc_quan.h"
#include "utils.h"
#include <bits/stdint-uintn.h>
#include <cmath>
#include "yo_struct.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <stdint.h>
#include "xtop.h"
#include "sys/mman.h"
#include "sys/time.h"

#define TN 4
#define TM 32
#define OTH 40
#define OTW 40
#define ITH 81
#define ITW 81
#define MIN(x,y) (x < y) ? (x) : (y)
#define MAX(x,y) (x > y) ? (x) : (y)
#define ONCHIP_Q 20
typedef short quan_t;
#define IP_CONTROL_BASE_ADDRESS 0x40000000
#define WEIGHTS_BASE 0x20000000
#define BIAS_BASE 0x20dd8000// 0x21BAF000
#define MEM_BASE 0x20dde000 // 0x21BBA000
#define IFM_PAD_LENGTH 640
const uint8_t POOL_MIN_MN = MIN(TN,TN);


double what_time_is_it_now() {
  struct timeval time;
  if(gettimeofday(&time,NULL)){
    return 0;
  }
  return (double)time.tv_sec + (double)time.tv_usec * 0.000001;
}

void copy_mem2dev(uint8_t *orig,uint32_t byte_num, unsigned long in_buffer)
{
	int fd = open("/dev/mem", O_RDWR);
	unsigned char *virtual_addr;
	uint32_t RequestByteNum;// must page
	if(byte_num%(4*1024)==0)
		RequestByteNum = byte_num;
	else
	{
		RequestByteNum = (byte_num/(4*1024)+1)*(4*1024);
	}
	virtual_addr = (unsigned char *)mmap(NULL, RequestByteNum, PROT_READ | PROT_WRITE, MAP_SHARED, fd, (off_t)in_buffer);
	if(virtual_addr == MAP_FAILED)
	{
		perror("Virtual_addr_in mappong for absolute memory access failed!\n");
		return;
	}
	memcpy(virtual_addr,orig,byte_num);

	munmap((void *)virtual_addr, byte_num);
	close(fd);
}

void copy_dev2mem(uint8_t *dst,uint32_t byte_num, unsigned long in_buffer)
{
	int fd = open("/dev/mem", O_RDWR);
	unsigned char *virtual_addr;
	uint32_t RequestByteNum;// must page
	if(byte_num%(4*1024)==0)
		RequestByteNum = byte_num;
	else
	{
		RequestByteNum = (byte_num/(4*1024)+1)*(4*1024);
	}
		virtual_addr = (unsigned char *)mmap(NULL, RequestByteNum, PROT_READ | PROT_WRITE, MAP_SHARED, fd, (off_t)in_buffer);
	if(virtual_addr == MAP_FAILED)
	{
		perror("Virtual_addr_in mappong for absolute memory access failed!\n");
		return;
	}
	memcpy((uint8_t *)dst,virtual_addr,byte_num);

	munmap((void *)virtual_addr, byte_num);
	close(fd);
}

int copy_file2mem(char *bin_file,uint32_t byte_num,unsigned long in_buffer)
{
	unsigned char *buffer = (unsigned char *)malloc(1024*1024);
	if(buffer==NULL){
		printf("cannot malloc buffer 1024*1024 byte\n");
		return -1;
	}

	FILE *fp;
	if( (fp = fopen(bin_file, "rb")) == NULL)fprintf(stderr,"CANNOT OPEN bin_file\n");
	int rd_num;
	unsigned long offset = 0;
	while(rd_num = fread(buffer, sizeof(unsigned char), 1024*1024, fp))
	{
		copy_mem2dev(buffer,rd_num, in_buffer+offset);
//		printf("rd_num=%d\n",rd_num);
		offset += rd_num;
	}
	printf("copy_file2mem offset=%d\n",offset);
	fclose(fp);

	free(buffer);


	return 0;
}

int copy_mem2file(char *bin_file,uint32_t byte_num,unsigned long in_buffer)
{
	void *buffer = malloc(1024*1024);
	if(buffer==NULL){
		printf("cannot malloc buffer 1024*1024 byte\n");
		return -1;
	}

	FILE *fp;
	if( (fp = fopen(bin_file, "wb")) == NULL)fprintf(stderr,"CANNOT OPEN bin_file\n");

	int x = byte_num;
	int addbyte;
	unsigned long offset = 0;
	while(addbyte=((x<1024*1024)?x:(1024*1024)))
	{
		copy_dev2mem((uint8_t *)buffer,addbyte, in_buffer+offset);
		fwrite(buffer , sizeof(unsigned char), addbyte, fp);
		x -= addbyte;
		offset += addbyte;
	}
	printf("copy_mem2file offset=%d\n",offset);

	fclose(fp);
	free(buffer);

	return 0;
}


void get_quan_data_with_q(float *data_in, quan_t *data_out, int data_num,
                          uint8_t q_value) {
  // quan_t *temp_data = (quan_t*)malloc(sizeof(quan_t) * data_num);
  for (int i = 0; i < data_num; i++) {
    data_out[i] = (quan_t)(data_in[i] * pow(2, q_value));
    // data_out[i] = (float)(temp_data[i] * powf(2, -q_value));
  }
  // free(temp_data);
}
void get_q1_q2_for_ifm_conv(int index, uint8_t* ofm_q_list, uint8_t& q1, uint8_t& q2) {
    const uint8_t cv1_in_c3[] = {4, 13,28, 51};
    const uint8_t cv3_in_c31[] = {9,  56, 67, 78, 88, 98};
    const uint8_t cv3_in_c33[] = {24, 39};
    const uint8_t cv_after_concat[] = {60, 62, 71, 73, 81, 83, 91, 93}; // {59, 70, 80, 90}
    const uint8_t cv_before_yolo[] = {100, 103, 106};

    if (check_list(index, cv1_in_c3)) {
        q1 = q2 = ofm_q_list[index-3];
    } else if(check_list(index, cv3_in_c31)) {
        q1 = ofm_q_list[index-1];
        q2 = ofm_q_list[index-7];
    } else if(check_list(index, cv3_in_c33)) {
        q1 = ofm_q_list[index-1];
        q2 = ofm_q_list[index-13];
    } else if(check_list(index, cv_after_concat)) {
        if(index==60) {q1=ofm_q_list[58];q2=ofm_q_list[39];}
        else if(index==62) {q1=ofm_q_list[58];q2=ofm_q_list[39];}
        else if(index==71) {q1=ofm_q_list[69];q2=ofm_q_list[24];}
        else if(index==73) {q1=ofm_q_list[69];q2=ofm_q_list[24];}
        else if(index==81) {q1=ofm_q_list[79];q2=ofm_q_list[68];}
        else if(index==83) {q1=ofm_q_list[79];q2=ofm_q_list[68];}
        else if(index==91) {q1=ofm_q_list[89];q2=ofm_q_list[57];}
        else if(index==93) {q1=ofm_q_list[89];q2=ofm_q_list[57];}
    } else if(check_list(index, cv_before_yolo)) {
        if(index==100) {q1=q2=ofm_q_list[78];}
        else if(index==103) {q1=q2=ofm_q_list[88];}
        else if(index==105) {q1=q2=ofm_q_list[98];}
    } else {
        q1=q2=ofm_q_list[index-1];
    }

}
void get_q1_q2_for_ifm_shortcut(int index, uint8_t *ofm_q_list, uint8_t &q1,
                                uint8_t &q2) {
  const uint8_t shortcut_in_c3[] = {7,  16, 19, 22, 31, 34,
                                    37, 54, 65, 76, 86, 96};

  if (check_list(index, shortcut_in_c3)) {
    q1 = ofm_q_list[index - 1];
    q2 = ofm_q_list[index - 3];
  }
}
void top(u32 ifm, u32 ofm, u32 weights, u32 bias, u16 ifm_ch, u16 ifm_h, u16 ifm_w,
         u16 ofm_ch, u16 ofm_h, u16 ofm_w, u8 I_CH, u8 I_H, u8 I_W, u8 O_CH, u8 O_H,
         u8 O_W, u8 k, u8 s, u8 p, u8 layertpe, bool act_silu, int CNT, u8 ifm_q1,
         u8 ifm_q2, u8 weights_q, u8 bias_q, u8 ofm_before_act_q, u8 ofm_after_act_q)
{
  XTop tp;
  if (XST_SUCCESS != XTop_Initialize(&tp, "top"))
  {
    fprintf(stderr, "IP coore init failed!\n");
  }
  while (1)
  {
    if (XTop_IsIdle(&tp))
    {
      break;
    }
  }
  XTop_Set_ifm_offset(&tp, ifm);
  XTop_Set_ofm_offset(&tp, ofm);
  XTop_Set_weights_offset(&tp, weights);
  XTop_Set_bias_offset(&tp, bias);
  XTop_Set_ifm_ch(&tp, ifm_ch);
  XTop_Set_ifm_h(&tp, ifm_h);
  XTop_Set_ifm_w(&tp, ifm_w);
  XTop_Set_ofm_ch(&tp, ofm_ch);
  XTop_Set_ofm_h(&tp, ofm_h);
  XTop_Set_ofm_w(&tp, ofm_w);
  XTop_Set_I_CH(&tp, I_CH);
  XTop_Set_I_H(&tp, I_H);
  XTop_Set_I_W(&tp, I_W);
  XTop_Set_O_CH(&tp, O_CH);
  XTop_Set_O_H(&tp, O_H);
  XTop_Set_O_W(&tp, O_W);
  XTop_Set_ker_size(&tp, k);
  XTop_Set_stride(&tp, s);
  XTop_Set_padding(&tp, p);
  XTop_Set_layer_type(&tp, layertpe);
  XTop_Set_act_silu(&tp, act_silu);
  XTop_Set_CNT(&tp, CNT);
  XTop_Set_ifm_q1(&tp, ifm_q1);
  XTop_Set_ifm_q2(&tp, ifm_q2);
  XTop_Set_weights_q(&tp, weights_q);
  XTop_Set_bias_q(&tp, bias_q);
  XTop_Set_ofm_q_before_act(&tp, ofm_before_act_q);
  XTop_Set_ofm_q_after_q(&tp, ofm_after_act_q);
  XTop_InterruptGlobalDisable(&tp);
  XTop_Start(&tp);
  while (1)
  {
    if (XTop_IsDone(&tp))
    {
      break;
    }
  }
  XTop_Release(&tp);
}
void top_conv(u32 ifm_in, u32 ofm_out, u32 weights, u32 bias,
              int ifm_ch, int ifm_h, int ifm_w, int ofm_ch, int ofm_h,
              int ofm_w, int I_CH, int I_H, int I_W, int O_CH, int O_H, int O_W,
              int ker_size, int stride, int padding, bool act_silu, int CNT,
              int ifm_q1, int ifm_q2, int weights_q, int bias_q,
              int ofm_q_before_act, int ofm_q_after_q) {
  // top(ifm_in, ofm_out, weights, bias, ifm_ch, ifm_h, ifm_w, ofm_ch, ofm_h,
  //     ofm_w, I_CH, I_H, I_W, O_CH, O_H, O_W, ker_size, stride, padding, 0,
  //     act_silu, CNT, ifm_q1, ifm_q2, weights_q, bias_q, ofm_q_before_act,
  //     ofm_q_after_q);
  top(ifm_in, ofm_out, weights, bias, ifm_ch, ifm_h, ifm_w, ofm_ch, ofm_h,
      ofm_w, I_CH, I_H, I_W, O_CH, O_H, O_W, ker_size, stride, padding, 0,
      act_silu, CNT, ifm_q1, ifm_q2, weights_q, bias_q, ofm_q_before_act,
      ofm_q_after_q);
}
void top_max(u32 ifm_in, u32 ofm_out, u32 weights, u32 bias,
             int ifm_ch, int ifm_h, int ifm_w, int ofm_ch, int ofm_h, int ofm_w,
             int I_CH, int I_H, int I_W, int O_CH, int O_H, int O_W,
             int ker_size, int stride, int padding, bool act_silu, int CNT,
             int ifm_q1, int ifm_q2, int weights_q, int bias_q,
             int ofm_q_before_act, int ofm_q_after_q) {
  top(ifm_in, ofm_out, weights, bias, ifm_ch, ifm_h, ifm_w, ofm_ch, ofm_h,
      ofm_w, I_CH, I_H, I_W, O_CH, O_H, O_W, ker_size, stride, padding, 1,
      act_silu, CNT, ifm_q1, ifm_q2, weights_q, bias_q, ofm_q_before_act,
      ofm_q_after_q);
}


template <typename T>
void upsample_cpu(T in, int w, int h, int c, int batch, int stride, int forward,
                  float scale, T out) {
  int i, j, k, b;
  for (b = 0; b < batch; ++b) {
    for (k = 0; k < c; ++k) {
      for (j = 0; j < h * stride; ++j) {
        for (i = 0; i < w * stride; ++i) {
          int in_index =
              b * w * h * c + k * w * h + (j / stride) * w + i / stride;
          int out_index = b * w * h * c * stride * stride +
                          k * w * h * stride * stride + j * w * stride + i;
          if (forward)
            out[out_index] = scale * in[in_index];
          else
            in[in_index] += scale * out[out_index];
        }
      }
    }
  }
}


void forward_upsample(layer l, uint32_t address_in, uint32_t address_out, quan_t* a, quan_t* b) {
  // fill_cpu(l.out_c * l.out_h * l.out_w, 0, address_out, 1);
  copy_dev2mem((uint8_t*)(a), l.c * l.h * l.w * sizeof(quan_t), address_in);
  upsample_cpu(a, l.w, l.h, l.c, 1, l.stride, 1, 1, b);
  copy_mem2dev((uint8_t*)b, 4 * l.c * l.h * l.w * sizeof(quan_t), address_out);
}

void forward_yolo(layer l, float *address_in, float *result) {
  static uint32_t offsets;
  int index_in = 0;
  int index_out = 0;
  int c = l.classes + 4 + 1;
  float *input_index = address_in;
  float *temp_result = result + offsets;
  offsets += l.out_c * l.out_h * l.out_w;
  float tmp = 0;
  for (int k = 0; k < l.h; k++) {
    for (int j = 0; j < l.n; j++) {
      for (int h = 0; h < l.w; h++) {
        for (int m = 0; m < c; m++) {
          index_out = j * l.w * l.h * c + k * l.w * c + h * c + m;
          index_in = j * l.w * l.h * c + m * l.w * l.h + k * l.w + h;
          tmp = input_index[index_in];
          if (m == 0) {
            temp_result[index_out] = (tmp * 2 - 0.5 + h) * l.stride;
          } else if (m == 1) {
            temp_result[index_out] = (tmp * 2 - 0.5 + k) * l.stride;
          } else if (m == 2) {
            temp_result[index_out] = (tmp * tmp * 4 * l.biases[l.mask[j] * 2]);
          } else if (m == 3) {
            temp_result[index_out] =
                (tmp * tmp * 4 * l.biases[l.mask[j] * 2 + 1]);
          } else {
            temp_result[index_out] = tmp;
          }
        }
      }
    }
  }
}
void net_ps(network *net, float *inputs, float *out) {
  //#ifndef BOARD

  copy_file2mem("weights_quan.bin", 14516224, WEIGHTS_BASE);
  copy_file2mem("bias_quan.bin", 24576, BIAS_BASE);


  uint8_t *weights_q_list = (uint8_t *)malloc(sizeof(uint8_t) * 108);
  FILE *fweights_q_list =
      fopen("weights_q_list.bin", "rb");
  fread(weights_q_list, sizeof(uint8_t), 108, fweights_q_list);
  fclose(fweights_q_list);

  uint8_t *bias_q_list = (uint8_t *)malloc(sizeof(uint8_t) * 108);
  FILE *fbias_q_list = fopen("bias_q_list.bin", "rb");
  fread(bias_q_list, sizeof(uint8_t), 108, fbias_q_list);
  fclose(fbias_q_list);

  uint8_t *ofm_q_list_before_act = (uint8_t *)malloc(sizeof(uint8_t) * 108);
  FILE *fofm_q_list_before_act =
      fopen("ofm_q_list_before_act.bin", "rb");
  fread(ofm_q_list_before_act, sizeof(uint8_t), 108, fofm_q_list_before_act);
  fclose(fofm_q_list_before_act);

  uint8_t *ofm_q_list_after_act = (uint8_t *)malloc(sizeof(uint8_t) * 108);
  FILE *fofm_q_list_after_act =
      fopen("ofm_q_list_after_act.bin", "rb");
  fread(ofm_q_list_after_act, sizeof(uint8_t), 108, fofm_q_list_after_act);
  fclose(fofm_q_list_after_act);

  int inputs_nums = 320 * 320 * 32 * 2;
  // quan_t *mem_share = (quan_t*)malloc(sizeof(quan_t)*(inputs_nums+640));
  // quan_t *mem_share = new quan_t[inputs_nums + IFM_PAD_LENGTH];
  quan_t *inputs_quan = new quan_t [net->inputs];
  for (int i = 0; i < net->inputs; i++) {
    inputs_quan[i] = (quan_t)(inputs[i] * pow(2, 14));
  }
  copy_mem2dev((uint8_t*)inputs_quan, net->inputs*(sizeof(quan_t)), MEM_BASE);
  // for (int i = 0; i < net->inputs; i++) {
  //   mem_share[i + IFM_PAD_LENGTH] = (quan_t)(inputs[i] * pow(2, 14));
  // }

  // quan_t **address_in = (quan_t**)malloc(sizeof(quan_t*)*net->n);
  uint32_t* address_in = new uint32_t [net->n];
  uint32_t* address_out = new uint32_t [net->n];
  generate_address(net, address_in, address_out, (uint32_t)MEM_BASE);

  const uint8_t temp_save_list[7] = {39, 24, 68, 57, 78, 88, 98};
  auto tmp39 = new quan_t[40 * 40 * 256];
  auto tmp24 = new quan_t[80 * 80 * 128];
  auto tmp68 = new quan_t[40 * 40 * 128];
  auto tmp57 = new quan_t[20 * 20 * 256];
  auto tmp78 = new quan_t[80 * 80 * 128];
  auto tmp88 = new quan_t[40 * 40 * 256];
  auto tmp98 = new quan_t[20 * 20 * 512];
  auto a = new quan_t [64*320*320];
  auto b = new quan_t [64*320*320];
  // auto temp_yolo_quan = new quan_t [255*80*80];
  auto temp_yolo_float = new float [255*80*80];

  double yolo_time0 = 0;
  double yolo_time1 = 0;
  int weights_offset = 0;
  int bias_offset = 0;
  u8 index = 0;
  u8 layertype = 0;
  bool act_type;
  uint8_t ifm_q1, ifm_q2;
  double time0 = what_time_is_it_now();
  while (index < net->n) {
    printf("layer %3d \n", index);
    layer l = net->layers[index];
    if (l.type == CONVOLUTIONAL) {
      std::cout << static_cast<int>(index) << " conv " << l.c << "x" << l.h
                << "x" << l.w << " --> " << l.out_c << "x" << l.out_h << "x"
                << l.out_w << std::endl;
      std::cout << "kernl size " << l.size << " stride = " << l.stride
                << " padding = " << l.pad << std::endl;
      layertype = 0;
      // act_type = (l.activation == SILU) ? (0) : (1);
      int I_CH = MIN(TN, l.c);
      int O_CH = MIN(TM, l.out_c);
      int O_H = MIN(((ITH - l.size) / l.stride + 1), OTH);
      O_H = MIN(O_H, l.out_h);
      int O_W = MIN(((ITW - l.size) / l.stride + 1), OTW);
      O_W = MIN(O_W, l.out_w);
      int I_H = ((O_H - 1) * l.stride + l.size);
      int I_W = ((O_W - 1) * l.stride + l.size);

      int h1 = ceil((float)(l.out_h) / O_H);
      int w1 = ceil((float)(l.out_w) / O_W);
      int ch1 = ceil((float)(l.out_c) / O_CH);
      int CNT = h1 * w1 * ch1;
      // u8 act_type = l.activation == SILU ? 0 : 1;
      // printf("I_CH = %2d, O_CH = %2d, O_H = %2d, O_W = %2d, I_H = %2d, I_W =
      // "
      //        "%2d, CNT = %3d\n",
      //        I_CH, O_CH, O_H, O_W, I_H, I_W, CNT);
      if(index==0) {ifm_q1=ifm_q2=14;}
      else{
        get_q1_q2_for_ifm_conv(index, ofm_q_list_after_act, ifm_q1, ifm_q2);
      }
      double time00 = what_time_is_it_now();

      top_conv(address_in[index], address_out[index], WEIGHTS_BASE + weights_offset,
               BIAS_BASE + bias_offset, l.c, l.h, l.w, l.out_c, l.out_h, l.out_w,
               I_CH, I_H, I_W, O_CH, O_H, O_W, l.size, l.stride, l.pad,
               l.activation == SILU, CNT, ifm_q1, ifm_q2, weights_q_list[index],
               bias_q_list[index], ofm_q_list_before_act[index],
               ofm_q_list_after_act[index]);
      double time01 = what_time_is_it_now();
      float flps = (l.size * l.size * l.c + 200) * l.out_c * l.out_h * l.out_w;
      flps = 2 * l.size * l.size * l.c * l.out_c * l.out_h * l.out_w + 20 * l.out_c * l.out_h * l.out_w;
      printf("time = %f, flps = %f\n", time01 - time00, flps / ((time01 - time00) * 1000000000)); 
      weights_offset += l.out_c * l.c * l.size * l.size * sizeof(quan_t);
      bias_offset += l.out_c * sizeof(quan_t);
    } else if (l.type == MAXPOOL) {
      printf("maxpool\n");

      // if (index == 42) {
      //   l.size = 13;
        // l.pad = 6;
        
        layertype = 1;
        act_type = 2;
        int I_CH = MIN(TN, l.c);
        int O_CH = MIN(POOL_MIN_MN, l.out_c);
        int O_H = MIN(((ITH - l.size) / l.stride + 1), OTH);
        O_H = MIN(O_H, l.out_h);
        int O_W = MIN(((ITW - l.size) / l.stride + 1), OTW);
        O_W = MIN(O_W, l.out_w);
        int I_H = ((O_H - 1) * l.stride + l.size);
        int I_W = ((O_W - 1) * l.stride + l.size);

        int h1 = ceil((float)(l.out_h) / O_H);
        int w1 = ceil((float)(l.out_w) / O_W);
        int ch1 = ceil((float)(l.out_c) / TN);
        int CNT = h1 * w1 * ch1 + 1;
        ifm_q1 = ifm_q2 = ofm_q_list_after_act[index - 1];
      double time00 = what_time_is_it_now();
        top_max(address_in[index], address_out[index], WEIGHTS_BASE, BIAS_BASE, l.c, l.h,
                l.w, l.out_c, l.out_h, l.out_w, I_CH, I_H, I_W, O_CH, O_H, O_W,
                l.size, l.stride, l.pad, l.activation == SILU, CNT, ifm_q1,
                ifm_q2, weights_q_list[index], bias_q_list[index],
                ofm_q_list_after_act[index], ofm_q_list_after_act[index]);
      double time01 = what_time_is_it_now();
      printf("time = %f\n", time01 - time00); 
      // }
    } else if (l.type == ROUTE) {
      printf("route\n");
      if (index == 59) {
        copy_mem2dev((uint8_t *)(tmp39), sizeof(quan_t) * l.c * l.h * l.w,
                     address_out[index] +
                         (l.c * l.h * l.w + IFM_PAD_LENGTH) * sizeof(quan_t));
        // memcpy(address_out[index] + IFM_PAD_LENGTH + l.c * l.h * l.w, tmp39,
        //        sizeof(quan_t) * l.c * l.h * l.w);
      } else if (index == 70) {
        copy_mem2dev((uint8_t *)(tmp24), sizeof(quan_t) * l.c * l.h * l.w,
                     address_out[index] +
                         (l.c * l.h * l.w + IFM_PAD_LENGTH) * sizeof(quan_t));
        // memcpy(address_out[index] + IFM_PAD_LENGTH + l.c * l.h * l.w, tmp24,
        //        sizeof(quan_t) * l.c * l.h * l.w);
      } else if (index == 80) {
        copy_mem2dev((uint8_t *)(tmp68), sizeof(quan_t) * l.c * l.h * l.w,
                     address_out[index] +
                         (l.c * l.h * l.w + IFM_PAD_LENGTH) * sizeof(quan_t));
        // memcpy(address_out[index] + IFM_PAD_LENGTH + l.c * l.h * l.w, tmp68,
        //        sizeof(quan_t) * l.c * l.h * l.w);
      } else if (index == 90) {
        copy_mem2dev((uint8_t *)(tmp57), sizeof(quan_t) * l.c * l.h * l.w,
                     address_out[index] +
                         (l.c * l.h * l.w + IFM_PAD_LENGTH) * sizeof(quan_t));
        // memcpy(address_out[index] + IFM_PAD_LENGTH + l.c * l.h * l.w, tmp57,
        //        sizeof(quan_t) * l.c * l.h * l.w);
      } else if (index == 99) {
        copy_mem2dev((uint8_t *)(tmp78), sizeof(quan_t) * l.inputs,
                     address_out[index] + IFM_PAD_LENGTH * sizeof(quan_t));
        // memcpy(address_out[index]+ IFM_PAD_LENGTH, tmp78, sizeof(quan_t) * l.inputs);
      } else if (index == 102) {
        copy_mem2dev((uint8_t *)(tmp88), sizeof(quan_t) * l.inputs,
                     address_out[index]+ IFM_PAD_LENGTH * sizeof(quan_t));
        // memcpy(address_out[index]+ IFM_PAD_LENGTH, tmp88, sizeof(quan_t) * l.inputs);
      } else if (index == 105) {
        copy_mem2dev((uint8_t *)(tmp98), sizeof(quan_t) * l.inputs,
                     address_out[index]+ IFM_PAD_LENGTH * sizeof(quan_t));
        // memcpy(address_out[index]+ IFM_PAD_LENGTH, tmp98, sizeof(quan_t) * l.inputs);
      }
    } else if (l.type == SHORTCUT) {
      printf("shortcut\n");
      int nums = l.c * l.h * l.w;      
      get_q1_q2_for_ifm_shortcut(index, ofm_q_list_after_act, ifm_q1, ifm_q2);
      printf("1\n");
      copy_dev2mem((uint8_t *)a, nums * sizeof(quan_t),
                   address_in[index] + IFM_PAD_LENGTH * sizeof(quan_t));
      printf("2\n");
      copy_dev2mem((uint8_t *)b, nums * sizeof(quan_t),
                   address_out[index] + IFM_PAD_LENGTH * sizeof(quan_t));
      for (int i=0;i<nums;i++){
        b[i] =
            ((a[i] << (ONCHIP_Q - ifm_q1)) + (b[i] << (ONCHIP_Q - ifm_q2))) >>
            (ONCHIP_Q - ofm_q_list_after_act[index]);
      }
      printf("3\n");
      copy_mem2dev((uint8_t *)b, nums * sizeof(quan_t),
                   address_out[index] + IFM_PAD_LENGTH * sizeof(quan_t));
      // forward_shortcut(l, address_in[index], address_out[index]);
    } else if (l.type == UPSAMPLE) {
      printf("upsample\n");
      forward_upsample(l, address_in[index] + IFM_PAD_LENGTH * sizeof(quan_t),
                       address_out[index] + IFM_PAD_LENGTH * sizeof(quan_t), a, b);
    } else if (l.type == YOLO) {
      printf("yolo\n");
      double t00 = what_time_is_it_now();
      int nums = l.c * l.h * l.w;
      copy_dev2mem((uint8_t *)(a), nums * sizeof(quan_t),
                   address_in[index] + IFM_PAD_LENGTH * sizeof(quan_t));
      for (int i = 0; i < nums; i++) {
        temp_yolo_float[i] = (float)(a[i] * pow(2, -ofm_q_list_after_act[index-1]));
        temp_yolo_float[i] = 1 / (1 + expf(-temp_yolo_float[i]));
      }
      double t01 = what_time_is_it_now();

      forward_yolo(l,temp_yolo_float,out);
      double t02 = what_time_is_it_now();
      yolo_time0 += (t01 - t00);
      yolo_time1 += (t02 - t00);
      printf("yolo_time0 = %f\n", t01 - t00);
      printf("yolo_time1 = %f\n", t02 - t00);
      printf("yolo done\n");
      // auto s_float = new float[l.c * l.h * l.w];
      // auto s_quan = new quan_t[l.c * l.h * l.w];
      // memcpy(s_quan, address_in[index]+ IFM_PAD_LENGTH, sizeof(quan_t) * l.c * l.h * l.w);
      // std::cout << " q for yolo act " << (int)ofm_q_list_after_act[index-1] << std::endl;
      // // if(index==107) exit(0);
      // for (int i = 0; i < l.c * l.h * l.w; i++) {
      //   s_float[i] =
      //       (float)(s_quan[i] * powf(2, -ofm_q_list_before_act[index - 1]));
      //       s_float[i] = 1 / (1+expf(-s_float[i]));
      // }
      // forward_yolo(l, s_float, out);
      // // forward_yolo(l, address_in[index], out);
      // delete[] s_quan;
      // delete[] s_float;
    }

    if (index == 42) {
      // FILE* fo = fopen("spp.txt","w");
      // for (int i = 0; i < 1024; i++) {
      //     for (int j = 0; j < 20; j++) {
      //         for (int k = 0; k < 15; k++) {
      //             fprintf(fo, "%f ", address_in[index][i * 300 + j * 15 +
      //             k]);
      //         }
      //         fprintf(fo, "\n");
      //     }
      //     fprintf(fo,"\n");
      // }
      // fclose(fo);
    }
    if (check_list(index, temp_save_list)) {
      if (index == 39) {
        copy_dev2mem((uint8_t *)(tmp39), sizeof(quan_t) * l.outputs,
                     address_out[index] + IFM_PAD_LENGTH * sizeof(quan_t));
        // memcpy(tmp39, address_out[index]+ IFM_PAD_LENGTH, sizeof(quan_t) * l.outputs);
      } else if (index == 57) {
        copy_dev2mem((uint8_t *)(tmp57), sizeof(quan_t) * l.outputs,
                     address_out[index] + IFM_PAD_LENGTH * sizeof(quan_t));
        // memcpy(tmp57, address_out[index]+ IFM_PAD_LENGTH, sizeof(quan_t) *
        // l.outputs);
      } else if (index == 24) {
        copy_dev2mem((uint8_t *)(tmp24), sizeof(quan_t) * l.outputs,
                     address_out[index] + IFM_PAD_LENGTH * sizeof(quan_t));
        // memcpy(tmp24, address_out[index]+ IFM_PAD_LENGTH, sizeof(quan_t) *
        // l.outputs);
      } else if (index == 68) {
        copy_dev2mem((uint8_t *)(tmp68), sizeof(quan_t) * l.outputs,
                     address_out[index] + IFM_PAD_LENGTH * sizeof(quan_t));
        // memcpy(tmp68, address_out[index]+ IFM_PAD_LENGTH, sizeof(quan_t) *
        // l.outputs);
      } else if (index == 78) {
        copy_dev2mem((uint8_t *)(tmp78), sizeof(quan_t) * l.outputs,
                     address_out[index] + IFM_PAD_LENGTH * sizeof(quan_t));
        // memcpy(tmp78, address_out[index]+ IFM_PAD_LENGTH, sizeof(quan_t) *
        // l.outputs);
      } else if (index == 88) {
        copy_dev2mem((uint8_t *)(tmp88), sizeof(quan_t) * l.outputs,
                     address_out[index] + IFM_PAD_LENGTH * sizeof(quan_t));
        // memcpy(tmp88, address_out[index]+ IFM_PAD_LENGTH, sizeof(quan_t) *
        // l.outputs);
      } else if (index == 98) {
        copy_dev2mem((uint8_t *)(tmp98), sizeof(quan_t) * l.outputs,
                     address_out[index] + IFM_PAD_LENGTH * sizeof(quan_t));
        // memcpy(tmp98, address_out[index]+ IFM_PAD_LENGTH, sizeof(quan_t) * l.outputs);
      }
    }
    index += 1;
  }
  // std::cout << int(index) << std::endl;
  double time1 = what_time_is_it_now();
  printf("all time = %f\n", time1 - time0 - yolo_time0);
  printf("all time = %f\n", time1 - time0 - yolo_time1);
  delete[] inputs_quan;
  delete[] address_in;
  delete[] address_out;
  delete[] tmp24;
  delete[] tmp39;
  delete[] tmp57;
  delete[] tmp68;
  delete[] tmp78;
  delete[] tmp88;
  delete[] tmp98;
  delete [] a;
  delete [] b;
  delete [] temp_yolo_float;
  //#else
  //#endif
}

template <typename T>
void generate_address(network *net, T address_in[], T address_out[],
                      T base_address) {
  address_in[0] = base_address - IFM_PAD_LENGTH * sizeof(quan_t);
  address_out[0] = base_address + 320 * 320 * 32 - IFM_PAD_LENGTH * sizeof(quan_t);

  u8 index = 1;
  while (index < net->n) {
    if (check_list(index, c31_list)) {
      generate_c31_address(net, address_in, address_out, index);
      index += 8;
    } else if (check_list(index, c33_list)) {
      generate_c33_address(net, address_in, address_out, index);
      index += 14;
    } else if (check_list(index, spp_list)) {
      generate_spp_address(net, address_in, address_out, index);
      index += 8;
    } else if (check_list(index, concat_list)) {
      generate_concat_address(net, address_in, address_out, index);
      index++;
    } else {
      swap_address(address_in, address_out, index);
      index++;
    }
  }
}

template <size_t SIZE>
bool check_list(const u8 &index, const u8 (&indexes)[SIZE]) {
  for (auto i : indexes) {
    if (index == i)
      return true;
  }
  return false;
}

template <typename T>
void generate_c31_address(network *net, T address_in[], T address_out[],
                          const u8 &index) {
  layer l = net->layers[index];
  const int layer_size = l.out_c * l.out_h * l.out_w * sizeof(quan_t);
  T add_begin = address_out[index - 1];
  T add_end = address_in[index - 1];
  // cv2
  address_in[index] = add_begin;
  address_out[index] = add_end + layer_size;
  // route
  address_in[index + 1] = add_end;
  address_out[index + 1] = add_end;
  // cv1
  address_in[index + 2] = add_begin;
  address_out[index + 2] = add_end;
  // bn.cv1
  address_in[index + 3] = add_end;
  address_out[index + 3] = add_begin;
  // bn.cv2
  address_in[index + 4] = add_begin;
  address_out[index + 4] = add_begin + layer_size;
  // shortcut
  address_in[index + 5] = add_begin + layer_size; // address_out[index + 4];
  address_out[index + 5] = add_end;
  // cat
  address_in[index + 6] = add_end;
  address_out[index + 6] = add_end;
  // cv3
  address_in[index + 7] = add_end;
  address_out[index + 7] = add_begin;
}

template <typename T>
void generate_c33_address(network *net, T address_in[], T address_out[],
                          const u8 &index) {
  layer l = net->layers[index];
  const int layer_size = l.out_c * l.out_h * l.out_w * sizeof(quan_t);
  T add_begin = address_out[index - 1];
  T add_end = address_in[index - 1];
  // cv2
  address_in[index] = add_begin;
  address_out[index] = add_end + layer_size;
  // route
  address_in[index + 1] = add_begin;
  address_out[index + 1] = add_end;
  // cv1
  address_in[index + 2] = add_begin;
  address_out[index + 2] = add_end;
  // bottleneck
  for (int i = 0; i < 3; i++) {
    // bn.cv1
    address_in[index + 3 + i * 3] = add_end;
    address_out[index + 3 + i * 3] = add_begin;
    // bn/cv2
    address_in[index + 4 + i * 3] = add_begin;
    address_out[index + 4 + i * 3] = add_begin + layer_size;
    // add
    address_in[index + 5 + i * 3] = add_begin + layer_size;
    address_out[index + 5 + i * 3] = add_end;
  }
  // route
  address_in[index + 12] = add_end;
  address_out[index + 12] = add_end;
  // cv3
  address_in[index + 13] = add_end;
  address_out[index + 13] = add_begin;
}

template <typename T>
void generate_spp_address(network *net, T address_in[], T address_out[],
                          const u8 &index) {
  layer l = net->layers[index];
  const int layer_size = l.out_c * l.out_h * l.out_w * sizeof(quan_t);
  T add_begin = address_out[index - 1];
  T add_end = address_in[index - 1];
  // cv1
  address_in[index] = add_begin;
  address_out[index] = add_end;
  // max5
  address_in[index + 1] = add_end;
  address_out[index + 1] = add_end + layer_size;
  // route
  address_in[index + 2] = add_end;
  address_out[index + 2] = add_end;
  // max9
  address_in[index + 3] = add_end;
  address_out[index + 3] = add_end + layer_size * 2;
  // route
  address_in[index + 4] = add_end;
  address_out[index + 4] = add_end;
  // max 13
  address_in[index + 5] = add_end;
  address_out[index + 5] = add_end + layer_size * 3;
  // route 4 spp
  address_in[index + 6] = add_end;
  address_out[index + 6] = add_end;
  // cv2
  address_in[index + 7] = add_end;
  address_out[index + 7] = add_begin;
}

template <typename T>
void generate_concat_address(network *net, T address_in[], T address_out[],
                             const u8 &index) {
  layer l = net->layers[index];
  const int layer_size = l.c * l.h * l.w;
  // address_in[59] = address_out[index - 1] + layer_size;
  // address_out[59] = address_out[index - 1];

  address_in[index] = address_in[index - 1];
  address_out[index] = address_out[index - 1];
}

template <typename T>
void swap_address(T address_in[], T address_out[], const u8 &index) {
  address_in[index] = address_out[index - 1];
  address_out[index] = address_in[index - 1];
}



template <typename T>
void forward_shortcut(layer l, T address_in, T address_out) {
  int nums = l.c * l.h * l.w;
  for (int i = 0; i < nums; i++) {
    address_out[i] += address_in[i];
  }
}
