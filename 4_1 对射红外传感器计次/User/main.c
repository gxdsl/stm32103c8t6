#include "stm32f10x.h"                  // Device header
#include "Countsensor.h"
#include "OLED.h"

int main(void)
{
	OLED_Init();
	CountSensor_Init();
	OLED_ShowString(1,1,"COUNT:");
	while(1)
	{
		OLED_ShowNum(1,7,Count_Getnum(),4);
	}
}

