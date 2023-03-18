#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开启APB2外设时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//设置GPIO口模式为推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//选择脚A1
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	// GPIO_SetBits(GPIOA,GPIO_Pin_1); //设置指定端口为高电平
	// GPIO_SetBits(GPIOA,GPIO_Pin_1); //设置指定端口为低电平
	while(1)
	{
		GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_SET); //设置指定端口为高电平
		Delay_ms(1000);
		GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET); //设置指定端口为低电平
		Delay_ms(1000);
	}
}
