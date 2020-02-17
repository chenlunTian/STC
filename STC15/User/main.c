#include "headfile.h"


unsigned int adc0,adc1,adc2,adc3,adc4;
float li_voltage=0;

KEYMSG left;
KEYMSG right;
KEYMSG up;
KEYMSG down;
KEYMSG kb;

KEYMSG a_jump; //��Ծ
KEYMSG a_shoot;//���
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
	Angle_Calcu();		//��Ǽ��� ���õ���������ȫ�ֱ���,ʹ��������ժ���Ŀ������˲�
						//float Angle;   //������б�Ƕ�
						//float Gyro_x;  //x����ٶ�
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
//	if((int)Angle>-90 && (int)Angle<90 )	  //�ų���ʼ���ȶ��Ӳ�
//	{
//		LCD_DrawPoint(j,229-(int)Angle);
//		//ͨ��NRF24L01���ͳ�ȥ
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
//  		Transmit(Tx_Buf);			//24L01���ͻ�������
//  		sta=SPI_Read(READ_REG +  STATUS);	//��24L01��״̬�Ĵ���
//  		if(TX_DS)	//sbit TX_DS =sta^5;���ݷ�������жϣ����յ�Ӧ���ź�ʱ��λ��1��д1����ж�
//  		{  
//   			//Delay_ms(5); 
//   			SPI_RW_Reg(WRITE_REG + STATUS,sta);  //д״̬�Ĵ���������ж�
//  		}
//		if(MAX_RT)  //����Ƿ��ͳ�ʱ  sbit MAX_RT =sta^4;
//  		{			//�ﵽ�����ط��жϣ�MAX_RT�жϲ�������������ϵͳ���ܽ���ͨѶ��д1����ж�
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

	Multiple_Read_HMC5883();				  //�Ƕȵı仯�ƺ����������Ե�
	LCD_Show2Num(32,80,(int)HMC5883_Angle,3); 
	POINT_COLOR=BACK_COLOR;					   //���Ǻ���ʹ�û��ȶ����Ƕ�!
	LCD_DrawLine(120,100,120+(int)(28.0*cos((Last_HMC5883_Angle-180.0)/57.3)),100+(int)(28.0*sin((Last_HMC5883_Angle-180.0)/57.3)));
	POINT_COLOR=Yellow;
	LCD_DrawLine(120,100,120+(int)(28.0*cos((HMC5883_Angle-180.0)/57.3)),100+(int)(28.0*sin((HMC5883_Angle-180.0)/57.3)));
	Last_HMC5883_Angle=HMC5883_Angle;
//			//ƽ��ֵ�˲�
//			m++;
//			temp_HMC5883_Angle+=HMC5883_Angle;	
//			if(m==5)
//			{
//				m=0;
//				Avg_HMC5883_Angle=temp_HMC5883_Angle/5.0;	 //��ǰ���ĸ�ֵ�����
//				//printf("\n\n%.2f\n\n",HMC5883_Angle);	  //HMC5883_Angle: float�ͣ�0~360
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
			LCD_Show2Num(96,32,(int)li_voltage,1); 				//��ʾ��������
			LCD_Show2Num(112,32,((int)(li_voltage*100))%100,2); //��ʾС������
			//printf("%d,%d,%d,%d,%.2f\n",adc0,adc1,adc2,adc3,li_voltage);
	 }//switch ����

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
//		sendMsg(&kb, Key_Num, 1);	 //sendMsg()����������printf
//	}
//	else  //if(key_up == 1) 
//	{
//
//		if (kb.msg == 1) ;
//			sendMsg(&kb, kb.key, 0);
//	}
//	//printf("%d\n",Key_Num);
//}

