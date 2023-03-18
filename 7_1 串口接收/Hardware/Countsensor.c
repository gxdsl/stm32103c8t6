#include "stm32f10x.h"                  // Device header
uint32_t Count = 0;
void CountSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource6);	//选择PinB5为中断源
	
	EXTI_InitTypeDef EXTI_Initstructure;
	EXTI_Initstructure.EXTI_Line = EXTI_Line6;
	EXTI_Initstructure.EXTI_LineCmd = ENABLE;
	EXTI_Initstructure.EXTI_Mode = EXTI_Mode_Interrupt;	//模式为中断触发
	EXTI_Initstructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;	//下降沿触发
	EXTI_Init(&EXTI_Initstructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_Initstructure;
	NVIC_Initstructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_Initstructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority = 1;	//抢占优先级
	NVIC_Initstructure.NVIC_IRQChannelSubPriority = 1;	//响应优先级
	NVIC_Init(&NVIC_Initstructure);
}
uint32_t Count_Getnum(void)
{
	return Count;
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line6) == SET)
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6) == SET)
		{
			Count++;
		}
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
}
