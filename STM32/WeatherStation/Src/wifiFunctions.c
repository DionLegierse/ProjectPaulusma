/*
 * wifiFunctions.c
 *
 *  Created on: 9 okt. 2018
 *      Author: djleg
 */
#include "wifiFunctions.h"

const char ssid[] = "baulusma";
const char password[] = "frikandel";

const char hostname[] = "student.aii.avans.nl";
const char portNumber[] = "80\0";
const char postRequest[] =
"POST /ENG/dallegie/ HTTP/1.1\n"
"Host: student.aii.avans.nl\n"
"Content-Type: application/x-www-form-urlencoded\n";

/*const char head[] =	"HEAD / HTTP/1.1\n"
					"Host: student.aii.avans.nl\n\n";*/

void send_data_to_esp(uint8_t str[], uint8_t rsp[], uint16_t amountOfAttempts){
	char buffer[80];
	uint16_t attempt = 0;

	memset(buffer,'\0',STANDARD_WIFI_BUFFER_SIZE);
	//send data to the esp8266
	HAL_UART_Transmit(&huart1, str, strlen(str), 100);
	//wait for the response
	do{
		++attempt;
		HAL_UART_Receive(&huart1, (uint8_t *)buffer, STANDARD_WIFI_BUFFER_SIZE, UART_RECEIVE_TIME);
	}while(!strstr(buffer,rsp) && rsp != NULL && (attempt <= amountOfAttempts));
}

void initialize_wifi_connection(){
		uint8_t buffer[STANDARD_WIFI_BUFFER_SIZE];

		//setup a the esp8266 in client mode
		sprintf(buffer, "AT+CWMODE=1\r\n");
		send_data_to_esp(buffer, "OK", STANDARD_ATTEMPT_TIMEOUT);

		//connect the baulusma to a network
		sprintf(buffer, "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, password);
		send_data_to_esp(buffer, "OK", CONNECT_TIMEOUT);

		//Set the ESP8266 to only have one connection
		sprintf(buffer, "AT+CIPMUX=0\r\n");
		send_data_to_esp(buffer, "OK", STANDARD_ATTEMPT_TIMEOUT);

		sprintf(buffer, "AT+CIPMODE=0\r\n");
		send_data_to_esp(buffer, "OK", STANDARD_ATTEMPT_TIMEOUT);
}

void send_data_to_server(int16_t temperature, uint16_t humidity, uint16_t pressure){
	char buffer[HTTP_HEADER_BUFFER_SIZE];
	char contentLength[HTTP_HEADER_LINE_LENGTH];
	char content[HTTP_HEADER_LINE_LENGTH];
	char atCommand[HTTP_HEADER_LINE_LENGTH];

	//Start a TCP connection with the given address on the given portnumber
	sprintf(buffer, "AT+CIPSTART=\"TCP\",\"%s\",%s\r\n",hostname,portNumber);
	send_data_to_esp(buffer, "OK", STANDARD_ATTEMPT_TIMEOUT);

	//Prepare the body of the HTTP request
	sprintf(content, "humidity=%d&pressure=%d&temperature=%d", humidity, pressure, temperature);

	//Prepare the content length line of the HTTP request
	sprintf(contentLength, "Content-Length: %d\n\n", strlen(content));

	//Contruct the HTTP request
	strcpy(buffer, postRequest);
	strcat(buffer, contentLength);
	strcat(buffer, content);

	//Send the HTTP request over the TCP connection
	sprintf(atCommand, "AT+CIPSEND=%d\r\n", strlen(buffer));
	send_data_to_esp(atCommand, "OK", STANDARD_ATTEMPT_TIMEOUT);

	//Wait for the responce from the webserver
	send_data_to_esp(buffer, "</body>", RESPONCE_TIMEOUT);

	//Close the TCP connection
	sprintf(buffer, "AT+CIPCLOSE\r\n");
	send_data_to_esp(buffer, "OK", STANDARD_ATTEMPT_TIMEOUT);
}
