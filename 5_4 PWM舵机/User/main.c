#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "Delay.h"
#include "Servo.h"

int main()
{
	PWMServo_Init();
	ServoKeyOled_Init();
	while(1)
	{
	}
}

