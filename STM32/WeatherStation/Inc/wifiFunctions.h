/*
 * wifiFunctions.h
 *
 *  Created on: 9 okt. 2018
 *      Author: djleg
 */

#ifndef WIFIFUNCTIONS_H_
#define WIFIFUNCTIONS_H_
#endif /* WIFIFUNCTIONS_H_ */

#define MAX_WIFI_BUFFER_SIZE (uint32_t)512
#define STANDARD_WIFI_BUFFER_SIZE (uint32_t)80

#include "main.h"
#include "stm32f0xx_hal.h"
#include "cmsis_os.h"

#include "string.h"

extern UART_HandleTypeDef huart1;

void initialize_wifi_connection();
void send_data_to_server(int16_t temperature, uint16_t humidity, uint16_t pressure);


