/*
 * wifiFunctions.c
 *
 *  Created on: 9 okt. 2018
 *      Author: djleg
 */
#include "wifiFunctions.h"

void initialize_wifi_connection(){
		uint8_t buffer[STANDARD_WIFI_BUFFER_SIZE];
		sprintf(buffer, "AT+GMR\r\n");
		HAL_UART_Transmit_IT(&huart1, buffer, strlen(buffer));

		sprintf(buffer, "AT+CWMODE=1\r\n");
		HAL_UART_Transmit_IT(&huart1, buffer, strlen(buffer));

		sprintf(buffer, "AT+CWJAP=\"baulusma\",\"frikandel\"\r\n");
		HAL_UART_Transmit_IT(&huart1, buffer, strlen(buffer));
}

