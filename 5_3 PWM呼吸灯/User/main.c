#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "Delay.h"

int main()
{
	PWMLED_Init();
	uint16_t i;
	while(1)
	{
		for(i=0;i<100;i++)
		{
			Set_CCR(i);
			Delay_ms(10);
		}
	}
}

