#ifndef __PWM_H__
#define __PWM_H__

void PWMLED_Init(void);	//PWM呼吸灯
void PWMServo_Init(void); //舵机
void Set_CCR(uint32_t CCR);
void Set_PSC(uint32_t PSC);

#endif
