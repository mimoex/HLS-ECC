// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2022.2 (64-bit)
// Tool Version Limit: 2019.12
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XADDMOD_H
#define XADDMOD_H

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
#include "xaddmod_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u64 Control_BaseAddress;
} XAddmod_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XAddmod;

typedef u32 word_type;

typedef struct {
    u32 word_0;
    u32 word_1;
    u32 word_2;
    u32 word_3;
    u32 word_4;
    u32 word_5;
    u32 word_6;
    u32 word_7;
} XAddmod_Z;

typedef struct {
    u32 word_0;
    u32 word_1;
    u32 word_2;
    u32 word_3;
    u32 word_4;
    u32 word_5;
    u32 word_6;
    u32 word_7;
} XAddmod_X;

typedef struct {
    u32 word_0;
    u32 word_1;
    u32 word_2;
    u32 word_3;
    u32 word_4;
    u32 word_5;
    u32 word_6;
    u32 word_7;
} XAddmod_Y;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XAddmod_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XAddmod_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XAddmod_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XAddmod_ReadReg(BaseAddress, RegOffset) \
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
int XAddmod_Initialize(XAddmod *InstancePtr, u16 DeviceId);
XAddmod_Config* XAddmod_LookupConfig(u16 DeviceId);
int XAddmod_CfgInitialize(XAddmod *InstancePtr, XAddmod_Config *ConfigPtr);
#else
int XAddmod_Initialize(XAddmod *InstancePtr, const char* InstanceName);
int XAddmod_Release(XAddmod *InstancePtr);
#endif

void XAddmod_Start(XAddmod *InstancePtr);
u32 XAddmod_IsDone(XAddmod *InstancePtr);
u32 XAddmod_IsIdle(XAddmod *InstancePtr);
u32 XAddmod_IsReady(XAddmod *InstancePtr);
void XAddmod_EnableAutoRestart(XAddmod *InstancePtr);
void XAddmod_DisableAutoRestart(XAddmod *InstancePtr);

XAddmod_Z XAddmod_Get_z(XAddmod *InstancePtr);
u32 XAddmod_Get_z_vld(XAddmod *InstancePtr);
void XAddmod_Set_x(XAddmod *InstancePtr, XAddmod_X Data);
XAddmod_X XAddmod_Get_x(XAddmod *InstancePtr);
void XAddmod_Set_y(XAddmod *InstancePtr, XAddmod_Y Data);
XAddmod_Y XAddmod_Get_y(XAddmod *InstancePtr);

void XAddmod_InterruptGlobalEnable(XAddmod *InstancePtr);
void XAddmod_InterruptGlobalDisable(XAddmod *InstancePtr);
void XAddmod_InterruptEnable(XAddmod *InstancePtr, u32 Mask);
void XAddmod_InterruptDisable(XAddmod *InstancePtr, u32 Mask);
void XAddmod_InterruptClear(XAddmod *InstancePtr, u32 Mask);
u32 XAddmod_InterruptGetEnabled(XAddmod *InstancePtr);
u32 XAddmod_InterruptGetStatus(XAddmod *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
