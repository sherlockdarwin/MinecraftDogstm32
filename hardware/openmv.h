#ifndef __OPENMV_H
#define __OPENMV_H

void openmv_Init(void);
void UART3set(unsigned char GetData);
uint16_t getflag(void);
void USART3_IRQHandler(void);
int getOpenMV_X(void);
int getOpenMV_Y(void);
int getOpenMV_R(void);


#endif
