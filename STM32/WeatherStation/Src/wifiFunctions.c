/*
 * wifiFunctions.c
 *
 *  Created on: 9 okt. 2018
 *      Author: djleg
 */
#include "wifiFunctions.h"

const char hostname[] = "student.aii.avans.nl/ENG/dallegie/\0";
const char portNumber[] = "80\0";
const char

void initialize_wifi_connection(){
		uint8_t buffer[STANDARD_WIFI_BUFFER_SIZE];
		sprintf(buffer, "AT+GMR\r\n");
		HAL_UART_Transmit_IT(&huart1, buffer, strlen(buffer));

		sprintf(buffer, "AT+CWMODE=1\r\n");
		HAL_UART_Transmit_IT(&huart1, buffer, strlen(buffer));

		sprintf(buffer, "AT+CWJAP=\"baulusma\",\"frikandel\"\r\n");
		HAL_UART_Transmit_IT(&huart1, buffer, strlen(buffer));
}

void send_data_to_server(int16_t temperature, uint16_t humidity, uint16_t pressure){
	char str[MAX_WIFI_BUFFER_SIZE] = "\0";

	sprintf(str, "AT+CIPMUX=1\r\n");
	HAL_UART_Transmit_IT(&huart1, str, strlen(str));

	do{
		HAL_UART_Receive_IT(&huart1, str,MAX_WIFI_BUFFER_SIZE);
	}while(strcmp(str, "OK"));
}

