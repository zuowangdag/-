//
// Created by admin on 2022/11/11.
//
#include "ps.h"
// #include "acc_quan.h"
#include "acc_quan.h"
#include "utils.h"
#include "yo_struct.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <stdint.h>
#define ONCHIP_Q 20
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
void net_ps(network *net, float *inputs, float *out) {
  //#ifndef BOARD

  char *weights_name = (char *)"weights_quan.bin";
  int weights_size = get_file_size(weights_name);
  quan_t *weights = (quan_t *)malloc(weights_size);
  FILE *fweights_quan = fopen(weights_name, "rb");
  fread(weights, sizeof(quan_t), weights_size / sizeof(quan_t), fweights_quan);
  fclose(fweights_quan);
  char *bias_name = (char *)"bias_quan.bin";
  int bias_size = get_file_size(bias_name);
  quan_t *bias = (quan_t *)malloc(bias_size);
  FILE *fbias = fopen(bias_name, "rb");
  fread(bias, sizeof(quan_t), bias_size / sizeof(quan_t), fbias);
  fclose(fbias);

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
  quan_t *mem_share = new quan_t[inputs_nums + 640];

  for (int i = 0; i < net->inputs; i++) {
    mem_share[i + 640] = (quan_t)(inputs[i] * pow(2, 14));
  }

  // quan_t **address_in = (quan_t**)malloc(sizeof(quan_t*)*net->n);
  quan_t **address_in = new quan_t *[net->n];
  quan_t **address_out = new quan_t *[net->n];
  generate_address(net, address_in, address_out, mem_share);

  const uint8_t temp_save_list[7] = {39, 24, 68, 57, 78, 88, 98};
  auto tmp39 = new quan_t[40 * 40 * 256];
  auto tmp24 = new quan_t[80 * 80 * 128];
  auto tmp68 = new quan_t[40 * 40 * 128];
  auto tmp57 = new quan_t[20 * 20 * 256];
  auto tmp78 = new quan_t[80 * 80 * 128];
  auto tmp88 = new quan_t[40 * 40 * 256];
  auto tmp98 = new quan_t[20 * 20 * 512];

  int weights_offset = 0;
  int bias_offset = 0;
  u8 index = 0;
  u8 layertype = 0;
  bool act_type;
  uint8_t ifm_q1, ifm_q2;
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
      top_conv(address_in[index], address_out[index], weights + weights_offset,
               bias + bias_offset, l.c, l.h, l.w, l.out_c, l.out_h, l.out_w,
               I_CH, I_H, I_W, O_CH, O_H, O_W, l.size, l.stride, l.pad,
               l.activation == SILU, CNT, ifm_q1, ifm_q2, weights_q_list[index],
               bias_q_list[index], ofm_q_list_before_act[index],
               ofm_q_list_after_act[index]);
      weights_offset += l.out_c * l.c * l.size * l.size;
      bias_offset += l.out_c;
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
        top_max(address_in[index], address_out[index], weights, bias, l.c, l.h,
                l.w, l.out_c, l.out_h, l.out_w, I_CH, I_H, I_W, O_CH, O_H, O_W,
                l.size, l.stride, l.pad, false, CNT, ifm_q1,
                ifm_q2, weights_q_list[index], bias_q_list[index],
                ifm_q1, ifm_q2);
      // }
    } else if (l.type == ROUTE) {
      printf("route\n");
      if (index == 59) {
        memcpy(address_out[index] + l.c * l.h * l.w, tmp39,
               sizeof(quan_t) * l.c * l.h * l.w);
      } else if (index == 70) {
        memcpy(address_out[index] + l.c * l.h * l.w, tmp24,
               sizeof(quan_t) * l.c * l.h * l.w);
      } else if (index == 80) {
        memcpy(address_out[index] + l.c * l.h * l.w, tmp68,
               sizeof(quan_t) * l.c * l.h * l.w);
      } else if (index == 90) {
        memcpy(address_out[index] + l.c * l.h * l.w, tmp57,
               sizeof(quan_t) * l.c * l.h * l.w);
      } else if (index == 99) {
        memcpy(address_out[index], tmp78, sizeof(quan_t) * l.inputs);
      } else if (index == 102) {
        memcpy(address_out[index], tmp88, sizeof(quan_t) * l.inputs);
      } else if (index == 105) {
        memcpy(address_out[index], tmp98, sizeof(quan_t) * l.inputs);
      }
    } else if (l.type == SHORTCUT) {
      printf("shortcut\n");
      // auto s_quan0 = new quan_t[l.c * l.h * l.w];
      // auto s_quan1 = new quan_t[l.c * l.h * l.w];
      // auto s_float0 = new float[l.c * l.h * l.w];
      // auto s_float1 = new float[l.c * l.h * l.w];
      // memcpy(s_quan0, address_in[index], sizeof(quan_t) * l.c * l.h * l.w);
      // memcpy(s_quan1, address_out[index], sizeof(quan_t) * l.c * l.h * l.w);
      // get_q1_q2_for_ifm_shortcut(index, ofm_q_list_after_act, ifm_q1, ifm_q2);
      // for (int i = 0; i < l.c * l.h * l.w; i++) {
      //   s_float0[i] = s_quan0[i] * powf(2, -ifm_q1);
      //   s_float1[i] = s_quan1[i] * powf(2, -ifm_q2);
      //   s_float0[i] = s_float0[i] + s_float1[i];
      //   s_quan1[i] =
      //       (quan_t)(s_float0[i] * pow(2, ofm_q_list_after_act[index]));
      // }
      // memcpy(address_out[index], s_quan1, sizeof(quan_t) * l.c * l.h * l.w);
      // delete[] s_quan0;
      // delete[] s_quan1;
      // delete[] s_float0;
      // delete[] s_float1;
      get_q1_q2_for_ifm_shortcut(index, ofm_q_list_after_act, ifm_q1, ifm_q2);
      int nums = l.c * l.h * l.w;
      for (int i =0;i<nums;i++){
        address_out[index][i] = ((address_in[index][i] << (ONCHIP_Q - ifm_q1)) + (address_out[index][i] << (ONCHIP_Q- ifm_q2)))
                                >> (ONCHIP_Q - ofm_q_list_after_act[index]);
      }
      if(index==7) {
    	  FILE *ft = fopen("res.txt","w");
    	  for(int i = 0; i < nums;i++){
    		  fprintf(ft,"%d\t", address_out[index][i]);
    		  if((i+1)%10==0){
    			  fprintf(ft, "\n");
    		  }
    	  }
    	  fclose(ft);
      }

      // forward_shortcut(l, address_in[index], address_out[index]);
    } else if (l.type == UPSAMPLE) {
      printf("upsample\n");
      forward_upsample(l, address_in[index], address_out[index]);
    } else if (l.type == YOLO) {
      printf("yolo\n");
      auto s_float = new float[l.c * l.h * l.w];
      auto s_quan = new quan_t[l.c * l.h * l.w];
      memcpy(s_quan, address_in[index], sizeof(quan_t) * l.c * l.h * l.w);
      std::cout << " q for yolo act " << (int)ofm_q_list_after_act[index-1] << std::endl;
      // if(index==107) exit(0);
      for (int i = 0; i < l.c * l.h * l.w; i++) {
        s_float[i] =
            (float)(s_quan[i] * powf(2, -ofm_q_list_before_act[index - 1]));
            s_float[i] = 1 / (1+expf(-s_float[i]));
      }
      forward_yolo(l, s_float, out);
      // forward_yolo(l, address_in[index], out);
      delete[] s_quan;
      delete[] s_float;
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
        memcpy(tmp39, address_out[index], sizeof(quan_t) * l.outputs);
      } else if (index == 57) {
        memcpy(tmp57, address_out[index], sizeof(quan_t) * l.outputs);
      } else if (index == 24) {
        memcpy(tmp24, address_out[index], sizeof(quan_t) * l.outputs);
      } else if (index == 68) {
        memcpy(tmp68, address_out[index], sizeof(quan_t) * l.outputs);
      } else if (index == 78) {
        memcpy(tmp78, address_out[index], sizeof(quan_t) * l.outputs);
      } else if (index == 88) {
        memcpy(tmp88, address_out[index], sizeof(quan_t) * l.outputs);
      } else if (index == 98) {
        memcpy(tmp98, address_out[index], sizeof(quan_t) * l.outputs);
      }
    }
    index += 1;
  }
  // std::cout << int(index) << std::endl;
  delete[] mem_share;
  delete[] address_in;
  delete[] address_out;
  delete[] tmp24;
  delete[] tmp39;
  delete[] tmp57;
  delete[] tmp68;
  delete[] tmp78;
  delete[] tmp88;
  delete[] tmp98;

  //#else
  //#endif
}

