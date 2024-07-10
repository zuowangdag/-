#include "acc_quan.h"
#include <cstring>
void load_bias(quan_t *bias, quan_t bias_bf[BIAS_MAX], uint16_t ofm_ch,
               bool enable) {
  if (!enable) {
    return;
  }
  assert((ofm_ch > 0) && (ofm_ch <= BIAS_MAX));
  memcpy(bias_bf, bias, sizeof(quan_t)*ofm_ch);
  // for (uint16_t i = 0; i < ofm_ch; i++) {
  //   bias_bf[i] = bias[i];
  // }
}
void load_local_bias(quan_t global_bias_bf[BIAS_MAX], quan_t local_bias_bf[TM],
                     uint16_t och, uint8_t min_ofm_ch, bool enable) {
  if(!enable) {return;}
  assert((min_ofm_ch > 0) && (min_ofm_ch <= TM));
  assert((och + min_ofm_ch <= BIAS_MAX));
  for (uint8_t i = 0; i < min_ofm_ch; i++) {
    local_bias_bf[i] = global_bias_bf[och + i];
  }
}

void load_pp0(quan_t *inputs, quan_t line_buffer[ITW], uint8_t ichh, uint8_t hh, 
              uint16_t ifm_h, uint16_t ifm_w, uint8_t min_ifm_w, bool enable) {
#pragma HLS INLINE off
  if(!enable) {
    return;
  }
  assert((min_ifm_w > 0) && (min_ifm_w <= ITW));
  quan_t *inputs_addr = inputs + ichh * ifm_h * ifm_w + hh * ifm_w;
  memcpy(line_buffer, inputs_addr, sizeof(quan_t)*min_ifm_w);
}
void load_pp1(quan_t ibf[TN][ITH][ITW], quan_t line_buffer[ITW], uint8_t ichh, uint8_t hh, 
              uint8_t min_ifm_w, uint16_t ifm_h, uint16_t ifm_w, int16_t h_offset, 
              int16_t w_offset, bool ich_enable, quan_t pad_value, bool enable) {
#pragma HLS INLINE off
  if(!enable) {return;}
  assert((min_ifm_w > 0) && (min_ifm_w <= ITW));
  int16_t hoffset = h_offset + hh;
  bool henable = (hoffset < 0) || (hoffset >= ifm_h);
  bool out_enable = henable || ich_enable;
  for (uint8_t ww = 0; ww < min_ifm_w; ww++) {
    int16_t woffset = w_offset + ww;
    bool wenable = ((woffset < 0) || (woffset >= ifm_w));
    ibf[ichh][hh][ww] = (wenable || out_enable)
                          ? pad_value
                          : line_buffer[ww];
  }
}

void load_inputs(quan_t *ifm_in, quan_t ifm_bf[TN][ITH][ITW], uint16_t ich,
                 uint16_t ifm_ch, uint16_t oh, uint16_t ifm_h, uint16_t ow, uint16_t ifm_w,
                 uint8_t min_ifm_ch, uint8_t min_ifm_h, uint8_t min_ifm_w,
                 uint32_t IFM_FEATURE_MAPS, uint8_t stride, uint8_t pad, quan_t pad_value,
                 bool enable){
  if(!enable){return;}
  assert((min_ifm_h > 0) && (min_ifm_h <= ITH));
  assert((min_ifm_w > 0) && (min_ifm_w <= ITW));
  assert((min_ifm_ch > 0) && (min_ifm_ch <= TN));
  bool ich_enable = ((ich < 0) || (ich >= ifm_ch));
  int16_t h_offset = oh * stride - pad;
  int16_t w_offset = ow * stride - pad;
  quan_t *inputs =
      ifm_in + IFM_FEATURE_MAPS * ich + ifm_w * h_offset + w_offset;
  static quan_t line_buffer0[ITW];
  static quan_t line_buffer1[ITW];
  const uint16_t loop_cnts = min_ifm_ch * min_ifm_h;
  bool inputs_pp = false;
  uint8_t ichh = 0, hh = 0, ichh_next = 0, hh_next = 0;
  for (uint16_t loop0 = 0; loop0 < loop_cnts + 1; loop0++) {
    if(inputs_pp) {
      load_pp0(inputs, line_buffer0, ichh, hh, ifm_h, ifm_w, min_ifm_w, loop0 < loop_cnts);
      load_pp1(ifm_bf, line_buffer1, ichh_next, hh_next, min_ifm_w, ifm_h, ifm_w, h_offset, w_offset, ich_enable, pad_value, loop0 > 0);
      inputs_pp = false;
    } else {
      load_pp0(inputs, line_buffer1, ichh, hh, ifm_h, ifm_w, min_ifm_w, loop0 < loop_cnts);
      load_pp1(ifm_bf, line_buffer0, ichh_next, hh_next, min_ifm_w, ifm_h, ifm_w, h_offset, w_offset, ich_enable, pad_value, loop0 > 0);
      inputs_pp = true;
    }
    ichh_next = ichh;
    hh_next = hh;
    hh++;
    if(hh == min_ifm_h) {
      ichh++;
      hh = 0;
    }
  }
}

