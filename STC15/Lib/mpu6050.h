#ifndef __MPU6050_H__
#define __MPU6050_H__

#include "headfile.h"

extern float Accel_x;	     					//X����ٶ�ֵ�ݴ�
extern float Accel_y;	     					//Y����ٶ�ֵ�ݴ�
extern float Accel_z;       					//�ɼ��ٶȼƼ������б�Ƕ�

extern float Gyro_y;        //Y�������������ݴ�					//�ɽ��ٶȼ������б�Ƕ�
extern float Gyro_x;        //x�������������ݴ�					//�ɽ��ٶȼ������б�Ƕ�
extern float Angle_ax;      //�ɼ��ٶȼ������б�Ƕ� x����
extern float Angle_ay;			//�ɼ��ٶȼ������б�Ƕ� y����
extern float Angle;         //������б�Ƕ�

//****************************************
// ����MPU6050�ڲ���ַ
//****************************************
#define	SMPLRT_DIV		0x19	//�����ǲ����ʣ�����ֵ��0x07(125Hz)
#define	CONFIG_M			0x1A	//��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
#define	ACCEL_CONFIG	0x1C	//���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B	//��Դ����������ֵ��0x00(��������)
#define	WHO_AM_I			0x75	//IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��)
#define	SlaveAddress	0xD0	//IICд��ʱ�ĵ�ַ�ֽ����ݣ�+1Ϊ��ȡ


#define  dt 0.01	            // dtΪkalman�˲�������ʱ��,�������ʱ���綨ʱ���ж�ʱ��ı䣿
#define  C_0  1.0

void MPU6050_Init();
void Angle_Calcu();

#endif