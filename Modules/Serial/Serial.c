#include "Serial.h"

uint8_t RX_data[256];
uint16_t rx_data_position= 0;

bool serialAvailable()
{
	return rx_data_position > 0;
}

uint8_t readSerial()
{
	if (rx_data_position == 0) return 0;
	uint8_t ret_data = RX_data[rx_data_position];
	rx_data_position -= 1;
	return ret_data;
}

void addRXSerialData(uint8_t* data, uint8_t size)
{
	if (rx_data_position == 256)return;
	for ( int i = 0; i < size; i++ )
	{
		if (rx_data_position == 256 ) break;
		RX_data[rx_data_position] = data[rx_data_position];
		rx_data_position += 1;
	}
}

void serialWrite(UART_HandleTypeDef *huart , uint8_t* buffer, uint8_t len)
{
	HAL_UART_Transmit(huart, (uint8_t*)buffer, len, HAL_MAX_DELAY);
}

void serialPrint(UART_HandleTypeDef *huart ,const char *fmt, ...)
{
  static char buffer[256];
  va_list args;
  va_start(args, fmt);
  vsnprintf(buffer, sizeof(buffer), fmt, args);
  va_end(args);
  int len = strlen(buffer);
  HAL_UART_Transmit(huart, (uint8_t*)buffer, len, HAL_MAX_DELAY);
}
