#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "IC.h"
#include "OLED.h"

int main()
{
	OLED_Init();
	PWMLED_Init();
	IC_Init();
	OLED_ShowString(1,1,"Freq:00000Hz");
	
	Set_PSC(720 - 1);			//Freq = 72M / (PSC + 1) / 100
	Set_CCR(50);				//Duty = CCR / 100
	
	while(1)
	{
		OLED_ShowNum(1,6,IC_GetFreq(),5);
	}
}