void load_weights(quan_t *weights, quan_t weights_bf[TM][TN][KK], uint16_t och,
                  uint16_t ich, uint16_t ifm_ch, uint8_t ker_size, uint8_t min_ofm_ch,
                  uint8_t min_ifm_ch, bool enable) {
  // #pragma DATA_FLOW
  if (!enable) {
    return;
  }
  static quan_t line_buffer[WEIGHTS_LINE];
  assert((min_ofm_ch > 0) && (min_ofm_ch <= TM));
  assert((min_ifm_ch > 0) && (min_ifm_ch <= TN));
  assert((ker_size > 0) && (ker_size <= K));

  uint8_t K2 = ker_size * ker_size;
  int cp_num = min_ofm_ch * min_ifm_ch * K2;
  static int offset;
  if ((och == 0) && (ich == 0)) {
    offset = 0;
  }
  quan_t *weights_addr = weights + offset;
  offset += cp_num;
  memcpy(line_buffer, weights_addr, sizeof(quan_t) * cp_num);
 int cnt = 0;
 for (uint8_t kk = 0; kk < K2; kk++) {
   for (uint8_t och = 0; och < TM; och++) {
     for (uint8_t ich = 0; ich < TN; ich++) {
       bool enable = (ich < min_ifm_ch) && (och < min_ofm_ch);
       weights_bf[och][ich][kk] = enable ? line_buffer[cnt++] : 0;
       // cnt = enable ? cnt+ 1 : cnt;
     }
   }
 }
  //  load_weight(weights_addr, line_buffer, weights_bf, cp_num, min_ofm_ch,
  //              min_ifm_ch, ker_size, K2);
}

void mul(quan_t ibf[TN][ITH][ITW], quan_t wbf[TM][TN][KK], int temp_mul[TM][TN],
         const int h_index, const int w_index, const uint8_t kk,
         const uint8_t mul_res_shift_q) {
  for (uint8_t ochh = 0; ochh < TM; ochh++) {
    for (uint8_t ichh = 0; ichh < TN; ichh++) {
      temp_mul[ochh][ichh] =
          (ibf[ichh][h_index][w_index] * wbf[ochh][ichh][kk]) >>
          (mul_res_shift_q);
    }
  }
}
void add(int temp_mul[TM][TN], int temp_add[TM]) {
  for (uint8_t ochh = 0; ochh < TM; ochh++) {
    for (uint8_t ichh = 0; ichh < TN; ichh++) {
      temp_add[ochh] = (ichh == 0) ? (temp_mul[ochh][ichh])
                                   : (temp_mul[ochh][ichh] + temp_add[ochh]);
    }
  }
}

void res(quan_t obf[TM][OTH][OTW], int temp_add[TM], quan_t bbf[TM],
         const uint16_t hh, const uint16_t ww, const uint8_t add_bias_shift_q,
         const uint8_t res_bias_shift, const bool enable) {
#pragma HLS DEPENDENCE false variable=obf
  for (uint8_t ochh = 0; ochh < TM; ochh++) {
    int temp_b = (bbf[ochh] << add_bias_shift_q);
    int temp = (obf[ochh][hh][ww] << res_bias_shift);
    obf[ochh][hh][ww] = (enable) ? ((temp_add[ochh] + temp_b) >> res_bias_shift)
                                 : ((temp_add[ochh] + temp) >> res_bias_shift);
  }
}

