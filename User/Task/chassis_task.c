#include "chassis_task.h"
#include "mpu.h"
#include "motor.h"
#include "Grayscale_traces.h"
/* 速度常量的宏定义 */
int flag_terrain = 0; //introduce global varies to avoid the error

void detect_terrain()
{
	Grayscale_Read();
	if( sum_E <= 4 )		//亮灯为0，所以我们讨论当亮灯个数大于三个时，则该情况下出现了交汇的情况，则需要开始转动。不再保持直行
	{
		flag_terrain ++;
	}
}
/**
 * @brief 认为他鸟用没有
 * 
 */
void turn_to_white_line()
{
	Grayscale_Read(); 
	if( sum_E <= 4 )		//亮灯为0，所以我们讨论当亮灯个数大于三个时，则该情况下出现了交汇的情况，则需要开始转动。不再保持直行
	{
		if(E1 == 0 || E2 == 0  ) //最左侧俩亮
		{
			turn_right(-800,800);
			HAL_Delay(50);
			return;
		}
		else if(E8 == 0 || E7 == 0 	) //最右侧俩亮
		{
			turn_left(-800,800);
			HAL_Delay(50);
			return;
		}
	}
	else if(sum_E >5 && E4 == 0 && E5==0) //亮灯个数小于三个，且中间两个为0，就保持快速沿白线
	{
	go_forward(200,Straight_Quick); //
	}
	HAL_Delay(10);
}

void follow_white_line_1()
{
	
	Grayscale_Read(); //--to get sum_e
	detect_terrain();
/*只通过亮灯个数判断有些草率了，我们需要添加 -> 当中间俩直行*/
	if(sum_E > 5 ) 
	{
			go_forward(200,Straight_Quick);
			HAL_Delay(10);
		
	}
	else if(sum_E > 5 && E5 == 0)
	{
			go_forward(150,Straight_Slow);
			HAL_Delay(10);
	}
	else if(sum_E > 5 && E5 == 0)
	{
		go_forward(150,Straight_Slow);
		HAL_Delay(10);
	}
	else if(sum_E <= 5 && flag_terrain >2)
	{
		turn_to_white_line();
		HAL_Delay(50);
	}
}
