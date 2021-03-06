#include "headfile.h"


unsigned int adc0,adc1,adc2,adc3,adc4;
float li_voltage=0;

KEYMSG left;
KEYMSG right;
KEYMSG up;
KEYMSG down;
KEYMSG kb;

KEYMSG a_jump; //跳跃
KEYMSG a_shoot;//射击
KEYMSG a_left;
KEYMSG a_right;

void Encoder_Task();
void MPU6050_Task();
void HMC5883_Task();
void KEY_Task();
void ADC_Task();

void Encoder_Task()
{
	LCD_Show2Num(0,112,Freq,6);
	printf("%d\n",Cnt_Now);	
}

void MPU6050_Task()
{
	static unsigned int j=0;
	Angle_Calcu();		//倾角计算 将得到下面两个全局变量,使用了网上摘抄的卡尔曼滤波
						//float Angle;   //最终倾斜角度
						//float Gyro_x;  //x轴角速度
//	if(Accel_x >=20 && Accel_x<=90)	
//	{
//		sendMsg(&a_jump, 7, 1);
//	}
//	else if(Accel_x >=-90 && Accel_x<=-20)	
//	{
//		sendMsg(&a_shoot, 6, 1);					 
//	}
//	else 
//	{
//		if(a_jump.msg == 1)
//		{
//			sendMsg(&a_jump, 7, 0);
//		}
//		else if(a_shoot.msg == 1)
//		{
//			sendMsg(&a_shoot, 6, 0);
//		}
//	}

//	if(Accel_y >=20 && Accel_y<=90)	
//	{
//		sendMsg(&a_right, 3, 1);
//	}
//	else if(Accel_y >=-90 && Accel_y<=-20)	
//	{
//		sendMsg(&a_left, 2, 1);					 
//	}
//	else 
//	{
//		if(a_right.msg == 1)
//		{
//			sendMsg(&a_right, 3, 0);
//		}
//		else if(a_left.msg == 1)
//		{
//			sendMsg(&a_left, 2, 0);
//		}
//	}



	printf("%.2f,%.2f\n",Angle,Gyro_x);
//	j++;
//	if(j>=240)
//	{
//		j=0;
//		LCD_Fill(0,140,239,318,Black);
//		POINT_COLOR = Red;
//		BACK_COLOR=Black;
//		LCD_DrawLine(0,229,239,229);
//		POINT_COLOR = Green;
//	}
//	if((int)Angle>-90 && (int)Angle<90 )	  //排除初始不稳定杂波
//	{
//		LCD_DrawPoint(j,229-(int)Angle);
//		//通过NRF24L01发送出去
//		if(Angle>=0)
//		{
//			Tx_Buf[2] = '+';
//			Tx_Buf[3] =(unsigned char)Angle;	
//		}
//		else
//		{
//			Tx_Buf[2] = '-';
//			Tx_Buf[3] = (unsigned char)(Angle*(-1));
//		}		
//  		Transmit(Tx_Buf);			//24L01发送缓冲数组
//  		sta=SPI_Read(READ_REG +  STATUS);	//读24L01的状态寄存器
//  		if(TX_DS)	//sbit TX_DS =sta^5;数据发送完成中断，接收到应答信号时此位置1，写1清除中断
//  		{  
//   			//Delay_ms(5); 
//   			SPI_RW_Reg(WRITE_REG + STATUS,sta);  //写状态寄存器，清除中断
//  		}
//		if(MAX_RT)  //如果是发送超时  sbit MAX_RT =sta^4;
//  		{			//达到最多次重发中断，MAX_RT中断产生则必须清除后系统才能进行通讯，写1清除中断
//   			//Delay_ms(5);  
//   			SPI_RW_Reg(WRITE_REG + STATUS,sta);
//  		}
//	}
	
}