void kernel(quan_t ibf[TN][ITH][ITW], quan_t wbf[TM][TN][KK],
            int temp_mul[TM][TN], int temp_add[TM], quan_t bbf[TM],
            quan_t obf[TM][OTH][OTW], const uint16_t ich, const uint16_t hh, const uint16_t ww,
            const uint8_t k1, const uint8_t k2, const uint8_t kk, const uint8_t stride,
            const uint8_t mul_res_shift_q, const uint8_t add_bias_shift_q,
            const uint8_t res_bias_shift) {
  int h_index = hh * stride + k1;
  int w_index = ww * stride + k2;
  bool enable = ((k1 == 0) && (k2 == 0) && (ich == 0));
  mul(ibf, wbf, temp_mul, h_index, w_index, kk, mul_res_shift_q);
  add(temp_mul, temp_add);
  res(obf, temp_add, bbf, hh, ww, add_bias_shift_q, res_bias_shift, enable);
}

void compute0(quan_t ibf[TN][ITH][ITW], quan_t wbf[TM][TN][KK],
              quan_t obf[TM][OTH][OTW], quan_t bbf[TM], const uint16_t ifm_ch,
              const uint16_t ich, const uint8_t min_ifm_ch, const uint8_t min_ofm_ch,
              const uint8_t min_ofm_h, const uint8_t min_ofm_w, const uint8_t ker_size,
              const uint8_t stride, const uint8_t ifm_q1, const uint8_t ifm_q2,
              const uint8_t wbf_q, const uint8_t bbf_q, const uint8_t ofm_q_acc,
              bool enable) {
//#pragma HLS INLINE
  if (!enable) {
    return;
  }
  static int temp_mul[TM][TN];
#pragma HLS ARRAY_PARTITION variable=temp_mul dim=0
  static int temp_add[TM];
#pragma HLS ARRAY_PARTITION variable=temp_add dim=1
  assert((ker_size > 0) && (ker_size <= K));
  assert((min_ofm_ch > 0) && (min_ofm_ch <= TM));
  assert((min_ofm_h > 0) && (min_ofm_h <= OTH));
  assert((min_ofm_w > 0) && (min_ofm_w <= OTW));
  assert((min_ifm_ch > 0) && (min_ifm_ch <= TN));
  assert((stride > 0) && (stride <= BIT_WIDTH));
  assert((ifm_q1 >= 0) && (ifm_q1 <= BIT_WIDTH));
  assert((ifm_q2 >= 0) && (ifm_q2 <= BIT_WIDTH));
  assert((ofm_q_acc >= 0) && (ofm_q_acc <= BIT_WIDTH));
  uint8_t k22 = ker_size * ker_size;
  uint8_t min_ofm_h_1 = min_ofm_h - 1;
  uint8_t min_ofm_w_1 = min_ofm_w - 1;
  uint8_t k1 = 0;
  uint8_t k2 = 0;
  uint8_t ifm_q = (ich < (ifm_ch >> 1)) ? (ifm_q1) : (ifm_q2);
  uint8_t mul_res_shift_q = ifm_q + wbf_q - ONCHIP_Q;
  uint8_t add_bias_shift_q = ONCHIP_Q - bbf_q;
  uint8_t res_bias_shift = ONCHIP_Q - ofm_q_acc;
  assert((k22 > 0) && (k22 <= KK));
  for (uint8_t kk = 0; kk < k22; kk++) {
    for (uint8_t hh = 0; hh < min_ofm_h; hh++) {
      for (uint8_t ww = 0; ww < min_ofm_w; ww++) {
#pragma HLS PIPELINE II=1
        kernel(ibf, wbf, temp_mul, temp_add, bbf, obf, ich, hh, ww, k1, k2, kk,
               stride, mul_res_shift_q, add_bias_shift_q, res_bias_shift);
        if ((hh == min_ofm_h_1) && (ww == min_ofm_w_1)) {
          k2++;
          if (k2 == ker_size) {
            k1++;
            k2 = 0;
            if (k1 == ker_size) {
              k1 = 0;
            }
          }
        }
      }
    }
  }
}

