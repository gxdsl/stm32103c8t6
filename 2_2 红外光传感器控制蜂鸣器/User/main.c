#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "buzzer.h"
#include "lightsensor.h"

uint8_t LightsensorNum;
int main(void)
{
	Lightsensor_Init();
	Buzzer_Init();
	while(1)
	{
		LightsensorNum = Lightsensor_Get();
		if(LightsensorNum == 1)
		{
			Buzzer_Switch();
		}
	}
	
}

