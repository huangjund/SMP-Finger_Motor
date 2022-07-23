#include "stm32f10x.h"
#include "Finger_Motor.h"
#include "LED.h"
#include "PWM.h"
#include "Encoder.h"
#include "config.h"

extern int16_t finger_reset_flag;

void reset2origin_finger(void) {
	Encoder_Get();	// flash the encoder
	LED1_ON();
	PWM_SetCompare1(FINGER_RESET_SPEED);
	TIM_Cmd(TIM3, ENABLE);
	while(!finger_reset_flag) {}
	TIM_Cmd(TIM3, DISABLE);
	finger_reset_flag = 0;
}

void finger_down(void) {
	int counter = 0;
	Encoder_Get();	// flash the encoder
	LED1_OFF();
	PWM_SetCompare1(DEGREE90_SPEED);
	
	// TIM_Cmd(TIM3, ENABLE);
	while (1)
	{
		counter += Encoder_Get();
		if (counter >= DEGREE90_SPEEDMAX_DECODER_NUM) {
			PWM_SetCompare1(FINGER_STOP_SPEED);
			TIM_Cmd(TIM3,DISABLE);
			break;
		}
	}
	finger_reset_flag = 0;
}

void finger_dock_back(void) {
	int counter = 0;
	Encoder_Get();	// flash the encoder
	LED1_ON();
	PWM_SetCompare1(DEGREE90_SPEED);
	while (1)
	{
		counter += Encoder_Get();
		if (counter >= DEGREE90_SPEEDMAX_DECODER_NUM) {
			PWM_SetCompare1(FINGER_STOP_SPEED);
		}
	}
}

void finger_stop(void) {
	PWM_SetCompare1(FINGER_STOP_SPEED);
	Encoder_Get();	// flash the encoder
}

	
