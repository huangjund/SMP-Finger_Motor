#include "stm32f10x.h"
#include "Finger_Motor.h"
#include "LED.h"
#include "PWM.h"
#include "Encoder.h"
#include "config.h"

extern int16_t finger_reset_flag;

void finger_moveInternal_(void) {
	int counter = 0;
	Encoder_Get();	// flash the encoder
	PWM_SetCompare1(DEGREE90_SPEED);
	
	TIM_Cmd(TIM3, ENABLE);
	while (!finger_reset_flag && counter < DEGREE90_SPEEDMAX_DECODER_NUM)
	{
		counter += Encoder_Get();
	}
	finger_stop();
	TIM_Cmd(TIM3,DISABLE);
	finger_reset_flag = 0;
	TIM_SetCounter(TIM3,0);
}

void reset2origin_finger(void) {
	Encoder_Get();	// flash the encoder
	LED1_OFF(); // set the rotation direction
	PWM_SetCompare1(FINGER_RESET_SPEED);
	TIM_Cmd(TIM3, ENABLE);
	while(!finger_reset_flag) {}
	TIM_Cmd(TIM3, DISABLE);
	finger_reset_flag = 0;
	TIM_SetCounter(TIM3,0);
}

void finger_down(void) {
	LED1_ON();	// set the rotation direction
	
	finger_moveInternal_();
}

void finger_dock_back(void) {
	LED1_OFF();	// set the rotation direction
	
	finger_moveInternal_();
}

void finger_stop(void) {
	PWM_SetCompare1(FINGER_STOP_SPEED);
	Encoder_Get();	// flash the encoder
}
	
