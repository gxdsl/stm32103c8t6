#include "stm32f10x.h"               // Device header

//uint8_t Serial_RxData;
uint8_t Serial_RxFlag;

uint8_t Serial_RxPacket[4];
uint8_t Serial_TxPacket[4];

void Serial_ReceiveInit(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);	//初始化USART2的时钟
	
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	
	USART_InitTypeDef USART_Initstructure;
	USART_Initstructure.USART_BaudRate = 9600;
	USART_Initstructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Initstructure.USART_Mode = USART_Mode_Tx;		//发送模式
	USART_Initstructure.USART_Parity = USART_Parity_No;
	USART_Initstructure.USART_StopBits = USART_StopBits_1;		//停止位占一位
	USART_Initstructure.USART_WordLength= USART_WordLength_8b;
	USART_Init(USART2,&USART_Initstructure);	
	
	USART_Cmd(USART2,ENABLE);
}

void Serial_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);	//初始化USART2的时钟
	
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_AF_PP;		//Tx
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IPU;		//Rx
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	
	USART_InitTypeDef USART_Initstructure;
	USART_Initstructure.USART_BaudRate = 9600;
	USART_Initstructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Initstructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;		//发送+接收模式
	USART_Initstructure.USART_Parity = USART_Parity_No;
	USART_Initstructure.USART_StopBits = USART_StopBits_1;		//停止位占一位
	USART_Initstructure.USART_WordLength= USART_WordLength_8b;
	USART_Init(USART2,&USART_Initstructure);
	
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);

	USART_Cmd(USART2,ENABLE);
}

void Serial_SendByte(uint8_t dBit)
{
	USART_SendData(USART2,dBit);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) == RESET);		//标志位是否为空
}

void Serial_SendString(uint8_t ByteArray[])
{
	for(int i=0;ByteArray[i]!='\0';i++)
	{
		Serial_SendByte(ByteArray[i]);
	}
}

uint8_t Serial_GetRxFlag(void)
{
	if (Serial_RxFlag == 1)
	{
		Serial_RxFlag = 0;
		return 1;
	}
	return 0;
}

//uint8_t Serial_GetRxData(void)
//{
//	return Serial_RxData;
//}

//void USART2_IRQHandler(void)
//{
//	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
//	{
//		Serial_RxData = USART_ReceiveData(USART2);
//		Serial_RxFlag = 1;
//		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
//	}
//}

void USART2_IRQHandler(void)
{
	static uint8_t pRxPacket = 0;
	static uint8_t Serial_PacketFlag;
	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
	{
		uint8_t RxData = USART_ReceiveData(USART2);
		if (Serial_PacketFlag == 0)
		{
			if (RxData == 0xFF)
			{
				Serial_PacketFlag = 1;
				pRxPacket = 0;
			}
		}
		else if (Serial_PacketFlag == 1)
		{
			Serial_RxPacket[pRxPacket] = RxData;
			pRxPacket ++;
			if (pRxPacket >= 4)
			{
				Serial_PacketFlag = 2;
			}
		}
		else if (Serial_PacketFlag == 2)
		{
			if (RxData == 0xFE)
			{
				Serial_PacketFlag = 0;
				Serial_RxFlag = 1;
			}
		}
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	}
}

void Serial_SendPacket(void)
{
	Serial_SendByte(0xFF);
	Serial_SendString(Serial_TxPacket);
	Serial_SendByte(0xFE);
}

