#include "stm32f10x.h"                  // Device header

void Buzzer_Init(void) 
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IPU;	//上拉输入模式
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_8;		
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
}

void Buzzer_Switch(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_8) == 0)	//读取输出脚Pin4是否为0
	{
		GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_SET);
	}
	else
	{
		GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_RESET);
	}
}