void compute_max(quan_t ibf[TN][ITH][ITW], quan_t obf[TM][OTH][OTW],
                  const uint8_t min_ofm_h, const uint8_t min_ofm_w, const uint8_t ker_size,
                  bool enable) {
  if (!enable) {
    return;
  }
  static quan_t temp[POOL_MIN_MN];
#pragma HLS ARRAY_PARTITION variable=temp dim=0
  assert((min_ofm_h > 0) && (min_ofm_h <= 20));
  assert((min_ofm_w > 0) && (min_ofm_w <= 20));
  assert((ker_size > 0) && (ker_size <= 20));
  for (uint8_t hh = 0; hh < min_ofm_h; hh++) {
    for (uint8_t ww = 0; ww < min_ofm_w; ww++) {
      for (uint8_t k1 = 0; k1 < ker_size; k1++) {
        for (uint8_t k2 = 0; k2 < ker_size; k2++) {
#pragma HLS PIPELINE II=1
          for (uint8_t ch = 0; ch < POOL_MIN_MN; ch++) {
#pragma HLS DEPENDENCE false variable=temp
            quan_t a = temp[ch];
            quan_t b = ibf[ch][hh + k1][ww + k2];
            if ((k1 == 0) && (k2 == 0)) {
              temp[ch] = b;
            } else {
              temp[ch] = MAX(a, b);
            }
            if ((k1 == ker_size - 1) && (k2 == ker_size - 1)) {
              obf[ch][hh][ww] = temp[ch];
            }
          }
        }
      }
    }
  }
}

void act_silu_func(quan_t obf[TM][OTH][OTW], const uint8_t min_ofm_ch,
              const uint8_t min_ofm_h, const uint8_t min_ofm_w, const float t1,
              const uint16_t t2, uint8_t shift_res, bool enable) {
  static quan_t temp_bf[TM];
  assert((min_ofm_w>0)&&(min_ofm_w<=OTW));
  assert((min_ofm_ch>0)&&(min_ofm_ch<=TM));
  assert((min_ofm_h>0)&&(min_ofm_h<=OTH));
  if (enable) {
    for (uint8_t hh = 0; hh < min_ofm_h; hh++) {
      for (uint8_t ww = 0; ww < min_ofm_w; ww++) {
        for (uint8_t ochh = 0; ochh < TM; ochh++) {
#pragma HLS DEPENDENCE false variable=obf
#pragma HLS UNROLL factor=4
          temp_bf[ochh] = obf[ochh][hh][ww];
          float a_float = temp_bf[ochh] * t1;
          float a_silu = a_float / (1 + expf(-a_float));
          obf[ochh][hh][ww] = a_silu * t2;
        }
      }
    }
  } else {
    for (uint8_t hh = 0; hh < min_ofm_h; hh++) {
      for (uint8_t ww = 0; ww < min_ofm_w; ww++) {
        for (uint8_t ochh = 0; ochh < TM; ochh++) {
#pragma HLS DEPENDENCE false variable=obf
#pragma HLS UNROLL
          temp_bf[ochh] = (obf[ochh][hh][ww] >> shift_res);
          obf[ochh][hh][ww] = temp_bf[ochh];
        }
      }
    }
  }
}

void save_pp0(quan_t obf[TM][OTH][OTW], quan_t line_buffer[OTW], uint8_t ochh, uint8_t hh, 
              uint8_t min_ofm_w, bool enable) {
  #pragma HLS inline off
  if(!enable) {
    return;
  }
  assert((min_ofm_w > 0) && (min_ofm_w <= OTW));
  for(uint8_t ww = 0; ww < min_ofm_w; ww++) {
    line_buffer[ww] = obf[ochh][hh][ww];
  }
}
void save_pp1(quan_t *ofm_out, quan_t line_buffer[OTW], uint8_t ochh, uint8_t hh, uint8_t min_ofm_w, uint16_t ofm_h, uint16_t ofm_w, bool enable) {
  #pragma HLS inline off
  if(!enable) {return;}
  assert((min_ofm_w > 0) && (min_ofm_w <= OTW));
  quan_t *ofm_addr = ofm_out + ochh * ofm_h * ofm_w + hh * ofm_w;
  memcpy(ofm_addr, line_buffer, sizeof(quan_t) * min_ofm_w);
}
void save0(quan_t *ofm_out, quan_t obf[TM][OTH][OTW], const int och,
           const int h, const int w, const uint8_t min_ofm_ch, const uint8_t min_ofm_h,
           const uint8_t min_ofm_w, const int ofm_h, const int ofm_w, bool enable) {
  if(!enable) {return;}
  assert((min_ofm_ch>0)&&(min_ofm_ch<=TM));
  assert((min_ofm_h>0)&&(min_ofm_h<=OTH));
  assert((min_ofm_w>0)&&(min_ofm_w<=OTW));
  quan_t *out_index = ofm_out + och * ofm_h * ofm_w + h * ofm_w + w;
  static quan_t line_buffer0[OTW];
  static quan_t line_buffer1[OTW];
  uint16_t cnt_loops = min_ofm_ch * min_ofm_h;
  uint8_t ochh = 0, hh = 0;
  uint8_t ochh_next, hh_next;
  bool save0_pp = false;
  for (uint16_t loops1 = 0; loops1 < cnt_loops + 1; loops1++) {
    if(save0_pp) {
      save_pp0(obf, line_buffer0, ochh, hh, min_ofm_w, loops1 < cnt_loops);
      save_pp1(out_index, line_buffer1, ochh_next, hh_next, min_ofm_w,ofm_h,ofm_w,loops1 > 0);
      save0_pp = false;
    } else {
      save_pp0(obf, line_buffer1, ochh, hh, min_ofm_w, loops1 < cnt_loops);
      save_pp1(out_index, line_buffer0, ochh_next, hh_next, min_ofm_w,ofm_h,ofm_w,loops1 > 0);
      save0_pp = true;
    }
    ochh_next = ochh;
    hh_next = hh;
    hh++;
    if(hh == min_ofm_h) {
      hh = 0;
      ochh++;
    }
  } 
}

