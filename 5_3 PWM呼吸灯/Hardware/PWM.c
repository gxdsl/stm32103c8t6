#include "stm32f10x.h"                  // Device header

void PWMLED_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	
//	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE);	//管脚重映射
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);	//管教重映射
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	
	TIM_InternalClockConfig(TIM2);	//使用内部时钟
	
	TIM_TimeBaseInitTypeDef TimeBase_Initstructure;
	TimeBase_Initstructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TimeBase_Initstructure.TIM_CounterMode = TIM_CounterMode_Up;
	TimeBase_Initstructure.TIM_Period = 72 - 1;	//ARR自动重装器的值
	TimeBase_Initstructure.TIM_Prescaler = 100 - 1;	//PSC预分频器的值
	TimeBase_Initstructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TimeBase_Initstructure);
	
	TIM_OCInitTypeDef TimOC_Initstructure;
	TIM_OCStructInit(&TimOC_Initstructure);	//初始化结构体
	TimOC_Initstructure.TIM_OCMode = TIM_OCMode_PWM1;	//设置输出比较模式
	TimOC_Initstructure.TIM_OCPolarity = TIM_OCPolarity_High;  //设置输出比较极性，高为不变
	TimOC_Initstructure.TIM_OutputState = TIM_OutputState_Enable;	//设置输出使能
	TimOC_Initstructure.TIM_Pulse = 50;	//设置CCR
	TIM_OC1Init(TIM2,&TimOC_Initstructure);
	
	TIM_Cmd(TIM2,ENABLE);
}


void Set_CCR(uint32_t CCR)
{
	TIM_SetCompare1(TIM2,CCR);
}
