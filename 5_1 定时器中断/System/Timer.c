#include "stm32f10x.h"                  // Device header

extern uint32_t CNT;

void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_InternalClockConfig(TIM2);	//使用内部时钟模式TIM2
	
	TIM_TimeBaseInitTypeDef TimerBase_Initstructure;
	TimerBase_Initstructure.TIM_ClockDivision = TIM_CKD_DIV1;	//指定时钟分频,DV1为不分频
	TimerBase_Initstructure.TIM_CounterMode = TIM_CounterMode_Up;	//计数模式为向上计数
	TimerBase_Initstructure.TIM_Period = 10000 - 1;	//ARR自动重装器的值
	TimerBase_Initstructure.TIM_Prescaler = 7200 - 1;	//Psc预分频器的值
	TimerBase_Initstructure.TIM_RepetitionCounter = 0;	//重复计数器的值，0为不使用
	TIM_TimeBaseInit(TIM2,&TimerBase_Initstructure);
	
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);	//清除中断位，避免初始化时进入中断
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);	//使能中断,开启中断
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//NVIC优先组配置
	
	NVIC_InitTypeDef NVIC_Initstructure;
	NVIC_Initstructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_Initstructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_Initstructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_Initstructure);
	
	TIM_Cmd(TIM2,ENABLE);	//中断输出控制，开启中断
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)	//获取中断标志位并判断
	{
		CNT++;	
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
}
