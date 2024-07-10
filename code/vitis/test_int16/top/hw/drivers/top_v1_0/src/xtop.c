// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xtop.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XTop_CfgInitialize(XTop *InstancePtr, XTop_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Ctrl_BaseAddress = ConfigPtr->Ctrl_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XTop_Start(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_AP_CTRL) & 0x80;
    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XTop_IsDone(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XTop_IsIdle(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XTop_IsReady(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XTop_EnableAutoRestart(XTop *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_AP_CTRL, 0x80);
}

void XTop_DisableAutoRestart(XTop *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_AP_CTRL, 0);
}

void XTop_Set_ifm_offset(XTop *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_IFM_OFFSET_DATA, Data);
}

u32 XTop_Get_ifm_offset(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_IFM_OFFSET_DATA);
    return Data;
}

void XTop_Set_ofm_offset(XTop *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_OFM_OFFSET_DATA, Data);
}

u32 XTop_Get_ofm_offset(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_OFM_OFFSET_DATA);
    return Data;
}

void XTop_Set_weights_offset(XTop *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_WEIGHTS_OFFSET_DATA, Data);
}

u32 XTop_Get_weights_offset(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_WEIGHTS_OFFSET_DATA);
    return Data;
}

void XTop_Set_bias_offset(XTop *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_BIAS_OFFSET_DATA, Data);
}

u32 XTop_Get_bias_offset(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_BIAS_OFFSET_DATA);
    return Data;
}

void XTop_Set_ifm_ch(XTop *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_IFM_CH_DATA, Data);
}

u32 XTop_Get_ifm_ch(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_IFM_CH_DATA);
    return Data;
}

void XTop_Set_ifm_h(XTop *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_IFM_H_DATA, Data);
}

u32 XTop_Get_ifm_h(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_IFM_H_DATA);
    return Data;
}

void XTop_Set_ifm_w(XTop *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_IFM_W_DATA, Data);
}

u32 XTop_Get_ifm_w(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_IFM_W_DATA);
    return Data;
}

void XTop_Set_ofm_ch(XTop *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_OFM_CH_DATA, Data);
}

u32 XTop_Get_ofm_ch(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_OFM_CH_DATA);
    return Data;
}

void XTop_Set_ofm_h(XTop *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_OFM_H_DATA, Data);
}

u32 XTop_Get_ofm_h(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_OFM_H_DATA);
    return Data;
}

void XTop_Set_ofm_w(XTop *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_OFM_W_DATA, Data);
}

u32 XTop_Get_ofm_w(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_OFM_W_DATA);
    return Data;
}

void XTop_Set_I_CH(XTop *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_I_CH_DATA, Data);
}

u32 XTop_Get_I_CH(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_I_CH_DATA);
    return Data;
}

void XTop_Set_I_H(XTop *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_I_H_DATA, Data);
}

u32 XTop_Get_I_H(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_I_H_DATA);
    return Data;
}

void XTop_Set_I_W(XTop *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_I_W_DATA, Data);
}

u32 XTop_Get_I_W(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_I_W_DATA);
    return Data;
}

void XTop_Set_O_CH(XTop *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_O_CH_DATA, Data);
}

u32 XTop_Get_O_CH(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_O_CH_DATA);
    return Data;
}

void XTop_Set_O_H(XTop *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_O_H_DATA, Data);
}

u32 XTop_Get_O_H(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_O_H_DATA);
    return Data;
}

void XTop_Set_O_W(XTop *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_O_W_DATA, Data);
}

u32 XTop_Get_O_W(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_O_W_DATA);
    return Data;
}

void XTop_Set_ker_size(XTop *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_KER_SIZE_DATA, Data);
}

u32 XTop_Get_ker_size(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_KER_SIZE_DATA);
    return Data;
}

void XTop_Set_stride(XTop *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_STRIDE_DATA, Data);
}

u32 XTop_Get_stride(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_STRIDE_DATA);
    return Data;
}

void XTop_Set_padding(XTop *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_PADDING_DATA, Data);
}

u32 XTop_Get_padding(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_PADDING_DATA);
    return Data;
}

void XTop_Set_layer_type(XTop *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_LAYER_TYPE_DATA, Data);
}

u32 XTop_Get_layer_type(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_LAYER_TYPE_DATA);
    return Data;
}

void XTop_Set_act_silu(XTop *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_ACT_SILU_DATA, Data);
}

u32 XTop_Get_act_silu(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_ACT_SILU_DATA);
    return Data;
}

void XTop_Set_CNT(XTop *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_CNT_DATA, Data);
}

u32 XTop_Get_CNT(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_CNT_DATA);
    return Data;
}

void XTop_Set_ifm_q1(XTop *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_IFM_Q1_DATA, Data);
}

u32 XTop_Get_ifm_q1(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_IFM_Q1_DATA);
    return Data;
}

void XTop_Set_ifm_q2(XTop *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_IFM_Q2_DATA, Data);
}

u32 XTop_Get_ifm_q2(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_IFM_Q2_DATA);
    return Data;
}

void XTop_Set_weights_q(XTop *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_WEIGHTS_Q_DATA, Data);
}

u32 XTop_Get_weights_q(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_WEIGHTS_Q_DATA);
    return Data;
}

void XTop_Set_bias_q(XTop *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_BIAS_Q_DATA, Data);
}

u32 XTop_Get_bias_q(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_BIAS_Q_DATA);
    return Data;
}

void XTop_Set_ofm_q_before_act(XTop *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_OFM_Q_BEFORE_ACT_DATA, Data);
}

u32 XTop_Get_ofm_q_before_act(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_OFM_Q_BEFORE_ACT_DATA);
    return Data;
}

void XTop_Set_ofm_q_after_q(XTop *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_OFM_Q_AFTER_Q_DATA, Data);
}

u32 XTop_Get_ofm_q_after_q(XTop *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_OFM_Q_AFTER_Q_DATA);
    return Data;
}

void XTop_InterruptGlobalEnable(XTop *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_GIE, 1);
}

void XTop_InterruptGlobalDisable(XTop *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_GIE, 0);
}

void XTop_InterruptEnable(XTop *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_IER);
    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_IER, Register | Mask);
}

void XTop_InterruptDisable(XTop *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_IER);
    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_IER, Register & (~Mask));
}

void XTop_InterruptClear(XTop *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XTop_WriteReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_ISR, Mask);
}

u32 XTop_InterruptGetEnabled(XTop *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_IER);
}

u32 XTop_InterruptGetStatus(XTop *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XTop_ReadReg(InstancePtr->Ctrl_BaseAddress, XTOP_CTRL_ADDR_ISR);
}

