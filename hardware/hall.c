#include "stm32f10x.h"                  // Device header

extern uint16_t falling;

void hall_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitTypeDef hallGPIO;
	hallGPIO.GPIO_Mode = GPIO_Mode_IPU;    //上拉输入
	hallGPIO.GPIO_Pin = GPIO_Pin_1;
	hallGPIO.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &hallGPIO);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);
	
	EXTI_InitTypeDef hallEXTI;
	hallEXTI.EXTI_Line = EXTI_Line1;
	hallEXTI.EXTI_LineCmd = ENABLE;
	hallEXTI.EXTI_Mode = EXTI_Mode_Interrupt;
	hallEXTI.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_Init(&hallEXTI);
	
	NVIC_InitTypeDef hallNVIC;
	hallNVIC.NVIC_IRQChannel = EXTI1_IRQn;
	hallNVIC.NVIC_IRQChannelCmd = ENABLE;
	hallNVIC.NVIC_IRQChannelPreemptionPriority = 1;
	hallNVIC.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&hallNVIC);
	
	
}

uint8_t hall_get(void)
{
	return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1);
}


void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1) == SET)
	{
		falling =  (hall_get() == 0);
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

