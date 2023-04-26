/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "xil_printf.h"
#include "xparameters.h"
#include "xaddmod.h"

XAddmod Instance;

/*
* AddMod test
* x=56444717392532950066703248216298613406963050146664185407156138575012476696839
* y=20812168509434597367146703229805575690060615791308155437936410982393987532344
* p=57896044618658097711785492504343953926634992332820282019728792003956564819949
* z=(x+y)%p
* z=19360841283309449722064458941760235170388673605152058825363757553449899409234
*/
int main()
{
    if(XAddmod_Initialize(&Instance,
    		XPAR_ADDMOD_0_DEVICE_ID)!=XST_SUCCESS){
    	xil_printf("Init Error\n");
    	return XST_FAILURE;
    }

    XAddmod_X xv;
    XAddmod_Y yv;
    XAddmod_Z zv;

    xv.word_0=0xe3bb3907;
    xv.word_1=0x94c4d5bb;
    xv.word_2=0xf63f0001;
    xv.word_3=0xc0259e16;
    xv.word_4=0x4c4c47b6;
    xv.word_5=0xb66313f4;
    xv.word_6=0x4310216d;
    xv.word_7=0x7cca93f1;

    yv.word_0=0xba510638;
    yv.word_1=0xb85497a9;
	yv.word_2=0xb479104;
	yv.word_3=0x68e100a5;
	yv.word_4=0x76877e9d;
	yv.word_5=0xd00b0638;
	yv.word_6=0x7181446f;
	yv.word_7=0x2e03451a;

	XAddmod_Set_x(&Instance, xv);
	XAddmod_Set_y(&Instance, yv);

	//XAddmod_EnableAutoRestart(&Instance);
	XAddmod_Start(&Instance);

	while (XAddmod_IsDone(&Instance)==0);

	zv=XAddmod_Get_z(&Instance);

	printf("%lu\n",zv.word_0);
	printf("%lu\n",zv.word_1);
	printf("%lu\n",zv.word_2);
	printf("%lu\n",zv.word_3);
	printf("%lu\n",zv.word_4);
	printf("%lu\n",zv.word_5);
	printf("%lu\n",zv.word_6);
	printf("%lu\n",zv.word_7);

    return 0;
}
