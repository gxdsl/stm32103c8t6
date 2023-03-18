#include "stm32f10x.h"                  // Device header
#include "Delay.h"

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//开启APB2外设时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//设置GPIO口模式为推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;//选择脚A1
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	while(1)
	{
		uint16_t Leds = 0x0001; 
		for(int32_t i=0;;i++)
		{
			GPIO_Write(GPIOA,Leds<<i);
			Delay_ms(500);
			if(i == 7) i=-1;
		}
	}
}