template <typename T>
void generate_address(network *net, T address_in[], T address_out[],
                      T base_address) {
  address_in[0] = base_address + 640;
  address_out[0] = base_address + 320 * 320 * 32 + 640;

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
  const int layer_size = l.out_c * l.out_h * l.out_w;
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
  const int layer_size = l.out_c * l.out_h * l.out_w;
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
  const int layer_size = l.out_c * l.out_h * l.out_w;
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

void top_conv(data_t *ifm_in, data_t *ofm_out, data_t *weights, data_t *bias,
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
void top_max(data_t *ifm_in, data_t *ofm_out, data_t *weights, data_t *bias,
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
void ps_Focus(network *net, T address_in[], T address_out[], const u8 &index,
              T weights, int weights_offset, T bias, int bias_offset) {
  layer l = net->layers[index];
  std::cout << static_cast<int>(index) << " Focus : conv " << l.c << "x" << l.h
            << "x" << l.w << " --> " << l.out_c << "x" << l.out_h << "x"
            << l.out_w << std::endl;
  std::cout << "kernl size " << l.size << " stride = " << l.stride
            << " padding = " << l.pad << std::endl;
  int I_CH = MIN(TN, l.c);
  int O_CH = MIN(TM, l.out_c);
  int O_H = MIN(((ITH - l.size) / l.stride + 1), OTH);
  int O_W = MIN(((ITW - l.size) / l.stride + 1), OTW);
  int I_H = ((O_H - 1) * l.stride + l.size);
  int I_W = ((O_W - 1) * l.stride + l.size);

  int h1 = ceil((float)(l.out_h) / O_H);
  int w1 = ceil((float)(l.out_w) / O_W);
  int ch1 = ceil((float)l.out_c / O_CH);
  int CNT = h1 * w1 * ch1;
  u8 act_type = l.activation == SILU ? 0 : 1;
  printf("I_CH = %2d, O_CH = %2d, O_H = %2d, O_W = %2d, I_H = %2d, I_W = %2d, "
         "CNT = %3d\n",
         I_CH, O_CH, O_H, O_W, I_H, I_W, CNT);

  top_conv(address_in[index], address_out[index], weights + weights_offset,
           bias + bias_offset, l.c, l.h, l.w, l.out_c, l.out_h, l.out_w, I_CH,
           I_H, I_W, O_CH, O_H, O_W, l.size, l.stride, l.pad, act_type, CNT);
  printf("focus done\n");
}

template <typename T>
void ps_Conv(network *net, T address_in[], T address_out[], const u8 &index) {
  layer l = net->layers[index];
  std::cout << static_cast<int>(index) << " layertype : conv " << l.c << "x"
            << l.h << "x" << l.w << " --> " << l.out_c << "x" << l.out_h << "x"
            << l.out_w << std::endl;
  std::cout << "kernl size " << l.size << " stride = " << l.stride
            << " padding = " << l.pad << std::endl;
  //    top_conv();
}

template <typename T>
void ps_C31(network *net, T address_in[], T address_out[], const u8 &index) {
  layer l_cv2 = net->layers[index];
  layer l_route1 = net->layers[index + 1];
  layer l_cv1 = net->layers[index + 2];
  layer l_bn_cv1 = net->layers[index + 3];
  layer l_bn_cv2 = net->layers[index + 4];
  layer l_bn_add = net->layers[index + 5];
  layer l_route2 = net->layers[index + 6];
  layer l_cv3 = net->layers[index + 7];

  //    top_conv();
  //    top_conv();
  //    top_conv();
  //    top_conv();
  //    top_add();
  //    top_conv();

  //    const u8 c31_index_last = index + 7;
  //    check_save_list();
  //    check_detect_save_list();
  //    if(check_list(c31_index_last, save_list))
  //    {
  //        check_save_list();
  //    }
}

template <typename T>
void ps_SPP(network *net, T address_in[], T address_out[], const u8 &index) {
  layer l_cv1 = net->layers[index];
  layer l_max5 = net->layers[index + 1];
  layer l_route1 = net->layers[index + 2];
  layer l_max9 = net->layers[index + 3];
  layer l_route2 = net->layers[index + 4];
  layer l_max13 = net->layers[index + 5];
  layer l_route3 = net->layers[index + 6];
  layer l_cv2 = net->layers[index + 7];

  //    top_conv();
  //    top_max();
  //    //
  //    top_conv();
}

template <typename T>
void ps_c33(network *net, T address_in[], T address_out[], const u8 &index) {
  layer l_cv2 = net->layers[index];
  layer l_route1 = net->layers[index + 1];
  layer l_cv1 = net->layers[index + 2];
  layer l_bn0_cv1 = net->layers[index + 3];
  layer l_bn0_cv2 = net->layers[index + 4];
  layer l_bn0_add = net->layers[index + 5];
  layer l_bn1_cv1 = net->layers[index + 6];
  layer l_bn1_cv2 = net->layers[index + 7];
  layer l_bn1_add = net->layers[index + 8];
  layer l_bn2_cv1 = net->layers[index + 9];
  layer l_bn2_cv2 = net->layers[index + 10];
  layer l_bn2_add = net->layers[index + 11];
  layer l_concat = net->layers[index + 12];
  layer l_cv3 = net->layers[index + 13];
}

template <typename T>
void ps_concat(network *net, T address_in[], T address_out[], const u8 &index) {

}

template <typename T>
void ps_upsample(network *net, T address_in[], T address_out[],
                 const u8 &index) {
  //    top_upsample();
}

template <typename T>
void ps_detect(network *net, T address_in[], T address_out[], const u8 &index) {
  layer l_route1 = net->layers[index];
  layer l_conv1 = net->layers[index + 1];
  layer l_detect1 = net->layers[index + 2];
  layer l_route2 = net->layers[index + 3];
  layer l_conv2 = net->layers[index + 4];
  layer l_detect2 = net->layers[index + 5];
  layer l_route3 = net->layers[index + 6];
  layer l_conv3 = net->layers[index + 7];
  layer l_detect3 = net->layers[index + 8];
}

template <typename T>
void forward_shortcut(layer l, T address_in, T address_out) {
  int nums = l.c * l.h * l.w;
  for (int i = 0; i < nums; i++) {
    address_out[i] += address_in[i];
  }
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

template <typename T>
void forward_upsample(layer l, T *address_in, T *address_out) {
  // fill_cpu(l.out_c * l.out_h * l.out_w, 0, address_out, 1);
  upsample_cpu(address_in, l.w, l.h, l.c, 1, l.stride, 1, 1, address_out);
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