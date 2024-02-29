#ifndef __SERIAL_H__
#define __SERIAL_H__

extern uint8_t Serial_TxPacket[];
extern uint8_t Serial_RxPacket[];

void Serial_Init(void);
void Serial_ReceiveInit(void);
void Serial_SendByte(uint8_t dBit);
void Serial_SendString(uint8_t ByteArray[]);

uint8_t Serial_GetRxFlag(void);
uint8_t Serial_GetRxData(void);

void Serial_SendPacket(void);

#endif
