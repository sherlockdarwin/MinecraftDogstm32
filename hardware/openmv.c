#include "stm32f10x.h"                  // Device header
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define OPENMV_BUF_LEN 30
char openmv_buf[OPENMV_BUF_LEN];
uint16_t buf_index = 0;
volatile uint16_t openmvgetflag = 0;
int openmv_X = 0;
int openmv_Y = 0;
int openmv_R = 0;


void openmv_Init(void)
{
	GPIO_InitTypeDef serialopenmvGPIO;
	serialopenmvGPIO.GPIO_Mode = GPIO_Mode_IPU;
	serialopenmvGPIO.GPIO_Pin = GPIO_Pin_11;
	serialopenmvGPIO.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&serialopenmvGPIO);
	
	USART_InitTypeDef serialopenmvUSART;
	serialopenmvUSART.USART_BaudRate = 9600;
	serialopenmvUSART.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	serialopenmvUSART.USART_Mode = USART_Mode_Rx;
	serialopenmvUSART.USART_Parity = USART_Parity_No;
	serialopenmvUSART.USART_StopBits = USART_StopBits_1;
	serialopenmvUSART.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART3,&serialopenmvUSART);
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
	
	NVIC_InitTypeDef openmvNVIC;
	openmvNVIC.NVIC_IRQChannel = USART3_IRQn;
	openmvNVIC.NVIC_IRQChannelCmd = ENABLE;
	openmvNVIC.NVIC_IRQChannelPreemptionPriority = 0;
	openmvNVIC.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&openmvNVIC);
	
	
	USART_Cmd(USART3, ENABLE);

}



uint16_t getflag(void)
{
	if(openmvgetflag == 1)
	{
		openmvgetflag = 0;
		return 1;
	}
	return 0;
}



void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
    {
        uint8_t recv_data = USART_ReceiveData(USART3);
        
        if(recv_data != '\n' && buf_index < OPENMV_BUF_LEN - 1)
        {
            openmv_buf[buf_index++] = recv_data;
        }
        else
        {
            openmv_buf[buf_index] = '\0';
            sscanf(openmv_buf, "%d,%d,%d", &openmv_X, &openmv_Y, &openmv_R);
            openmvgetflag = 1;
            buf_index = 0;
			TIM_SetCounter(TIM3, 0);
        }
        
        USART_ClearITPendingBit(USART3, USART_IT_RXNE);

    }
	
}


int getOpenMV_X(void)
{
    return openmv_X;
}

int getOpenMV_Y(void)
{
    return openmv_Y;
}

int getOpenMV_R(void)
{
    return openmv_R;
}

