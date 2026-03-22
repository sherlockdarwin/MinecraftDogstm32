#include "stm32f10x.h"  // Device header

#define AIN1   GPIO_Pin_4
#define AIN2    GPIO_Pin_5
#define PWMA   GPIO_Pin_1

#define BIN1   GPIO_Pin_6
#define BIN2    GPIO_Pin_7
#define PWMB   GPIO_Pin_2

#define STBY    GPIO_Pin_11

void car_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	//runcar
	GPIO_InitTypeDef carGPIO;
	carGPIO.GPIO_Mode = GPIO_Mode_Out_PP;
	carGPIO.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_11;
	carGPIO.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&carGPIO);
	GPIO_SetBits(GPIOA, GPIO_Pin_11);
	
	//pmwcar
	GPIO_InitTypeDef carpwmGPIO;
	carpwmGPIO.GPIO_Mode = GPIO_Mode_AF_PP;
	carpwmGPIO.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2;
	carpwmGPIO.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&carpwmGPIO);
	
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;    //ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 36  - 1;   //PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef carTIM;
	TIM_OCStructInit(&carTIM);
	carTIM.TIM_OCMode = TIM_OCMode_PWM1;
	carTIM.TIM_OCPolarity = TIM_OCPolarity_High;
	carTIM.TIM_OutputState = TIM_OutputState_Enable;
	carTIM.TIM_Pulse = 0;                 //CCR
	 
	TIM_OC2Init(TIM2,&carTIM);
	TIM_OC3Init(TIM2,&carTIM);
	
	TIM_Cmd(TIM2, ENABLE);
}


void writepwma(uint16_t pwma)
{
	TIM_SetCompare2(TIM2, pwma);
}


void writepwmb(uint16_t pwmb)
{
	TIM_SetCompare3(TIM2, pwmb);
}


void gogogo_Init(void)
{
	GPIO_ResetBits(GPIOA, AIN1);
	GPIO_SetBits(GPIOA, AIN2);
	GPIO_SetBits(GPIOA, BIN1);
	GPIO_ResetBits(GPIOA, BIN2);
}


void forward(void)
{
	gogogo_Init();
	writepwma(50);
	writepwmb(50);
}	


void turnleft(void)
{
	gogogo_Init();
	writepwma(50);
	writepwmb(20);
}


void turnright(void)
{
	gogogo_Init();
	writepwma(20);
	writepwmb(50);
}


void carstop(void)
{
	GPIO_SetBits(GPIOA, AIN1);
	GPIO_SetBits(GPIOA, AIN2);
	GPIO_SetBits(GPIOA, BIN1);
	GPIO_SetBits(GPIOA, BIN2);
	writepwma(0);
	writepwmb(0);
}
	