/*����ʹ�õ�������һ�����鿴Ч��*/
void main()
{	
//	unsigned int i;

	Delay_ms(10);	
	Delay_us(10);
//	PWM2=0;			//����ƶ�����������10k��������Ϊ�����ƶ�

//	/*2.2�硢320*240�ֱ��ʡ�SPI�ӿڵ�LCD��ʼ��,ʹ��STC��Ӳ��SPI,LCD����оƬΪILI9340C*/
//	LCD_LED=0;		//LCD��������
//	SPI_Init();		//IAP15Ӳ��SPI��ʼ��,�л�����SPI�ĵڶ�ͨ��:SS/P24��MOSI/P23��MISO/P22��SCK/P21
//	LCD_Init();		//LCD��ʼ���������ṩ

//	/*LCD������ʾ*/
//	LCD_Sleep();	//LCD��������״̬
//	Delay_ms(100);	
//	LCD_ExitSleep();//LCD�˳�����״̬
//	/*LCDˢ����ʾ����Ȼ��������� �׺�*/
//	LCD_Clear(Red);	
//	LCD_Clear(Orange);
//	LCD_Clear(Yellow);
//	LCD_Clear(Green);
//	LCD_Clear(Cyan);
//	LCD_Clear(Blue);
//	LCD_Clear(Purple);
//	LCD_Clear(White);
//	LCD_Clear(Black);
//	/*LCD���ߡ�Ӣ�ġ����֡�������ʾ����*/
//	/*Һ�������Ͻ�����Ϊ(0,0),���½�����Ϊ(239,319)*/
//	POINT_COLOR=Green; //ȫ�ֱ���
//	BACK_COLOR=Black; 	//ǰ��ɫ�������ںڰ�д�ֵĸ�����ɫ�ķ۱ʣ��ڰ����ɫ���Ǳ���ɫ	
//	LCD_ShowString(0,0,"Hello,world!");	//��(0,0)���꿪ʼ��ʾ�ַ�����Hello,World!��
//	POINT_COLOR=Blue;					//������ʱ���Ļ�����ɫ����ʾ��ͬ��ɫ������
//	LCD_DrawLine(100,0,240,15);			//��һ���߶Σ���ʼ����(100,0),�յ�����(240,15)
//	LCD_Show2Num(0,16,65535,5);			//��(0,16)���꿪ʼ��ʾ0~65535�����֣�5Ϊ����λ��������ʾ5λ����
//	LCD_ShowNum(100,16,987654321,9);	//��(100,16)���꿪ʼ��ʾunsigned long������(0~4294967295),10Ϊ����λ������10λ����
//	POINT_COLOR=Yellow;
//	for(i=32;i<320;i+=16)
//	{
//		LCD_ShowString(0,i,"abcdefghijklmnopqrstuvwxyz!");
//	}
//	LCD_LED=1;		//LCD����ر�
//	Delay_ms(500);
//	LCD_LED=0;		//LCD��������
//	Delay_ms(500);
//	LCD_Clear(Black);					//��������ɫ
//	//LCD_Fill(120,120,160,160,Yellow);	//�ھ����������ɫ�飬�ں�������F12���Բ鿴����ԭ��
//	LCD_ShowImage(gImage_musi,80,120,78,80);//��ʾ��ɫͼ�� Ľ˾LOGO
//	Delay_ms(2000);
//	LCD_Clear(Black);
//	POINT_COLOR=Red;
//	LCD_DrawRectangle(0,0,239,60);	 //�����Σ��Խ�����(���ϡ�����)Ϊ(0,0),(239,60)
//	POINT_COLOR=Purple;
//	LCD_ShowString(80,2,"Ľ˾"); 	 //��ʾ16*16����
//	LCD_ShowString(16,22,"Ϊһ��΢ã��һ����У�");
//	LCD_ShowString(8,42,"������ܿܿ˭����������ԣ�");
//	POINT_COLOR=Cyan;
//	LCD_ShowGB3232(80,160,"�ഺ");
//	POINT_COLOR=Green;
//	LCD_DrawCircle(112,176,48);
//	Delay_ms(500);

//	PCA_PWM_Init();		//PWM��ʼ�����л���PWM�ĵ���ͨ��P25/P26/P27�������ʹ����PWM1(P26,��LCD_LED����)
//	LCD_LED=0;			//LCD��������
//	for(i=255;i<=0;i--)	//Һ������256�����ȵ�����ʾ:��������
//	{
//		CCAP1H = CCAP1L = i; 	  //ͨ������ռ�ձ���������Ļ����
//		Delay_ms(20);
//	}
//	LCD_LED=1;			//LCD����ر�
//	for(i=0;i<255;i++)	//Һ������256�����ȵ�����ʾ:�ɰ�����
//	{
//		CCAP1H = CCAP1L = i; 	  //ͨ������ռ�ձ���������Ļ����
//		Delay_ms(20);
//	}
//	Delay_ms(1000);
//	LCD_Clear(Black);

//	LKB_Init();				//LED Key Buzzer��LED�������������� ��ʼ��(���÷������˿�Ϊ�������)
//	Buzzer_Func(500,1000);	//������500Hz@1000ms

//	ADC_Init();			   //AD��ʼ��������P1��0 1 2 3(ҡ��)4(﮵�ص�ѹ)��ΪAD�ڣ�
//	POINT_COLOR = Green; 	   //Һ����������ɫ
//	BACK_COLOR=Black;	   //����ɫ
//	LCD_ShowString(0,0 ,"adc0:     ");
//	LCD_ShowString(0,16,"adc1:     ");
//	LCD_ShowString(120,0,"adc2:     ");
//	LCD_ShowString(120,16,"adc3:     ");
//	LCD_ShowString(0,32,"li_voltage:      V");
//	LCD_ShowString(104,32,".");

//	NRF24L01_Init();
//	TX_Mode();		     //����ģʽ
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
//	LCD_ShowString(0,64,"direction��");

//	LCD_ShowString(0,96,"speed��");

	Timer_Init(100);	 //ÿ10ms�ж�һ��,����Ϊ��us��100*100us = 10ms
	UART_Init(115200);	 //���ڳ�ʼ����ʹ���˴���1�ĵ�һͨ�������ò�����115200�����ڷ���ʱ�����л����ڶ�ͨ��P36/P37
	TI=1;
	SBUF=0;				 //��һ��ʹ��printf��ʱ�Ǳ����
	INT_Init(); 
	MPU6050_Init();
	printf("MPU6050 IS OK\n\t");	
	Delay_ms(100);
	while(1)
	{
		
//		if(LED_flag)		 //ÿ1s�л�һ��LED��״̬
//		{LED_flag=0;LED1 = ~LED1;}

//		if(ADC_flag)
//		{ADC_flag=0;ADC_Task();}
		
//		if(adc2 >=80 && Encoder_flag)	 //ʹ��adc2������
//		{
//			Encoder_flag=0;
//			CCAP2H = CCAP2L = (adc3 - 10)*2;	//ʹ��ҡ�˵�ADC3���ڵ��ת��
//			Encoder_Task();
//		}
//		else  if(adc2 <=70)
//		{
			if(MPU6050_flag)	  //MPU6050�ļ�������ʹ����Delay_us(5)
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
//			//interrupt.c�а�Key_Scan()�ĳ�֧������
//			//uart.c�аѴ���1�л���P30/P31
//			if(KEY_flag)
//			{
////				KEY_Task();
//				if (key_up==0)
//				{
//					sendMsg(&kb, Key_Num, 1);	 //sendMsg()����������printf
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