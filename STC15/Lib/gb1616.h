#ifndef __GB1616_H__
#define __GB1616_H__

#include "headfile.h"

/* ������ģ�����ݽṹ���� */
struct  typFNT_GB16                 // ������ģ���ݽṹ 
{
       unsigned char  Index[3];               // ������������	
       unsigned char   Msk[32];                        // ���������� 
}; 

extern code struct typFNT_GB16 codeGB_16[];

#endif

