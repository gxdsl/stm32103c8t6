#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "key.h"
#include "OLED.h"

void ServoKeyOled_Init(void)
{
	uint32_t Angle = 0;
	Key_Init();
	OLED_Init();
	OLED_ShowString(2,1,"Angle:");
	while(1)
	{
		if(Key_Getnum() == 1)
		{
			Angle += 30;
			if(Angle > 180) Angle = 0;
		}
		OLED_ShowNum(2,7,Angle,3);
		Set_CCR(Angle * 2000 / 180 + 500);
	}
	
}
