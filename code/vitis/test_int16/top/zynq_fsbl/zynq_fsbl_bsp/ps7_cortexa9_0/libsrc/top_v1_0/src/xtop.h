// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XTOP_H
#define XTOP_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xtop_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u32 Ctrl_BaseAddress;
} XTop_Config;
#endif

typedef struct {
    u64 Ctrl_BaseAddress;
    u32 IsReady;
} XTop;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XTop_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XTop_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XTop_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XTop_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XTop_Initialize(XTop *InstancePtr, u16 DeviceId);
XTop_Config* XTop_LookupConfig(u16 DeviceId);
int XTop_CfgInitialize(XTop *InstancePtr, XTop_Config *ConfigPtr);
#else
int XTop_Initialize(XTop *InstancePtr, const char* InstanceName);
int XTop_Release(XTop *InstancePtr);
#endif

void XTop_Start(XTop *InstancePtr);
u32 XTop_IsDone(XTop *InstancePtr);
u32 XTop_IsIdle(XTop *InstancePtr);
u32 XTop_IsReady(XTop *InstancePtr);
void XTop_EnableAutoRestart(XTop *InstancePtr);
void XTop_DisableAutoRestart(XTop *InstancePtr);

void XTop_Set_ifm_offset(XTop *InstancePtr, u32 Data);
u32 XTop_Get_ifm_offset(XTop *InstancePtr);
void XTop_Set_ofm_offset(XTop *InstancePtr, u32 Data);
u32 XTop_Get_ofm_offset(XTop *InstancePtr);
void XTop_Set_weights_offset(XTop *InstancePtr, u32 Data);
u32 XTop_Get_weights_offset(XTop *InstancePtr);
void XTop_Set_bias_offset(XTop *InstancePtr, u32 Data);
u32 XTop_Get_bias_offset(XTop *InstancePtr);
void XTop_Set_ifm_ch(XTop *InstancePtr, u32 Data);
u32 XTop_Get_ifm_ch(XTop *InstancePtr);
void XTop_Set_ifm_h(XTop *InstancePtr, u32 Data);
u32 XTop_Get_ifm_h(XTop *InstancePtr);
void XTop_Set_ifm_w(XTop *InstancePtr, u32 Data);
u32 XTop_Get_ifm_w(XTop *InstancePtr);
void XTop_Set_ofm_ch(XTop *InstancePtr, u32 Data);
u32 XTop_Get_ofm_ch(XTop *InstancePtr);
void XTop_Set_ofm_h(XTop *InstancePtr, u32 Data);
u32 XTop_Get_ofm_h(XTop *InstancePtr);
void XTop_Set_ofm_w(XTop *InstancePtr, u32 Data);
u32 XTop_Get_ofm_w(XTop *InstancePtr);
void XTop_Set_I_CH(XTop *InstancePtr, u32 Data);
u32 XTop_Get_I_CH(XTop *InstancePtr);
void XTop_Set_I_H(XTop *InstancePtr, u32 Data);
u32 XTop_Get_I_H(XTop *InstancePtr);
void XTop_Set_I_W(XTop *InstancePtr, u32 Data);
u32 XTop_Get_I_W(XTop *InstancePtr);
void XTop_Set_O_CH(XTop *InstancePtr, u32 Data);
u32 XTop_Get_O_CH(XTop *InstancePtr);
void XTop_Set_O_H(XTop *InstancePtr, u32 Data);
u32 XTop_Get_O_H(XTop *InstancePtr);
void XTop_Set_O_W(XTop *InstancePtr, u32 Data);
u32 XTop_Get_O_W(XTop *InstancePtr);
void XTop_Set_ker_size(XTop *InstancePtr, u32 Data);
u32 XTop_Get_ker_size(XTop *InstancePtr);
void XTop_Set_stride(XTop *InstancePtr, u32 Data);
u32 XTop_Get_stride(XTop *InstancePtr);
void XTop_Set_padding(XTop *InstancePtr, u32 Data);
u32 XTop_Get_padding(XTop *InstancePtr);
void XTop_Set_layer_type(XTop *InstancePtr, u32 Data);
u32 XTop_Get_layer_type(XTop *InstancePtr);
void XTop_Set_act_silu(XTop *InstancePtr, u32 Data);
u32 XTop_Get_act_silu(XTop *InstancePtr);
void XTop_Set_CNT(XTop *InstancePtr, u32 Data);
u32 XTop_Get_CNT(XTop *InstancePtr);
void XTop_Set_ifm_q1(XTop *InstancePtr, u32 Data);
u32 XTop_Get_ifm_q1(XTop *InstancePtr);
void XTop_Set_ifm_q2(XTop *InstancePtr, u32 Data);
u32 XTop_Get_ifm_q2(XTop *InstancePtr);
void XTop_Set_weights_q(XTop *InstancePtr, u32 Data);
u32 XTop_Get_weights_q(XTop *InstancePtr);
void XTop_Set_bias_q(XTop *InstancePtr, u32 Data);
u32 XTop_Get_bias_q(XTop *InstancePtr);
void XTop_Set_ofm_q_before_act(XTop *InstancePtr, u32 Data);
u32 XTop_Get_ofm_q_before_act(XTop *InstancePtr);
void XTop_Set_ofm_q_after_q(XTop *InstancePtr, u32 Data);
u32 XTop_Get_ofm_q_after_q(XTop *InstancePtr);

void XTop_InterruptGlobalEnable(XTop *InstancePtr);
void XTop_InterruptGlobalDisable(XTop *InstancePtr);
void XTop_InterruptEnable(XTop *InstancePtr, u32 Mask);
void XTop_InterruptDisable(XTop *InstancePtr, u32 Mask);
void XTop_InterruptClear(XTop *InstancePtr, u32 Mask);
u32 XTop_InterruptGetEnabled(XTop *InstancePtr);
u32 XTop_InterruptGetStatus(XTop *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
