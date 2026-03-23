#include "stm32f10x.h"                  // Device header
#include "music.h" 

extern uint16_t music;

void musictimer_Init(void)
{
	
	TIM_TimeBaseInitTypeDef musictimerTIM;
	musictimerTIM.TIM_ClockDivision = TIM_CKD_DIV1;
	musictimerTIM.TIM_CounterMode = TIM_CounterMode_Up;
	musictimerTIM.TIM_Period = 45000 - 1;
	musictimerTIM.TIM_Prescaler = 64000 - 1;
	musictimerTIM.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &musictimerTIM);
	
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
	
	
	NVIC_InitTypeDef musictimerNVIC;
	musictimerNVIC.NVIC_IRQChannel = TIM4_IRQn;
	musictimerNVIC.NVIC_IRQChannelCmd = ENABLE;
	musictimerNVIC.NVIC_IRQChannelPreemptionPriority = 3;
	musictimerNVIC.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&musictimerNVIC);
	
	TIM_Cmd(TIM4, ENABLE);
}


void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)
	{
		playmusic(1);
        music = 1;
        GPIO_SetBits(GPIOB, GPIO_Pin_8);
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}

