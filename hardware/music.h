#ifndef __MUSIC_H
#define __MUSIC_H

void music_Init(void);
void serialmusic_Init(void);

void volume(int volume);
void UART1SendByte(unsigned char SendData);
void playmusic(unsigned char dat);


#endif
