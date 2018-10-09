/*
 * wifiFunctions.c
 *
 *  Created on: 9 okt. 2018
 *      Author: djleg
 */
#include "wifiFunctions.h"


const char hostname[] = "student.aii.avans.nl";
const char portNumber[] = "80\0";
const char postRequest1[] = "POST /ENG/dallegie/ HTTP/1.1";
const char postRequest2[] = "Host: student.aii.avans.nl";
const char postRequest3[] = "Content-Type: application/x-www-form-urlencoded";
const char postRequest4[] = "cache-control: no-cache";
//const char postRequest5[] = "humidity=60&pressure=1018&temperature=253"
const char postRequest5[] = "------WebKitFormBoundary7MA4YWxkTrZu0gW--";

void initialize_wifi_connection(){
		uint8_t buffer[STANDARD_WIFI_BUFFER_SIZE];

		sprintf(buffer, "AT+CWMODE=1\r\n");
		HAL_UART_Transmit(&huart1, buffer, strlen(buffer), 100);
		do{
			HAL_UART_Receive(&huart1, (uint8_t *)buffer, STANDARD_WIFI_BUFFER_SIZE, 100);
		}while(!strstr(buffer,"OK"));

		sprintf(buffer, "AT+CWJAP=\"baulusma\",\"frikandel\"\r\n");
		HAL_UART_Transmit(&huart1, buffer, strlen(buffer), 100);

		do{
			HAL_UART_Receive(&huart1, (uint8_t *)buffer, STANDARD_WIFI_BUFFER_SIZE, 100);
		}while(!strstr(buffer,"OK"));
}

void send_data_to_server(int16_t temperature, uint16_t humidity, uint16_t pressure){
	char buffer[STANDARD_WIFI_BUFFER_SIZE];

	sprintf(buffer, "AT+CIPMUX=1\r\n");
	HAL_UART_Transmit(&huart1, buffer, strlen(buffer), 100);
	do{
		HAL_UART_Receive(&huart1, (uint8_t *)buffer, STANDARD_WIFI_BUFFER_SIZE, 100);
	}while(!strstr(buffer, "OK"));

	sprintf(buffer, "AT+CIPSTART=0,\"TCP\",\"%s\",%s\r\n",hostname,portNumber,portNumber);
	HAL_UART_Transmit(&huart1, buffer, strlen(buffer), 100);

	do{
		HAL_UART_Receive(&huart1, (uint8_t *)buffer, STANDARD_WIFI_BUFFER_SIZE, 100);
	}while(!strstr(buffer, "OK"));


	sprintf(buffer, "CIPSEND=0,\"%s ",postRequest1);
	HAL_UART_Transmit(&huart1, buffer, strlen(buffer), 100);
	osDelay(1000);

	sprintf(buffer, "%s ",postRequest2);
	HAL_UART_Transmit(&huart1, buffer, strlen(buffer), 100);
	osDelay(1000);

	sprintf(buffer, "%s ",postRequest3);
	HAL_UART_Transmit(&huart1, buffer, strlen(buffer), 100);
	osDelay(1000);

	sprintf(buffer, "%s ",postRequest4);
	HAL_UART_Transmit(&huart1, buffer, strlen(buffer), 100);
	osDelay(1000);

	sprintf(buffer, "temperature=255&humidity=34&pressure=1002 ");
	HAL_UART_Transmit(&huart1, buffer, strlen(buffer), 100);

	sprintf(buffer, "%s\"\r\n",postRequest5);
	HAL_UART_Transmit(&huart1, buffer, strlen(buffer), 100);
	osDelay(1000);

	do{
		HAL_UART_Receive(&huart1, (uint8_t *)buffer, STANDARD_WIFI_BUFFER_SIZE, 100);
	}while(!strstr(buffer, "OK"));

	sprintf(buffer, "AT+CIPCLOSE=0\r\n");
	HAL_UART_Transmit(&huart1, buffer, strlen(buffer), 100);

	do{
		HAL_UART_Receive(&huart1, (uint8_t *)buffer, STANDARD_WIFI_BUFFER_SIZE, 100);
	}while(!strstr(buffer, "OK"));


}

