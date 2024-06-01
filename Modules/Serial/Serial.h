#ifndef __SERIAL_H__
#define __SERIAL_H__

#include "moduleInit.h"

void serialWrite(UART_HandleTypeDef *huart , uint8_t* buffer, uint8_t len);
void serialPrint( UART_HandleTypeDef *huart , const char *fmt, ...);
void addRXSerialData(uint8_t* data, uint8_t size);
uint8_t readSerial();
bool serialAvailable();

#endif