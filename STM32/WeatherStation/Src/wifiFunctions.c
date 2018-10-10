/*
 * wifiFunctions.c
 *
 *  Created on: 9 okt. 2018
 *      Author: djleg
 */
#include "wifiFunctions.h"


const char hostname[] = "student.aii.avans.nl";
const char portNumber[] = "80\0";
const char postRequest[] =
"POST /ENG/dallegie/ HTTP/1.1\n"
"Host: student.aii.avans.nl\n"
"Content-Type: application/x-www-form-urlencoded\n";
const char content[] = "humidity=54&pressure=1010&temperature=242------WebKitFormBoundary7MA4YWxkTrZu0gW--\n\n";

/*
"humidity=60&pressure=1018&temperature=253"
"------WebKitFormBoundary7MA4YWxkTrZu0gW--\n\n";
*/

const char head[] =	"HEAD / HTTP/1.1\n"
					"Host: student.aii.avans.nl\n\n";

void send_data_to_esp(uint8_t str[], uint8_t rsp[]){
	HAL_UART_Transmit(&huart1, str, strlen(str), 100);
	do{
		HAL_UART_Receive(&huart1, (uint8_t *)str, STANDARD_WIFI_BUFFER_SIZE, 100);
	}while(!strstr(str,rsp) && rsp != NULL);
	memset(str,'\0',STANDARD_WIFI_BUFFER_SIZE);
}

void initialize_wifi_connection(){
		uint8_t buffer[STANDARD_WIFI_BUFFER_SIZE];

		sprintf(buffer, "AT+CWMODE=1\r\n");
		send_data_to_esp(buffer, "OK");

		sprintf(buffer, "AT+CWJAP=\"baulusma\",\"frikandel\"\r\n");
		send_data_to_esp(buffer, "OK");
}

void send_data_to_server(int16_t temperature, uint16_t humidity, uint16_t pressure){
	char buffer[300];
	char contentLength[80];
	char atCommand[30];
	//"humidity=%d&pressure=%d&temperature=%d\n", 60, 1010, 232

	sprintf(buffer, "AT+CIPMUX=0\r\n");
	send_data_to_esp(buffer, "OK");

	sprintf(buffer, "AT+CIPMODE=0\r\n");
	send_data_to_esp(buffer, "OK");

	sprintf(buffer, "AT+CIPSTART=\"TCP\",\"%s\",%s\r\n",hostname,portNumber);
	send_data_to_esp(buffer, "OK");

	sprintf(contentLength, "Content-Length: %d\n", strlen(content));

	strcpy(buffer, postRequest);
	strcat(buffer, contentLength);
	strcat(buffer, content);

	sprintf(atCommand, "AT+CIPSEND=%d\r\n", strlen(buffer));
	send_data_to_esp(atCommand, "OK");

	send_data_to_esp(buffer, "SEND OK");

	osDelay(5000);

	sprintf(buffer, "AT+CIPCLOSE\r\n");
	send_data_to_esp(buffer, "OK");

	while(1);

}
