#ifndef ACC_QUAN_H
#define ACC_QUAN_H

// #include <ap_fixed.h>
#include <assert.h>
// #include <hls_math.h>
#include <stdbool.h>
#include <stdint.h>
#include <cmath>
#define BIT_WIDTH 16
typedef short quan_t;
// typedef int quan2_t;
// typedef ap_fixed<16, 7> fixed_16_7_t;
// typedef ap_fixed<16, 10> fixed_16_10_t;
#define TN 4
#define TM 32
#define OTH 40
#define OTW 40
#define ITH 81
#define ITW 81
#define K 3
#define KK K *K
#define S 2
#define BIAS_MAX 512
#define WEIGHTS_LINE TM*TN*KK
// #define ONES fixed_16_7_t(1)
#define POOL_MIN_MN TN
#define MAX(x, y) (x > y) ? (x) : (y)
#define MIN(x, y) (x < y) ? (x) : (y)
#define ONCHIP_Q 20
#define IFM_PAD_LENGTH 640
const float int2fl_array[] = {0,
                              0.5,
                              0.25,
                              0.125,
                              0.0625,
                              0.03125,
                              0.015625,
                              0.0078125,
                              0.00390625,
                              0.001953125,
                              0.0009765625,
                              0.00048828125,
                              0.000244140625,
                              0.0001220703125,
                              6.103515625e-05,
                              3.0517578125e-05};
const float times[16] = {1,   2,   4,    8,    16,   32,   64,    128,
                         256, 512, 1024, 2048, 4096, 8192, 16384, 32768};

void top(quan_t *ifm_in, quan_t *ofm_out, quan_t *weights, quan_t *bias,
         uint16_t ifm_ch, uint16_t ifm_h, uint16_t ifm_w, uint16_t ofm_ch, uint16_t ofm_h, uint16_t ofm_w,
         uint8_t I_CH, uint8_t I_H, uint8_t I_W, uint8_t O_CH, uint8_t O_H, uint8_t O_W, uint8_t ker_size,
         uint8_t stride, uint8_t padding, uint8_t layer_type, bool act_silu, uint16_t CNT,
         uint8_t ifm_q1, uint8_t ifm_q2, uint8_t weights_q, uint8_t bias_q,
         uint8_t ofm_q_before_act, uint8_t ofm_q_after_q);
#endif