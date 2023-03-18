#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led.h"
#include "key.h"
uint8_t KeyNum;
int main(void)
{
	LED_Init();
	Key_Init();
	while(1)
	{
		KeyNum = Key_Getnum();
		if(KeyNum == 1)
		{
			LED_Switch();
		}
	}
}

