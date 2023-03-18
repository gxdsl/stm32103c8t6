#include "stm32f10x.h"                  // Device header

void Lightsensor_Init(void) 
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IPD;	//下拉输入模式
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_8;		
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstructure);
}

uint8_t Lightsensor_Get(void)
{
	uint8_t LightsensorNum = 0;
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8) == 1)
	{
		LightsensorNum = 1;
	}
	return LightsensorNum;
}
