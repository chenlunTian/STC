/**
  ************************************* Copyright ******************************   
  *
  *                 (C) Copyright {2020},CLTian,China, SZ.
  *                            All Rights Reserved
  *                              
  *    
  * FileName   : headfile.h   
  * Version    : v1.0		
  * Author     : CLTian			
  * Date       : 2020-02-07         
  * Description:    
  * Function List:  
  ******************************************************************************
 */


#ifndef __HEADFILE_H_
#define __HEADFILE_H_

/*************************************
*串口1使用定时器2作为波特率发生器
*************************************/

#include "stc15f2k60s2.h"

#define FOSC 24000000L
//#define FOSC 11059200L

sbit LED1 = P2^0;
sbit BEEP = P2^5;

sbit KEY1 = P1^5;
sbit KEY2 = P1^6;
sbit KEY3 = P1^7;
sbit KEY4 = P3^3;
sbit KEY5 = P4^6;
sbit KEY6 = P3^2;
sbit KEY7 = P3^5;
sbit KEY8 = P4^2;
sbit KEY9 = P3^4;
sbit KEY10= P4^7;

//LCD引脚定义：注意LCD连接到了SPI接口的第二引脚，在lcd.c中作了切换
sbit    LCD_LED = 	P2^6; //一般直接接地，使液晶屏最亮，若需要亮度调节，连接到P26口，使用PWM可以调节液晶屏亮度
sbit	LCD_RST =	P0^0; //液晶RESET引脚,接单片机IO引脚
sbit	LCD_DC	=	P0^1;//液晶D/CX引脚，数据/命令控制，接单片机IO引脚
sbit	LCD_CS	=	P2^4;//液晶片选CS,P1.4为单片机SPI总线的SS引脚,通过MSTR位配置为IO模式
//以下3个SPI引脚的连接。因接单片机默认硬件SPI引脚,只需要在SPCTL中使能即可,不需程序中定义
//此为P1的SPI口，lcd.c的SPI_Init()中切换到了P2的SPI引脚上
//sbit	SDI	=	P1^3; 液晶SDI引脚,主机写到液晶,接单片机MOSI引脚P1.5
//sbit	SDO	=	P1^4; 液晶SDO引脚,从液晶读数据,接单片机MISO引脚P1.6
//sbit	SCL =   P1^5; 液晶SCL时钟引脚,接单片机SCLK时钟引脚P1.7

//MPU6050引脚定义
sbit SCL2 = P1^0;
sbit SDA2 = P1^1;

//HMC5883L
sbit SCL1 = P0^7;    
sbit SDA1 = P5^5;

//NRF24L01引脚定义
sbit MISO=P4^1;
sbit SCK =P4^3;
sbit CE  =P0^3;
sbit IRQ =P0^2;
sbit MOSI=P4^0;
sbit CSN =P5^4; 

//编码器A/B相脉冲引脚
sbit A_Phase = P3^2;	  //INT0中断
sbit B_Phase = P3^3;

sbit PWM2 = P2^7;

extern bit LED_flag;
extern bit BEEP_flag;
extern bit KEY_flag;
extern bit ADC_flag;
extern bit MPU6050_flag;
extern bit HMC5883_flag;
extern bit Encoder_flag;
				   
//bit Rotate_Dir=0;	  //用于判断编码器旋转方向
//extern int Cnt_Last;                      //记录上一次的捕获值
extern int Cnt_Now;                       //记录本次的捕获值

extern unsigned int Freq;

extern unsigned int Key_Num;

extern unsigned int adc0,adc1,adc2,adc3,adc4;
extern float li_voltage;

/****************************************************************
**頭文件
****************************************************************/
#include "delay.h"
#include "lkb.h"
#include "timer.h"
#include "uart.h"
#include <stdio.h>										 
#include "lcd.h"
#include "adc.h"
#include "mpu6050.h"
#include "image0.h"
#include "pca_pwm.h"
#include "hmc5883l.h"
#include "nrf24l01.h"
#include <math.h>
#include "int.h"


#endif


 

