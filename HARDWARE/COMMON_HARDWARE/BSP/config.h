/************************************************************
* 组织名称： (C), 1988-1999, Tech. Co., Ltd.
* 文件名称: test.cpp
* 作者:
* 版本 :
* 日期:
* 描述: // 模块描述
* 主要函数及其功能 : // 主要函数及其功能
  1. -------
* 历史修改记录: // 历史修改记录
* <作者> <时间> <版本 > <描述>
* David 96/10/12 1.0 build this moudle
***********************************************************/
#ifndef     _CONFIG_H_
#define     _CONFIG_H_
/*********************************************************/
//#define MAIN_Fosc     22118400L   //定义主时钟
//#define MAIN_Fosc       12000000L   //定义主时钟
//#define MAIN_Fosc     11059200L   //定义主时钟
//#define MAIN_Fosc      5529600L   //定义主时钟
#define MAIN_Fosc     24000000L   //定义主时钟
//#define MAIN_Fosc     30000000L   //定义主时钟

/*********************************************************/
#include    "STC15Fxxxx.H"
/**************************************************************************/
#define Main_Fosc_KHZ   (MAIN_Fosc / 1000)
/***********************************************************/
#endif
