#include "stm32f10x.h"                  // Device header
#include "hall.h"
#include "music.h"
#include "car.h"
#include "openmv.h"
#include "timer.h"
#include "musictimer.h"


uint16_t falling;
uint16_t music = 1;

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	TIM_InternalClockConfig(TIM2);
	TIM_InternalClockConfig(TIM3);
	TIM_InternalClockConfig(TIM4);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	hall_Init();
	music_Init();
	serialmusic_Init();
	car_Init();
	openmv_Init();
	timer_Init();
	musictimer_Init()
	volume(25);
	playmusic(1);
	
	while(1)
	{
		//音乐
		if(falling&&music==1)
		{
			volume(30);
			GPIO_ResetBits(GPIOB, GPIO_Pin_8);
			music = 2;
			TIM_SetCounter(TIM4, 0);
		}
		
		//接收openmv
		if(getflag() == 1)
        {
            int cx = getOpenMV_X();
            int cy = getOpenMV_Y();
            int r = getOpenMV_R();
            
            if(r > 23)
            {
                carstop();
            }
            else 
            {
                if(cx < 57) turnleft();
                else if(cx > 183) turnright();
                else forward();
            }
        }
		
	}
}

