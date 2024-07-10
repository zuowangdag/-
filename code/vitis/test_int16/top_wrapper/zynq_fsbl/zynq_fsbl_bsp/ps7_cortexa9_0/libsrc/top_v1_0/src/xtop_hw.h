// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// ctrl
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read)
//        bit 7  - auto_restart (Read/Write)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0  - enable ap_done interrupt (Read/Write)
//        bit 1  - enable ap_ready interrupt (Read/Write)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0  - ap_done (COR/TOW)
//        bit 1  - ap_ready (COR/TOW)
//        others - reserved
// 0x10 : Data signal of ifm_offset
//        bit 31~0 - ifm_offset[31:0] (Read/Write)
// 0x14 : reserved
// 0x18 : Data signal of ofm_offset
//        bit 31~0 - ofm_offset[31:0] (Read/Write)
// 0x1c : reserved
// 0x20 : Data signal of weights_offset
//        bit 31~0 - weights_offset[31:0] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of bias_offset
//        bit 31~0 - bias_offset[31:0] (Read/Write)
// 0x2c : reserved
// 0x30 : Data signal of ifm_ch
//        bit 15~0 - ifm_ch[15:0] (Read/Write)
//        others   - reserved
// 0x34 : reserved
// 0x38 : Data signal of ifm_h
//        bit 15~0 - ifm_h[15:0] (Read/Write)
//        others   - reserved
// 0x3c : reserved
// 0x40 : Data signal of ifm_w
//        bit 15~0 - ifm_w[15:0] (Read/Write)
//        others   - reserved
// 0x44 : reserved
// 0x48 : Data signal of ofm_ch
//        bit 15~0 - ofm_ch[15:0] (Read/Write)
//        others   - reserved
// 0x4c : reserved
// 0x50 : Data signal of ofm_h
//        bit 15~0 - ofm_h[15:0] (Read/Write)
//        others   - reserved
// 0x54 : reserved
// 0x58 : Data signal of ofm_w
//        bit 15~0 - ofm_w[15:0] (Read/Write)
//        others   - reserved
// 0x5c : reserved
// 0x60 : Data signal of I_CH
//        bit 7~0 - I_CH[7:0] (Read/Write)
//        others  - reserved
// 0x64 : reserved
// 0x68 : Data signal of I_H
//        bit 7~0 - I_H[7:0] (Read/Write)
//        others  - reserved
// 0x6c : reserved
// 0x70 : Data signal of I_W
//        bit 7~0 - I_W[7:0] (Read/Write)
//        others  - reserved
// 0x74 : reserved
// 0x78 : Data signal of O_CH
//        bit 7~0 - O_CH[7:0] (Read/Write)
//        others  - reserved
// 0x7c : reserved
// 0x80 : Data signal of O_H
//        bit 7~0 - O_H[7:0] (Read/Write)
//        others  - reserved
// 0x84 : reserved
// 0x88 : Data signal of O_W
//        bit 7~0 - O_W[7:0] (Read/Write)
//        others  - reserved
// 0x8c : reserved
// 0x90 : Data signal of ker_size
//        bit 7~0 - ker_size[7:0] (Read/Write)
//        others  - reserved
// 0x94 : reserved
// 0x98 : Data signal of stride
//        bit 7~0 - stride[7:0] (Read/Write)
//        others  - reserved
// 0x9c : reserved
// 0xa0 : Data signal of padding
//        bit 7~0 - padding[7:0] (Read/Write)
//        others  - reserved
// 0xa4 : reserved
// 0xa8 : Data signal of layer_type
//        bit 7~0 - layer_type[7:0] (Read/Write)
//        others  - reserved
// 0xac : reserved
// 0xb0 : Data signal of act_silu
//        bit 0  - act_silu[0] (Read/Write)
//        others - reserved
// 0xb4 : reserved
// 0xb8 : Data signal of CNT
//        bit 15~0 - CNT[15:0] (Read/Write)
//        others   - reserved
// 0xbc : reserved
// 0xc0 : Data signal of ifm_q1
//        bit 7~0 - ifm_q1[7:0] (Read/Write)
//        others  - reserved
// 0xc4 : reserved
// 0xc8 : Data signal of ifm_q2
//        bit 7~0 - ifm_q2[7:0] (Read/Write)
//        others  - reserved
// 0xcc : reserved
// 0xd0 : Data signal of weights_q
//        bit 7~0 - weights_q[7:0] (Read/Write)
//        others  - reserved
// 0xd4 : reserved
// 0xd8 : Data signal of bias_q
//        bit 7~0 - bias_q[7:0] (Read/Write)
//        others  - reserved
// 0xdc : reserved
// 0xe0 : Data signal of ofm_q_before_act
//        bit 7~0 - ofm_q_before_act[7:0] (Read/Write)
//        others  - reserved
// 0xe4 : reserved
// 0xe8 : Data signal of ofm_q_after_q
//        bit 7~0 - ofm_q_after_q[7:0] (Read/Write)
//        others  - reserved
// 0xec : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XTOP_CTRL_ADDR_AP_CTRL               0x00
#define XTOP_CTRL_ADDR_GIE                   0x04
#define XTOP_CTRL_ADDR_IER                   0x08
#define XTOP_CTRL_ADDR_ISR                   0x0c
#define XTOP_CTRL_ADDR_IFM_OFFSET_DATA       0x10
#define XTOP_CTRL_BITS_IFM_OFFSET_DATA       32
#define XTOP_CTRL_ADDR_OFM_OFFSET_DATA       0x18
#define XTOP_CTRL_BITS_OFM_OFFSET_DATA       32
#define XTOP_CTRL_ADDR_WEIGHTS_OFFSET_DATA   0x20
#define XTOP_CTRL_BITS_WEIGHTS_OFFSET_DATA   32
#define XTOP_CTRL_ADDR_BIAS_OFFSET_DATA      0x28
#define XTOP_CTRL_BITS_BIAS_OFFSET_DATA      32
#define XTOP_CTRL_ADDR_IFM_CH_DATA           0x30
#define XTOP_CTRL_BITS_IFM_CH_DATA           16
#define XTOP_CTRL_ADDR_IFM_H_DATA            0x38
#define XTOP_CTRL_BITS_IFM_H_DATA            16
#define XTOP_CTRL_ADDR_IFM_W_DATA            0x40
#define XTOP_CTRL_BITS_IFM_W_DATA            16
#define XTOP_CTRL_ADDR_OFM_CH_DATA           0x48
#define XTOP_CTRL_BITS_OFM_CH_DATA           16
#define XTOP_CTRL_ADDR_OFM_H_DATA            0x50
#define XTOP_CTRL_BITS_OFM_H_DATA            16
#define XTOP_CTRL_ADDR_OFM_W_DATA            0x58
#define XTOP_CTRL_BITS_OFM_W_DATA            16
#define XTOP_CTRL_ADDR_I_CH_DATA             0x60
#define XTOP_CTRL_BITS_I_CH_DATA             8
#define XTOP_CTRL_ADDR_I_H_DATA              0x68
#define XTOP_CTRL_BITS_I_H_DATA              8
#define XTOP_CTRL_ADDR_I_W_DATA              0x70
#define XTOP_CTRL_BITS_I_W_DATA              8
#define XTOP_CTRL_ADDR_O_CH_DATA             0x78
#define XTOP_CTRL_BITS_O_CH_DATA             8
#define XTOP_CTRL_ADDR_O_H_DATA              0x80
#define XTOP_CTRL_BITS_O_H_DATA              8
#define XTOP_CTRL_ADDR_O_W_DATA              0x88
#define XTOP_CTRL_BITS_O_W_DATA              8
#define XTOP_CTRL_ADDR_KER_SIZE_DATA         0x90
#define XTOP_CTRL_BITS_KER_SIZE_DATA         8
#define XTOP_CTRL_ADDR_STRIDE_DATA           0x98
#define XTOP_CTRL_BITS_STRIDE_DATA           8
#define XTOP_CTRL_ADDR_PADDING_DATA          0xa0
#define XTOP_CTRL_BITS_PADDING_DATA          8
#define XTOP_CTRL_ADDR_LAYER_TYPE_DATA       0xa8
#define XTOP_CTRL_BITS_LAYER_TYPE_DATA       8
#define XTOP_CTRL_ADDR_ACT_SILU_DATA         0xb0
#define XTOP_CTRL_BITS_ACT_SILU_DATA         1
#define XTOP_CTRL_ADDR_CNT_DATA              0xb8
#define XTOP_CTRL_BITS_CNT_DATA              16
#define XTOP_CTRL_ADDR_IFM_Q1_DATA           0xc0
#define XTOP_CTRL_BITS_IFM_Q1_DATA           8
#define XTOP_CTRL_ADDR_IFM_Q2_DATA           0xc8
#define XTOP_CTRL_BITS_IFM_Q2_DATA           8
#define XTOP_CTRL_ADDR_WEIGHTS_Q_DATA        0xd0
#define XTOP_CTRL_BITS_WEIGHTS_Q_DATA        8
#define XTOP_CTRL_ADDR_BIAS_Q_DATA           0xd8
#define XTOP_CTRL_BITS_BIAS_Q_DATA           8
#define XTOP_CTRL_ADDR_OFM_Q_BEFORE_ACT_DATA 0xe0
#define XTOP_CTRL_BITS_OFM_Q_BEFORE_ACT_DATA 8
#define XTOP_CTRL_ADDR_OFM_Q_AFTER_Q_DATA    0xe8
#define XTOP_CTRL_BITS_OFM_Q_AFTER_Q_DATA    8

