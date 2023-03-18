#include "stm32f10x.h"                  // Device header
#include "Timer.h"
#include "OLED.h"

uint32_t CNT = 0;

int main(void)
{
	OLED_Init();
	Timer_Init();
	OLED_ShowString(1,1,"COUNT:");
	while(1)
	{
		OLED_ShowNum(1,7,CNT,5);
		OLED_ShowNum(2,7,TIM_GetCounter(TIM2),5);
	}
}

