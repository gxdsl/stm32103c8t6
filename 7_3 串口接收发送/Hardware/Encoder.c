#include "stm32f10x.h"                  // Device header

void EncoderInterpace_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);	
	
	TIM_TimeBaseInitTypeDef TimBase_Initstructure;
	TimBase_Initstructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TimBase_Initstructure.TIM_CounterMode = TIM_CounterMode_Up;
	TimBase_Initstructure.TIM_Period = 65536 - 1;	 //ARR
	TimBase_Initstructure.TIM_Prescaler = 1 - 1;	//PSC
	TimBase_Initstructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3,&TimBase_Initstructure);
	
	TIM_ICInitTypeDef IC_Initstructure;
	TIM_ICStructInit(&IC_Initstructure);
	IC_Initstructure.TIM_Channel = TIM_Channel_1;	//通道1
	IC_Initstructure.TIM_ICFilter = 0xf;
//	IC_Initstructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInit(TIM2,&IC_Initstructure);
	TIM_ICStructInit(&IC_Initstructure);
	IC_Initstructure.TIM_Channel = TIM_Channel_2;	//通道2
	IC_Initstructure.TIM_ICFilter = 0xf;
//	IC_Initstructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInit(TIM2,&IC_Initstructure);
	
	TIM_EncoderInterfaceConfig(TIM2,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	
	TIM_Cmd(TIM2,ENABLE);
}

int32_t Get_EINum(void)
{
	return TIM_GetCounter(TIM2);
}
