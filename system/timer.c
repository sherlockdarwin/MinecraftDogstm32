#include "stm32f10x.h"                  // Device header
#include "car.h" 

void timer_Init(void)
{
	
	TIM_TimeBaseInitTypeDef timerTIM;
	timerTIM.TIM_ClockDivision = TIM_CKD_DIV1;
	timerTIM.TIM_CounterMode = TIM_CounterMode_Up;
	timerTIM.TIM_Period = 15000 - 1;
	timerTIM.TIM_Prescaler = 7200 - 1;
	timerTIM.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &timerTIM);
	
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	
	
	NVIC_InitTypeDef timerNVIC;
	timerNVIC.NVIC_IRQChannel = TIM3_IRQn;
	timerNVIC.NVIC_IRQChannelCmd = ENABLE;
	timerNVIC.NVIC_IRQChannelPreemptionPriority = 2;
	timerNVIC.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&timerNVIC);
	
	TIM_Cmd(TIM3, ENABLE);
}


void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
	{
		carstop();
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}