void compute_save0(quan_t obf[TM][OTH][OTW], quan_t *ofm_out, const uint16_t h,
                   const uint16_t w, const uint16_t och, const uint8_t min_ofm_h,
                   const uint8_t min_ofm_w, const uint8_t min_ofm_ch, const uint16_t ofm_h,
                   const uint16_t ofm_w, const uint8_t ofm_q_before_act,
                   const uint8_t ofm_q_after_act, bool silu_act, bool enable) {
#pragma HLS INLINE off
  if (!enable) {
    return;
  }
  act_silu_func(obf, min_ofm_ch, min_ofm_h, min_ofm_w, int2fl_array[ofm_q_before_act],
           times[ofm_q_after_act], ofm_q_before_act - ofm_q_after_act,
           silu_act);
  save0(ofm_out, obf, och, h, w, min_ofm_ch, min_ofm_h, min_ofm_w, ofm_h, ofm_w,
        true);
}

void load_compute1(quan_t *ifm_in, quan_t *weights, quan_t ibf0[TN][ITH][ITW],
                   quan_t ibf1[TN][ITH][ITW], quan_t obf[TM][OTH][OTW],
                   quan_t bbf[TM], uint16_t ifm_ch, uint16_t ifm_h,
                   uint16_t ifm_w, uint16_t och, uint16_t oh, uint16_t ow,
                   uint8_t min_ifm_h, uint8_t min_ifm_w, uint8_t s, uint8_t p,
                   uint8_t k, uint8_t min_ofm_ch, uint8_t min_ofm_h,
                   uint8_t min_ofm_w, uint8_t min_ofm_ch_next_out[1],
                   uint8_t min_ofm_h_next_out[1], uint8_t min_ofm_w_next_out[1],
                   uint16_t och_next_out[1], uint16_t oh_next_out[1],
                   uint16_t ow_next_out[1], uint8_t I_CH, uint8_t layertype,
                   uint8_t ifm_q1, uint8_t ifm_q2, uint8_t wbf_q, uint8_t bbf_q,
                   uint8_t ofm_q_acc, bool top_pp0, bool max_enable,
                   bool enable) {
#pragma HLS inline off
  static quan_t wbf0[TM][TN][KK];
#pragma HLS ARRAY_PARTITION variable=wbf0 dim=1
#pragma HLS ARRAY_PARTITION variable=wbf0 dim=2
  static quan_t wbf1[TM][TN][KK];
#pragma HLS ARRAY_PARTITION variable=wbf1 dim=1
#pragma HLS ARRAY_PARTITION variable=wbf1 dim=2
  static uint8_t min_ofm_h_next, min_ofm_w_next, min_ofm_ch_next;
  static uint8_t och_next, oh_next, ow_next;
  if (layertype == 0) {
    if (!enable) {
      return;
    }
    bool top_pp1 = false;
    uint16_t ich_next;
    uint8_t min_ifm_ch, min_ifm_ch_next;
    for (uint16_t ich = 0; ich < ifm_ch + I_CH; ich += I_CH) {
      min_ifm_ch = MIN(I_CH, ifm_ch - ich);
      if (top_pp1) {
        load_inputs(ifm_in, ibf0, ich, ifm_ch, oh, ifm_h, ow, ifm_w,
                        min_ifm_ch, min_ifm_h, min_ifm_w, ifm_h * ifm_w, s, p,
                        0x00, ich < ifm_ch);
        load_weights(weights, wbf0, och, ich, ifm_ch, k, min_ofm_ch, min_ifm_ch,
                     ich < ifm_ch);
        compute0(ibf1, wbf1, obf, bbf, ifm_ch, ich_next, min_ifm_ch_next,
                 min_ofm_ch, min_ofm_h, min_ofm_w, k, s, ifm_q1, ifm_q2, wbf_q,
                 bbf_q, ofm_q_acc, ich > 0);
        top_pp1 = false;
      } else {
        load_inputs(ifm_in, ibf1, ich, ifm_ch, oh, ifm_h, ow, ifm_w,
                        min_ifm_ch, min_ifm_h, min_ifm_w, ifm_h * ifm_w, s, p,
                        0x00, ich < ifm_ch);
        load_weights(weights, wbf1, och, ich, ifm_ch, k, min_ofm_ch, min_ifm_ch,
                     ich < ifm_ch);
        compute0(ibf0, wbf0, obf, bbf, ifm_ch, ich_next, min_ifm_ch_next,
                 min_ofm_ch, min_ofm_h, min_ofm_w, k, s, ifm_q1, ifm_q2, wbf_q,
                 bbf_q, ofm_q_acc, ich > 0);
        top_pp1 = true;
      }
      min_ifm_ch_next = min_ifm_ch;
      ich_next = ich;
    }
    min_ofm_ch_next_out[0] = min_ofm_ch;
    min_ofm_h_next_out[0] = min_ofm_h;
    min_ofm_w_next_out[0] = min_ofm_w;
    och_next_out[0] = och;
    oh_next_out[0] = oh;
    ow_next_out[0] = ow;
  } else if (layertype == 1) {
    if(top_pp0) {
      load_inputs(ifm_in, ibf0, och, ifm_ch, oh, ifm_h, ow, ifm_w, min_ofm_ch,
                      min_ifm_h, min_ifm_w, ifm_h * ifm_w, s, p, 0x8000, enable);
      compute_max(ibf1, obf, min_ofm_h_next, min_ofm_w_next, k, max_enable);
    } else {
      load_inputs(ifm_in, ibf1, och, ifm_ch, oh, ifm_h, ow, ifm_w, min_ofm_ch,
                      min_ifm_h, min_ifm_w, ifm_h * ifm_w, s, p, 0x8000, enable);
      compute_max(ibf0, obf, min_ofm_h_next, min_ofm_w_next, k, max_enable);
    }
    min_ofm_ch_next_out[0] = min_ofm_ch_next;
    min_ofm_h_next_out[0] = min_ofm_h_next;
    min_ofm_w_next_out[0] = min_ofm_w_next;
    min_ofm_ch_next = min_ofm_ch;
    min_ofm_h_next = min_ofm_h;
    min_ofm_w_next = min_ofm_w;
    och_next_out[0] = och_next;
    oh_next_out[0] = oh_next;
    ow_next_out[0] = ow_next;
    och_next = och;
    oh_next = oh;
    ow_next = ow;
  }
}

