#include "stm32f10x.h"                  // Device header
#include "OLED.h"

int main(void)
{
	OLED_Init();
	OLED_ShowChar(1,1,'A');
	OLED_ShowString(1,3,"DAISHILIN");
	OLED_ShowNum(2,1,12345,5);
	OLED_ShowSignedNum(2,8,223,3);
	OLED_ShowBinNum(3,1,123,10);
	OLED_ShowHexNum(4,1,88888,10);
//	OLED_Clear();
}

