#include "stm32f10x.h"                  // Device header

void music_Init(void)
{
	
	GPIO_InitTypeDef musicGPIO;
	musicGPIO.GPIO_Mode = GPIO_Mode_Out_PP;
	musicGPIO.GPIO_Pin = GPIO_Pin_8;
	musicGPIO.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&musicGPIO);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_8);
}


void serialmusic_Init(void)
{
	GPIO_InitTypeDef serialmusicGPIO;
	serialmusicGPIO.GPIO_Mode = GPIO_Mode_AF_PP;
	serialmusicGPIO.GPIO_Pin = GPIO_Pin_9;
	serialmusicGPIO.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&serialmusicGPIO);
	
	USART_InitTypeDef serialmusicUSART;
	serialmusicUSART.USART_BaudRate = 9600;
	serialmusicUSART.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	serialmusicUSART.USART_Mode = USART_Mode_Tx;
	serialmusicUSART.USART_Parity = USART_Parity_No;
	serialmusicUSART.USART_StopBits = USART_StopBits_1;
	serialmusicUSART.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&serialmusicUSART);
	
	USART_Cmd(USART1, ENABLE);
}


void UART1SendByte(unsigned char SendData)
{	   
		USART_SendData(USART1,SendData);
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	    
}


void playmusic(unsigned char dat)
{
	unsigned char  music_code[6] = {0X7E,0X04,0X03,0X00,0X01,0XEF};	
	int i;
	music_code[4] = dat;
	for(i=0;i<6;i++)
	{
		UART1SendByte(music_code[i]);
	}
}

void volume(unsigned char dat)
{
	unsigned char  volume_code[6] = {0X7E,0X03,0X06,0X00,0X01,0XEF};	
	int i;
	volume_code[4] = dat;
	for(i=0;i<6;i++)
	{
		UART1SendByte(volume_code[i]);
	}
}

