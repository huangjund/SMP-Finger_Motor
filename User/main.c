#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "PWM.h"
#include "LED.h"
#include "Encoder.h"
#include "Finger_Motor.h"
#include "Timer.h"
#include "Serial.h"

int32_t Encoder_Count;
int16_t finger_reset_flag = 0;

int main(void)
{
	uint8_t RxFlag;
	uint8_t RxData;
	
	PWM_Init();
	LED_Init();
	Encoder_Init();
	Timer_Init();
	Serial_Init();
	
	reset2origin_finger();
	while (1)
	{
		RxFlag = Serial_GetRxFlag();
		if (RxFlag == 1)
		{
			RxData = Serial_GetRxData();
			Serial_SendByte(RxData);
		}
	}
}

void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
	{
		finger_stop();
		finger_reset_flag = 1;
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}
