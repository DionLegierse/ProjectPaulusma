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

void send_data_to_esp(uint8_t str[]){
	HAL_UART_Transmit(&huart1, str, strlen(str), 100);
	do{
		HAL_UART_Receive(&huart1, (uint8_t *)str, STANDARD_WIFI_BUFFER_SIZE, 100);
	}while(!strstr(str,"OK"));
	memset(str,'\0',STANDARD_WIFI_BUFFER_SIZE);
}

void initialize_wifi_connection(){
		uint8_t buffer[STANDARD_WIFI_BUFFER_SIZE];

		sprintf(buffer, "AT+CWMODE=1\r\n");
		send_data_to_esp(buffer);

		sprintf(buffer, "AT+CWJAP=\"baulusma\",\"frikandel\"\r\n");
		send_data_to_esp(buffer);
}

void send_data_to_server(int16_t temperature, uint16_t humidity, uint16_t pressure){
	char buffer[STANDARD_WIFI_BUFFER_SIZE];

	sprintf(buffer, "AT+CIPMUX=0\r\n");
	send_data_to_esp(buffer);

	sprintf(buffer, "AT+CIPSTART=\"TCP\",\"%s\",%s\r\n",hostname,portNumber,portNumber);
	send_data_to_esp(buffer);

	sprintf(buffer, "AT+CIPCLOSE\r\n");
	send_data_to_esp(buffer);

}
