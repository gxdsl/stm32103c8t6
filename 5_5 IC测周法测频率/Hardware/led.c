#include "stm32f10x.h"                  // Device header

void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);	
}

void LED_Switch(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_4) == 0)	//读取输出脚Pin4是否为0
	{
		GPIO_WriteBit(GPIOA,GPIO_Pin_4,Bit_SET);
	}
	else
	{
		GPIO_WriteBit(GPIOA,GPIO_Pin_4,Bit_RESET);
	}
}
