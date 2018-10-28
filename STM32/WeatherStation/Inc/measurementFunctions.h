/*
 * measurementFunctions.h
 *
 *  Created on: 2 okt. 2018
 *      Author: djleg
 */

#ifndef MEASUREMENTFUNCTIONS_H_
#define MEASUREMENTFUNCTIONS_H_

#endif /* MEASUREMENTFUNCTIONS_H_ */

#include "main.h"
#include "stm32f0xx_hal.h"
#include "cmsis_os.h"

extern I2C_HandleTypeDef hi2c1;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

extern osMutexId I2CBusMutexHandle;

//Custom data structures for BMP280
typedef struct {
	uint16_t dig_T1;
	int16_t dig_T2;
	int16_t dig_T3;
	uint16_t dig_P1;
	int16_t dig_P2;
	int16_t dig_P3;
	int16_t dig_P4;
	int16_t dig_P5;
	int16_t dig_P6;
	int16_t dig_P7;
	int16_t dig_P8;
	int16_t dig_P9;
} calibrationData;

typedef struct {
	uint8_t tMSB;
	uint8_t tLSB;
	uint8_t tXLSB;
	uint8_t pMSB;
	uint8_t pLSB;
	uint8_t pXLSB;
} rawData;

typedef struct {
	uint32_t parsedPressureData;
	uint32_t parsedTemperatureData;
	int32_t t_fine;
	double temperature;
	double pressure;
} parsedData;

#define STANDARD_TIMEOUT (uint8_t)100
#define UART_MUTEX_TIMEOUT (uint8_t)100
#define STANDARD_OS_DELAY (uint32_t)1000
#define ADDRESS_OF_is7021 (uint8_t) 0x40 << 1
#define MSB_OFFSET (uint8_t) 8
#define STANDARD_MUTEX_TAKE_TIME (uint32_t)100
#define PRESSURE_MUTEX_TAKE_TIME (uint32_t)500
#define MAX_BUFFER_SIZE (uint8_t)40
#define MEASURE_DELAY (uint32_t)50000

#define ABORTED (uint8_t) 0
#define SUCCES (uint8_t) 1
#define READY (uint8_t)1
#define NOT_READY (uint8_t)0

#define BUFFER_SIZE_CALIBRATION_DATA (uint8_t)24
#define FORCE_MODE (uint8_t)0b00100101
#define MEMORY_NOT_READY_FLAG (uint8_t)0x8
#define BUFFER_SIZE_RAW_DATA (uint8_t)6
#define MSB_SHIFT (uint8_t)12
#define LSB_SHIFT (uint8_t)4
#define XLSB_SHIFT (uint8_t)4
#define INVALID_PRESSURE (double)0
#define PASCAL_TO_MILLIBAR_DIVISION_FACTOR (double)100

double get_pressure();
void get_data_from_is7021(uint8_t * buffer, uint8_t * command);
int16_t convert_data_temp_to_int(uint8_t * buffer);
uint16_t convert_data_humid_to_int(uint8_t * buffer);

