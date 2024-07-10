//

// Created by admin on 2022/11/11.
//

#ifndef YOLOV5_SFT_PS_H
#define YOLOV5_SFT_PS_H

#include "yo_struct.h"
#include "utils.h"
#include <bits/stdint-uintn.h>
#include <cstdio>
#include <cstring>
// #include "acc_quan.h"

typedef short data_t;
typedef uint8_t u8;
// typedef uint32_t u32;
const u8 save_list[] = {39, 24, 68, 57};
const u8 save_for_detection[3] = {78, 88, 98};
const u8 conv_list[] = {1, 10, 25, 40, 57, 68, 79, 89};
const u8 spp_list[] = {41}; // 48
const u8 focus_list[1] = {0};
const u8 c31_list[] = {2, 49, 60, 71, 81, 91};
const u8 c33_list[] = {11, 26};
//const u8 add_list[] = {};

const u8 upsample_list[2] = {58, 69};
const u8 concat_list[] = {59, 70, 80, 90}; // make sure the address_out is the output address of last layer, then cp to
const u8 detection[] = {99};
const u8 detect_route[3] = {99, 102, 105}; // just use cp operation to address_out
const u8 detect_conv[] = {100, 103, 106};
const u8 detect_process[] = {101, 104, 107}; // address does not important, just save the results to outputs
void net_ps(network *net, float *inputs, float *out);

template<typename T>
void generate_address(network *net, T address_in[], T address_out[], T base_address);

template<size_t SIZE>
bool check_list(const u8 &index, const u8 (&indexes)[SIZE]);

template<typename T>
void generate_c31_address(network *net, T address_in[], T address_out[], const u8 &index);

template<typename T>
void generate_c33_address(network *net, T address_in[], T address_out[], const u8 &index);

template<typename T>
void generate_spp_address(network *net, T address_in[], T address_out[], const u8 &index);

template<typename T>
void swap_address(T address_in[], T address_out[], const u8 &index);

template<typename T>
void ps_Focus(network *net, T address_in[], T address_out[], const u8 &index, T weights, int weights_offset, T bias, int bias_offset);

template<typename T>
void ps_Conv(network *net, T address_in[], T address_out[], const u8 &index);

template<typename T>
void ps_C31(network *net, T address_in[], T address_out[], const u8 &index);

template<typename T>
void ps_c33(network *net, T address_in[], T address_out[], const u8 &index);

template<typename T>
void ps_SPP(network *net, T address_in[], T address_out[], const u8 &index);

template<typename T>
void ps_concat(network *net, T address_in[], T address_out[], const u8 &index);

template<typename T>
void ps_upsample(network *net, T address_in[], T address_out[], const u8 &index);

template<typename T>
void ps_detect(network *net, T address_in[], T address_out[], const u8 &index);

void top_conv(uint32_t ifm_in, uint32_t ofm_out, uint32_t weights, uint32_t bias,
              int ifm_ch, int ifm_h, int ifm_w, int ofm_ch, int ofm_h,
              int ofm_w, int I_CH, int I_H, int I_W, int O_CH, int O_H, int O_W,
              int ker_size, int stride, int padding, bool act_silu, int CNT,
              int ifm_q1, int ifm_q2, int weights_q, int bias_q,
              int ofm_q_before_act, int ofm_q_after_q);

void top_max(uint32_t ifm_in, uint32_t ofm_out, uint32_t weights, uint32_t bias,
              int ifm_ch, int ifm_h, int ifm_w, int ofm_ch, int ofm_h,
              int ofm_w, int I_CH, int I_H, int I_W, int O_CH, int O_H, int O_W,
              int ker_size, int stride, int padding, bool act_silu, int CNT,
              int ifm_q1, int ifm_q2, int weights_q, int bias_q,
              int ofm_q_before_act, int ofm_q_after_q);
// void top_conv(data_t *ifm_in, data_t *ofm_out, data_t *weights, data_t *bias,
//               int ifm_ch, int ifm_h, int ifm_w, int ofm_ch, int ofm_h,
//               int ofm_w, int I_CH, int I_H, int I_W, int O_CH, int O_H, int O_W,
//               int ker_size, int stride, int padding, bool act_silu, int CNT,
//               int ifm_q1, int ifm_q2, int weights_q, int bias_q,
//               int ofm_q_before_act, int ofm_q_after_q);

// void top_max(data_t *ifm_in, data_t *ofm_out, data_t *weights, data_t *bias,
//              int ifm_ch, int ifm_h, int ifm_w, int ofm_ch, int ofm_h, int ofm_w,
//              int I_CH, int I_H, int I_W, int O_CH, int O_H, int O_W,
//              int ker_size, int stride, int padding, bool act_silu, int CNT,
//              int ifm_q1, int ifm_q2, int weights_q, int bias_q,
//              int ofm_q_before_act, int ofm_q_after_q);

// template<typename T>
// void forward_shortcut(layer l, T address_in, T address_out);

// template<typename T>
// void forward_upsample(layer l, T *address_in, T *address_out);
// void forward_upsample(layer l, uint32_t address_in, uint32_t address_out, quan_t* a, quan_t* b);
void forward_yolo(layer l, float *address_in, float *result);

#endif //YOLOV5_SFT_PS_H
