/*
 * wifiFunctions.h
 *
 *  Created on: 9 okt. 2018
 *      Author: djleg
 */

#ifndef WIFIFUNCTIONS_H_
#define WIFIFUNCTIONS_H_
#endif /* WIFIFUNCTIONS_H_ */

#define STANDARD_WIFI_BUFFER_SIZE (uint32_t)80
#define HTTP_HEADER_LINE_LENGTH (uint32_t)50
#define HTTP_HEADER_BUFFER_SIZE (uint32_t)300

#include "main.h"
#include "stm32f0xx_hal.h"
#include "cmsis_os.h"

#include "string.h"

extern UART_HandleTypeDef huart1;

void initialize_wifi_connection();
void send_data_to_server(int16_t temperature, uint16_t humidity, uint16_t pressure);


