#include "mpu.h"
#include "main.h"
#include <stdint.h>

/**硬件层 - > PD8 PD9 作为发送 usart3
 * 得到的数据储存在my_95Q
 * 储存值分别为 roll pitch yaw level
 */
extern USART_HandleTypeDef husart3;
uint8_t usart_rx_data[30]={0},Receive_ok=1;

gy my_95Q = {0,0,0,0};
void get_data(gy *gyro)
{
	if (Receive_ok) // 如果接收完成
{
    // 计算校验和
    uint8_t sum = 0;
    for (uint8_t i = 0; i < (usart_rx_data[3] + 4); i++)
    {
        sum += usart_rx_data[i];
    }

    // 校验通过
    if (sum == usart_rx_data[usart_rx_data[3] + 4])
    {
        gy my_95Q;
        memcpy(&my_95Q, &usart_rx_data[4], sizeof(my_95Q));

        // 打印接收到的姿态数据
        printf("roll: %.2f, ", (float)my_95Q.roll / 100.0f);
        printf("pitch: %.2f, ", (float)my_95Q.pitch / 100.0f);
        printf("yaw: %.2f, ", (float)my_95Q.yaw / 100);
        printf("temp: %.2f, ", (float)my_95Q.temp / 100.0f);
        printf("leve: %.2f\r\n", (float)my_95Q.leve);
    }
    else
    {
        printf("sum %d\r\n", sum);
        printf("count %d\r\n", usart_rx_data[3] + 4);
    }

    Receive_ok = 0; // 清除接收完成标志，准备接收下一帧数据
}
	
}
void send_command(uint8_t addr, uint8_t ft_code, uint8_t start_reg, uint8_t reg_number)
{
    uint8_t send_data[5] = {addr, ft_code, start_reg, reg_number, 0};
    HAL_USART_Transmit(&husart3, send_data, 5, HAL_MAX_DELAY); // HAL-based transmission
}
