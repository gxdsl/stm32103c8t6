#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//开启APB2外设时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//设置GPIO口模式为推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;//选择脚B14
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	while(1)
	{
		GPIO_WriteBit(GPIOB,GPIO_Pin_14,Bit_SET);
		Delay_ms(1000);
		GPIO_WriteBit(GPIOB,GPIO_Pin_14,Bit_RESET);
		Delay_ms(1000);
	}
}