void top(quan_t *ifm, quan_t *ofm, quan_t *weights, quan_t *bias,
         uint16_t ifm_ch, uint16_t ifm_h, uint16_t ifm_w, uint16_t ofm_ch,
         uint16_t ofm_h, uint16_t ofm_w, uint8_t I_CH, uint8_t I_H, uint8_t I_W,
         uint8_t O_CH, uint8_t O_H, uint8_t O_W, uint8_t ker_size,
         uint8_t stride, uint8_t padding, uint8_t layer_type, bool act_silu,
         uint16_t CNT, uint8_t ifm_q1, uint8_t ifm_q2, uint8_t weights_q,
         uint8_t bias_q, uint8_t ofm_q_before_act, uint8_t ofm_q_after_q) {
#pragma HLS INTERFACE s_axilite port=return bundle=ctrl register
#pragma HLS INTERFACE m_axi num_write_outstanding=2 num_read_outstanding=2 max_write_burst_length=128 max_widen_bitwidth=32 max_read_burst_length=128 depth=3277440 bundle=ifm port=ifm offset=slave
#pragma HLS INTERFACE m_axi num_write_outstanding=2 num_read_outstanding=2 max_write_burst_length=128 max_widen_bitwidth=32 max_read_burst_length=128 depth=3277440 bundle=ofm port=ofm offset=slave
#pragma HLS INTERFACE m_axi num_write_outstanding=2 num_read_outstanding=2 max_write_burst_length=256 max_widen_bitwidth=32 max_read_burst_length=256 depth=1179648 bundle=weights port=weights offset=slave
#pragma HLS INTERFACE m_axi num_write_outstanding=2 num_read_outstanding=2 max_write_burst_length=256 max_widen_bitwidth=32 max_read_burst_length=256 depth=512 bundle=bias port=bias offset=slave
#pragma HLS INTERFACE s_axilite port=ifm bundle=ctrl register
#pragma HLS INTERFACE s_axilite port=ofm bundle=ctrl register
#pragma HLS INTERFACE s_axilite port=weights bundle=ctrl register
#pragma HLS INTERFACE s_axilite port=bias bundle=ctrl register
#pragma HLS INTERFACE s_axilite port=ifm_ch bundle=ctrl register
#pragma HLS INTERFACE s_axilite port=ifm_h bundle=ctrl register
#pragma HLS INTERFACE s_axilite port=ifm_w bundle=ctrl register
#pragma HLS INTERFACE s_axilite port=ofm_ch bundle=ctrl register
#pragma HLS INTERFACE s_axilite port=ofm_h bundle=ctrl register
#pragma HLS INTERFACE s_axilite port=ofm_w bundle=ctrl register
#pragma HLS INTERFACE s_axilite port=I_CH bundle=ctrl register
#pragma HLS INTERFACE s_axilite port=I_H bundle=ctrl register
#pragma HLS INTERFACE s_axilite port=I_W bundle=ctrl register
#pragma HLS INTERFACE s_axilite port=O_CH bundle=ctrl register
#pragma HLS INTERFACE s_axilite port=O_H bundle=ctrl register
#pragma HLS INTERFACE s_axilite port=O_W bundle=ctrl register
#pragma HLS INTERFACE s_axilite port=ker_size bundle=ctrl register
#pragma HLS INTERFACE s_axilite port=stride bundle=ctrl register
#pragma HLS INTERFACE s_axilite port=padding bundle=ctrl register
#pragma HLS INTERFACE s_axilite port=layer_type bundle=ctrl register
#pragma HLS INTERFACE s_axilite port=act_silu bundle=ctrl register
#pragma HLS INTERFACE s_axilite port=CNT bundle=ctrl register
#pragma HLS INTERFACE s_axilite port=ifm_q1 bundle=ctrl register
#pragma HLS INTERFACE s_axilite port=ifm_q2 bundle=ctrl register
#pragma HLS INTERFACE s_axilite port=weights_q bundle=ctrl register
#pragma HLS INTERFACE s_axilite port=bias_q bundle=ctrl register
#pragma HLS INTERFACE s_axilite port=ofm_q_before_act bundle=ctrl register
#pragma HLS INTERFACE s_axilite port=ofm_q_after_q bundle=ctrl register

  uint32_t IFM_FEATURE_MAPS = ifm_h * ifm_w;
  uint32_t OFM_FEATURE_MAPS = ofm_h * ofm_w;

  static quan_t global_bias_bf[BIAS_MAX];
  static quan_t local_bias_bf[TM];
#pragma HLS ARRAY_PARTITION variable=local_bias_bf dim=1
  static quan_t ifm_bf0[TN][ITH][ITW];
#pragma HLS ARRAY_PARTITION variable=ifm_bf0 dim=1
  static quan_t ifm_bf1[TN][ITH][ITW];
#pragma HLS ARRAY_PARTITION variable=ifm_bf1 dim=1
  static quan_t ofm_bf0[TM][OTH][OTW];
#pragma HLS ARRAY_PARTITION variable=ofm_bf0 dim=1
  static quan_t ofm_bf1[TM][OTH][OTW];
#pragma HLS ARRAY_PARTITION variable=ofm_bf1 dim=1
// ifm = ifm + IFM_PAD_LENGTH;
// ofm = ofm + IFM_PAD_LENGTH;
  load_bias(bias, global_bias_bf, ofm_ch, layer_type == 0);
  const uint16_t ifm_ch_plus_ICH = ifm_ch + I_CH;
  uint8_t min_ofm_ch, min_ofm_h, min_ofm_w;
  uint8_t min_ofm_ch_next, min_ofm_h_next, min_ofm_w_next;
  uint16_t och_next, oh_next, ow_next;
  uint8_t min_ifm_ch, min_ifm_h, min_ifm_w;
  uint16_t och = 0, oh = 0, ow = 0;

  uint16_t och_next0, oh_next0, ow_next0;
  uint16_t och_next1, oh_next1, ow_next1;
  uint8_t min_ofm_ch_next0, min_ofm_h_next0, min_ofm_w_next0;
  uint8_t min_ofm_ch_next1, min_ofm_h_next1, min_ofm_w_next1;

  bool load_enable, save_enable, max_enable;
  bool top_pp0 = false;
  for (int cnt = 0; cnt < CNT + 1; cnt++) {
    min_ofm_ch = MIN(O_CH, ofm_ch - och);
    min_ofm_h = MIN(O_H, ofm_h - oh);
    min_ofm_w = MIN(O_W, ofm_w - ow);
    load_enable = (layer_type == 0) ? (cnt < CNT) : (cnt < CNT - 1);
    save_enable = (layer_type == 0) ? (cnt > 0) : (cnt > 1);
    max_enable = (cnt > 0) && (cnt < CNT);
    min_ifm_h = MIN(I_H, (min_ofm_h - 1) * stride + ker_size);
    min_ifm_w = MIN(I_W, (min_ofm_w - 1) * stride + ker_size);
      load_local_bias(global_bias_bf, local_bias_bf, och, min_ofm_ch, layer_type==0);
      if(top_pp0) {
        load_compute1(ifm, weights, ifm_bf0, ifm_bf1, ofm_bf0, local_bias_bf,
                      ifm_ch, ifm_h, ifm_w, och, oh, ow, min_ifm_h, min_ifm_w,
                      stride, padding, ker_size, min_ofm_ch, min_ofm_h,
                      min_ofm_w, &min_ofm_ch_next0, &min_ofm_h_next0,
                      &min_ofm_w_next0, &och_next0, &oh_next0, &ow_next0, I_CH,
                      layer_type, ifm_q1, ifm_q2, weights_q, bias_q,
                      ofm_q_before_act, top_pp0, max_enable, load_enable);
        compute_save0(ofm_bf1, ofm, oh_next1, ow_next1, och_next1,
                      min_ofm_h_next1, min_ofm_w_next1, min_ofm_ch_next1, ofm_h,
                      ofm_w, ofm_q_before_act, ofm_q_after_q, act_silu,
                      save_enable);
        
        top_pp0 = false;
      } else {
        load_compute1(ifm, weights, ifm_bf0, ifm_bf1, ofm_bf1, local_bias_bf,
                      ifm_ch, ifm_h, ifm_w, och, oh, ow, min_ifm_h, min_ifm_w,
                      stride, padding, ker_size, min_ofm_ch, min_ofm_h,
                      min_ofm_w, &min_ofm_ch_next1, &min_ofm_h_next1,
                      &min_ofm_w_next1, &och_next1, &oh_next1, &ow_next1, I_CH,
                      layer_type, ifm_q1, ifm_q2, weights_q, bias_q,
                      ofm_q_before_act, top_pp0, max_enable, load_enable);
        compute_save0(ofm_bf0, ofm, oh_next0, ow_next0, och_next0,
                      min_ofm_h_next0, min_ofm_w_next0, min_ofm_ch_next0, ofm_h,
                      ofm_w, ofm_q_before_act, ofm_q_after_q, act_silu,
                      save_enable);
        top_pp0 = true;
      }
    och += ((layer_type == 0) ? (O_CH) : (POOL_MIN_MN));
    if (och >= ofm_ch) {
      och = 0;
      ow += O_W;
      if (ow >= ofm_w) {
        ow = 0;
        oh += O_H;
        if(oh >= ofm_h){
          oh=0;
        }
      }
    }
  }
}
