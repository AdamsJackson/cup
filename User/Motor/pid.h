#ifndef __PID__H
#define __PID__H

#include "mpu.h"

typedef struct {
	float setpoint;  //Ŀ���趨ֵ
	float Now_err;   //���嵱ǰ���
	float Sum_err;   //�����
	float Diff_err;  //΢���
	float Last_err;  //��һ�����
	float kp,ki,kd;  //������У�΢�֣����ֳ���
}PID;




/* Door_testģʽ��ö�� */
typedef enum  
{
	DT_Disable  = 0,
	DT_1        = 1,
	DT_2        = 2,
	DT_3      	= 3,
	DT_4        = 4,
}DT_TYPE;

extern float Hui_Error_return(void);

#endif
