#include "stm32f10x.h"               // Device header
#include "string.h" 

void Serial_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	
	USART_InitTypeDef USART_Initstructure;
	USART_Initstructure.USART_BaudRate = 9600;
	USART_Initstructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Initstructure.USART_Mode = USART_Mode_Tx;		//发送模式
	USART_Initstructure.USART_Parity = USART_Parity_No;
	USART_Initstructure.USART_StopBits = USART_StopBits_1;		//停止位占一位
	USART_Initstructure.USART_WordLength= USART_WordLength_8b;
	USART_Init(USART2,&USART_Initstructure);	
	
	USART_Cmd(USART2,ENABLE);
}

void Serial_SentByte(uint8_t dBit)
{
	USART_SendData(USART2,dBit);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) == RESET);		//标志位是否为空
}

void Serial_SentString(uint8_t ByteArray[])
{
	for(int i=0;ByteArray[i]!='\0';i++)
	{
		Serial_SentByte(ByteArray[i]);
	}
}