void HMC5883_Task()
{
	//static unsigned int m=0;
	static float Last_HMC5883_Angle=0;
//	float Avg_HMC5883_Angle=0;
//	float Last_Avg_HMC5883_Angle=0;
//	float temp_HMC5883_Angle=0;

	Multiple_Read_HMC5883();				  //角度的变化似乎并不是线性的
	LCD_Show2Num(32,80,(int)HMC5883_Angle,3); 
	POINT_COLOR=BACK_COLOR;					   //三角函数使用弧度而不是度!
	LCD_DrawLine(120,100,120+(int)(28.0*cos((Last_HMC5883_Angle-180.0)/57.3)),100+(int)(28.0*sin((Last_HMC5883_Angle-180.0)/57.3)));
	POINT_COLOR=Yellow;
	LCD_DrawLine(120,100,120+(int)(28.0*cos((HMC5883_Angle-180.0)/57.3)),100+(int)(28.0*sin((HMC5883_Angle-180.0)/57.3)));
	Last_HMC5883_Angle=HMC5883_Angle;
//			//平均值滤波
//			m++;
//			temp_HMC5883_Angle+=HMC5883_Angle;	
//			if(m==5)
//			{
//				m=0;
//				Avg_HMC5883_Angle=temp_HMC5883_Angle/5.0;	 //与前面四个值相关联
//				//printf("\n\n%.2f\n\n",HMC5883_Angle);	  //HMC5883_Angle: float型，0~360
//				LCD_Show2Num(32,80,(int)Avg_HMC5883_Angle,3); 
//				POINT_COLOR=BACK_COLOR;
//				LCD_DrawLine(120,100,120+28*cos((Last_Avg_HMC5883_Angle-180.0)/57.3),100+28*sin((Last_Avg_HMC5883_Angle-180.0)/57.3));
//				POINT_COLOR=Yellow;
//				LCD_DrawLine(120,100,120+28*cos((Avg_HMC5883_Angle-180.0)/57.3),100+28*sin((Avg_HMC5883_Angle-180.0)/57.3));
//				Last_Avg_HMC5883_Angle=Avg_HMC5883_Angle;
//			} 
}

void ADC_Task()
{
	static unsigned int i=0;
	static unsigned int k=0;

	POINT_COLOR= Green;
	i++;
	switch(i)
	{
		case 1: adc0=(int)ADC_GetResult(0);LCD_Show2Num(48,0,adc0,3); break;
		case 2:	adc1=(int)ADC_GetResult(1);LCD_Show2Num(48,16,adc1,3); break;
		case 3:	adc2=(int)ADC_GetResult(2);LCD_Show2Num(168,0,adc2,3); break;
		case 4:	adc3=(int)ADC_GetResult(3);LCD_Show2Num(168,16,adc3,3); break;
		case 5:	li_voltage=(float)ADC_GetResult(4)*0.019f; break; //adc4*3.3/256*(6.8+3.3)/6.8=adc4*0.019
		default:
			i=0;
			LCD_Show2Num(96,32,(int)li_voltage,1); 				//显示整数部分
			LCD_Show2Num(112,32,((int)(li_voltage*100))%100,2); //显示小数部分
			//printf("%d,%d,%d,%d,%.2f\n",adc0,adc1,adc2,adc3,li_voltage);
	 }//switch 结束

	k++;
	//printf("%d,%d,", adc1, adc0);
	if(k%2)
	{
		if(adc1>=0 && adc1<=80)	
		{
			sendMsg(&up, 1, 1);
		}
		else if(adc1>=170 && adc1<=255)	
		{
			sendMsg(&down, 4, 1);					 
		}
		else 
		{
			if(up.msg == 1)
			{
				sendMsg(&up, 1, 0);
			}
			else if(down.msg == 1)
			{
				sendMsg(&down, 4, 0);
			}
		}
	}
	else
	{
		if(adc0>=0 && adc0<=80)	
		{
			sendMsg(&left, 3, 1);
		}
		else if(adc0>=170 && adc0<=255)	
		{
			sendMsg(&right, 2, 1);					 
		}
		else 
		{
			if(left.msg == 1)
			{
				sendMsg(&left, 3, 0);
			}
			else if(right.msg == 1)
			{
				sendMsg(&right, 2, 0);
			}
		}
	}
}

//void KEY_Task()
//{
//	if (key_up==0)
//	{
//		sendMsg(&kb, Key_Num, 1);	 //sendMsg()函数里面有printf
//	}
//	else  //if(key_up == 1) 
//	{
//
//		if (kb.msg == 1) ;
//			sendMsg(&kb, kb.key, 0);
//	}
//	//printf("%d\n",Key_Num);
//}

