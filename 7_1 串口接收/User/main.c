#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Serial.h"

int main()
{
	OLED_Init();
	Serial_Init();
//	Serial_SentByte('a');
	Serial_SentString("123456");
	while(1)
	{
		
	}
}