/*可以使用单步仿真一步步查看效果*/
void main()
{	
//	unsigned int i;

	Delay_ms(10);	
	Delay_us(10);
//	PWM2=0;			//电机制动，可以下拉10k设置引脚为推挽制动

//	/*2.2寸、320*240分辨率、SPI接口的LCD初始化,使用STC的硬件SPI,LCD驱动芯片为ILI9340C*/
//	LCD_LED=0;		//LCD背光最亮
//	SPI_Init();		//IAP15硬件SPI初始化,切换到了SPI的第二通道:SS/P24、MOSI/P23、MISO/P22、SCK/P21
//	LCD_Init();		//LCD初始化，厂家提供

//	/*LCD休眠演示*/
//	LCD_Sleep();	//LCD进入休眠状态
//	Delay_ms(100);	
//	LCD_ExitSleep();//LCD退出休眠状态
//	/*LCD刷屏演示：红橙黄绿青蓝紫 白黑*/
//	LCD_Clear(Red);	
//	LCD_Clear(Orange);
//	LCD_Clear(Yellow);
//	LCD_Clear(Green);
//	LCD_Clear(Cyan);
//	LCD_Clear(Blue);
//	LCD_Clear(Purple);
//	LCD_Clear(White);
//	LCD_Clear(Black);
//	/*LCD画线、英文、汉字、数字显示测试*/
//	/*液晶屏左上角坐标为(0,0),右下角坐标为(239,319)*/
//	POINT_COLOR=Green; //全局变量
//	BACK_COLOR=Black; 	//前景色类似于在黑板写字的各种颜色的粉笔，黑板的颜色就是背景色	
//	LCD_ShowString(0,0,"Hello,world!");	//从(0,0)坐标开始显示字符串“Hello,World!”
//	POINT_COLOR=Blue;					//可以随时更改画笔颜色，显示不同颜色的数字
//	LCD_DrawLine(100,0,240,15);			//画一条线段，起始坐标(100,0),终点坐标(240,15)
//	LCD_Show2Num(0,16,65535,5);			//从(0,16)坐标开始显示0~65535的数字，5为数字位数，即显示5位数字
//	LCD_ShowNum(100,16,987654321,9);	//从(100,16)坐标开始显示unsigned long型数字(0~4294967295),10为数字位数，即10位数字
//	POINT_COLOR=Yellow;
//	for(i=32;i<320;i+=16)
//	{
//		LCD_ShowString(0,i,"abcdefghijklmnopqrstuvwxyz!");
//	}
//	LCD_LED=1;		//LCD背光关闭
//	Delay_ms(500);
//	LCD_LED=0;		//LCD背光最亮
//	Delay_ms(500);
//	LCD_Clear(Black);					//清屏：黑色
//	//LCD_Fill(120,120,160,160,Yellow);	//在矩形区域填充色块，在函数处按F12可以查看函数原型
//	LCD_ShowImage(gImage_musi,80,120,78,80);//显示彩色图像： 慕司LOGO
//	Delay_ms(2000);
//	LCD_Clear(Black);
//	POINT_COLOR=Red;
//	LCD_DrawRectangle(0,0,239,60);	 //画矩形：对角坐标(左上、右下)为(0,0),(239,60)
//	POINT_COLOR=Purple;
//	LCD_ShowString(80,2,"慕司"); 	 //显示16*16汉字
//	LCD_ShowString(16,22,"为一线微茫憧憬一意孤行，");
//	LCD_ShowString(8,42,"这众生芸芸谁不曾如此任性！");
//	POINT_COLOR=Cyan;
//	LCD_ShowGB3232(80,160,"青春");
//	POINT_COLOR=Green;
//	LCD_DrawCircle(112,176,48);
//	Delay_ms(500);

//	PCA_PWM_Init();		//PWM初始化，切换到PWM的第三通道P25/P26/P27，这里仅使用了PWM1(P26,即LCD_LED引脚)
//	LCD_LED=0;			//LCD背光最亮
//	for(i=255;i<=0;i--)	//液晶背光256级亮度调节演示:由亮到暗
//	{
//		CCAP1H = CCAP1L = i; 	  //通过调节占空比来调节屏幕亮度
//		Delay_ms(20);
//	}
//	LCD_LED=1;			//LCD背光关闭
//	for(i=0;i<255;i++)	//液晶背光256级亮度调节演示:由暗到亮
//	{
//		CCAP1H = CCAP1L = i; 	  //通过调节占空比来调节屏幕亮度
//		Delay_ms(20);
//	}
//	Delay_ms(1000);
//	LCD_Clear(Black);

//	LKB_Init();				//LED Key Buzzer：LED、按键、蜂鸣器 初始化(设置蜂鸣器端口为推挽输出)
//	Buzzer_Func(500,1000);	//蜂鸣器500Hz@1000ms

//	ADC_Init();			   //AD初始化：设置P1的0 1 2 3(摇杆)4(锂电池电压)口为AD口，
//	POINT_COLOR = Green; 	   //液晶屏画笔颜色
//	BACK_COLOR=Black;	   //背景色
//	LCD_ShowString(0,0 ,"adc0:     ");
//	LCD_ShowString(0,16,"adc1:     ");
//	LCD_ShowString(120,0,"adc2:     ");
//	LCD_ShowString(120,16,"adc3:     ");
//	LCD_ShowString(0,32,"li_voltage:      V");
//	LCD_ShowString(104,32,".");

//	NRF24L01_Init();
//	TX_Mode();		     //发送模式
//	LCD_ShowString(0,48,"NRF24L01_State: Tx_Mode");

//	MPU6050_Init();
//	Delay_ms(100);

//	POINT_COLOR = Red;
//	LCD_DrawLine(0,319,239,319);
//	LCD_DrawLine(0,139,239,139);
//	LCD_DrawLine(0,229,239,229);

//	HMC5883_Init();
//	Delay_ms(100);
//	POINT_COLOR = Green;
//	LCD_DrawCircle(120,100,31);
//	LCD_ShowString(0,64,"direction：");

//	LCD_ShowString(0,96,"speed：");

	Timer_Init(100);	 //每10ms中断一次,参数为百us：100*100us = 10ms
	UART_Init(115200);	 //串口初始化，使用了串口1的第一通道，设置波特率115200，用于仿真时可以切换到第二通道P36/P37
	TI=1;
	SBUF=0;				 //这一句使用printf有时是必须的
	INT_Init(); 
	MPU6050_Init();
	printf("MPU6050 IS OK\n\t");	
	Delay_ms(100);
	while(1)
	{
		
//		if(LED_flag)		 //每1s切换一次LED的状态
//		{LED_flag=0;LED1 = ~LED1;}

//		if(ADC_flag)
//		{ADC_flag=0;ADC_Task();}
		
//		if(adc2 >=80 && Encoder_flag)	 //使用adc2作开关
//		{
//			Encoder_flag=0;
//			CCAP2H = CCAP2L = (adc3 - 10)*2;	//使用摇杆的ADC3调节电机转速
//			Encoder_Task();
//		}
//		else  if(adc2 <=70)
//		{
			if(MPU6050_flag)	  //MPU6050的几个函数使用了Delay_us(5)
			{
			MPU6050_flag=0;
			MPU6050_Task();
			printf("MPU6050_Task is ok\n\t");
				
			}
			Delay_ms(100);
//	
//			if(HMC5883_flag)
//			{HMC5883_flag=0;HMC5883_Task();}
//	
//			//interrupt.c中把Key_Scan()改成支持连按
//			//uart.c中把串口1切换回P30/P31
//			if(KEY_flag)
//			{
////				KEY_Task();
//				if (key_up==0)
//				{
//					sendMsg(&kb, Key_Num, 1);	 //sendMsg()函数里面有printf
//				}
//				else  //if(key_up == 1) 
//				{
//				 	KEY_flag=0;
//					if (kb.msg == 1) ;
//						sendMsg(&kb, kb.key, 0);
//				}
//				printf("%d\n",Key_Num);
//			}
//		}
//		else
//			{;}
	}		
}
