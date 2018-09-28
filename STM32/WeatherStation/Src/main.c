/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * This notice applies to any and all portions of this file
 * that are not between comment pairs USER CODE BEGIN and
 * USER CODE END. Other portions of this file, whether
 * inserted by the user or by software development tools
 * are owned by their respective copyright owners.
 *
 * Copyright (c) 2018 STMicroelectronics International N.V.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted, provided that the following conditions are met:
 *
 * 1. Redistribution of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of other
 *    contributors to this software may be used to endorse or promote products
 *    derived from this software without specific written permission.
 * 4. This software, including modifications and/or derivative works of this
 *    software, must execute solely and exclusively on microcontroller or
 *    microprocessor devices manufactured by or for STMicroelectronics.
 * 5. Redistribution and use of this software other than as permitted under
 *    this license is void and will automatically terminate your rights under
 *    this license.
 *
 * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
 * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
 * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f0xx_hal.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */
#include "string.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

osThreadId taskTemperatureHandle;
osThreadId taskHumidityHandle;
osThreadId taskPressureHandle;
osMutexId I2CBusMutexHandle;
osMutexId UART2BusMutexHandle;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
void StartTaskTemperature(void const * argument);
void startTaskHumidity(void const * argument);
void startTaskPressure(void const * argument);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 *
 * @retval None
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration----------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_USART2_UART_Init();
	MX_I2C1_Init();
	MX_USART1_UART_Init();
	/* USER CODE BEGIN 2 */

	/* USER CODE END 2 */

	/* Create the mutex(es) */
	/* definition and creation of I2CBusMutex */
	osMutexDef(I2CBusMutex);
	I2CBusMutexHandle = osMutexCreate(osMutex(I2CBusMutex));

	/* definition and creation of UART2BusMutex */
	osMutexDef(UART2BusMutex);
	UART2BusMutexHandle = osMutexCreate(osMutex(UART2BusMutex));

	/* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
	/* USER CODE END RTOS_MUTEX */

	/* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
	/* USER CODE END RTOS_SEMAPHORES */

	/* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
	/* USER CODE END RTOS_TIMERS */

	/* Create the thread(s) */
	/* definition and creation of taskTemperature */
	osThreadDef(taskTemperature, StartTaskTemperature, osPriorityNormal, 0,
			128);
	taskTemperatureHandle = osThreadCreate(osThread(taskTemperature), NULL);

	/* definition and creation of taskHumidity */
	osThreadDef(taskHumidity, startTaskHumidity, osPriorityIdle, 0, 128);
	taskHumidityHandle = osThreadCreate(osThread(taskHumidity), NULL);

	/* definition and creation of taskPressure */
	osThreadDef(taskPressure, startTaskPressure, osPriorityIdle, 0, 128);
	taskPressureHandle = osThreadCreate(osThread(taskPressure), NULL);

	/* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
	/* USER CODE END RTOS_THREADS */

	/* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
	/* USER CODE END RTOS_QUEUES */

	/* Start scheduler */
	osKernelStart();

	/* We should never get here as control is now taken by the scheduler */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {

		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */

	}
	/* USER CODE END 3 */

}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {

	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_PeriphCLKInitTypeDef PeriphClkInit;

	/**Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = 16;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
	RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1
			| RCC_PERIPHCLK_I2C1;
	PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
	PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure the Systick interrupt time
	 */
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

	/**Configure the Systick
	 */
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 3, 0);
}

/* I2C1 init function */
static void MX_I2C1_Init(void) {

	hi2c1.Instance = I2C1;
	hi2c1.Init.Timing = 0x2000090E;
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if (HAL_I2C_Init(&hi2c1) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure Analogue filter
	 */
	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE)
			!= HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure Digital filter
	 */
	if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

}

/* USART1 init function */
static void MX_USART1_UART_Init(void) {

	huart1.Instance = USART1;
	huart1.Init.BaudRate = 38400;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart1) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

}

/* USART2 init function */
static void MX_USART2_UART_Init(void) {

	huart2.Instance = USART2;
	huart2.Init.BaudRate = 38400;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart2) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

}

/** Configure pins as 
 * Analog
 * Input
 * Output
 * EVENT_OUT
 * EXTI
 */
static void MX_GPIO_Init(void) {

	GPIO_InitTypeDef GPIO_InitStruct;

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE()
	;
	__HAL_RCC_GPIOF_CLK_ENABLE()
	;
	__HAL_RCC_GPIOA_CLK_ENABLE()
	;
	__HAL_RCC_GPIOB_CLK_ENABLE()
	;

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin : B1_Pin */
	GPIO_InitStruct.Pin = B1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : LD2_Pin */
	GPIO_InitStruct.Pin = LD2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
#define STANDARD_TIMEOUT (uint8_t)100
#define UART_MUTEX_TIMEOUT (uint8_t)100
#define STANDARD_OS_DELAY (uint32_t)1000
#define ADDRESS_OF_is7021 (uint8_t) 0x40 << 1
#define MSB_OFFSET (uint8_t) 8
#define STANDARD_MUTEX_TAKE_TIME (uint32_t)100
#define PRESSURE_MUTEX_TAKE_TIME (uint32_t)500
#define MAX_BUFFER_SIZE (uint8_t)40

#define ABORTED (uint8_t) 0
#define SUCCES (uint8_t) 1

#define BUFFER_SIZE_CALIBRATION_DATA (uint8_t)24
#define FORCE_MODE (uint8_t)0b00100101
#define MEMORY_NOT_READY_FLAG (uint8_t)0x8
#define BUFFER_SIZE_RAW_DATA (uint8_t)6
#define MSB_SHIFT (uint8_t)12
#define LSB_SHIFT (uint8_t)4
#define XLSB_SHIFT (uint8_t)4
#define INVALID_PRESSURE (double)0
#define PASCAL_TO_MILLIBAR_DIVISION_FACTOR (double)100

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

void getCalibrationData(uint16_t slaveAddress, uint16_t calibrationDataAddress,
		calibrationData * data) {
	uint8_t calibBuffer[BUFFER_SIZE_CALIBRATION_DATA];

	HAL_I2C_Mem_Read(&hi2c1, slaveAddress, calibrationDataAddress, sizeof(uint8_t), calibBuffer, BUFFER_SIZE_CALIBRATION_DATA,STANDARD_TIMEOUT);

	data->dig_T1 = ((uint16_t) calibBuffer[1] << 8) | calibBuffer[0];
	data->dig_T2 = ((uint16_t) calibBuffer[3] << 8) | calibBuffer[2];
	data->dig_T3 = ((uint16_t) calibBuffer[5] << 8) | calibBuffer[4];
	data->dig_P1 = ((uint16_t) calibBuffer[7] << 8) | calibBuffer[6];
	data->dig_P2 = ((uint16_t) calibBuffer[9] << 8) | calibBuffer[8];
	data->dig_P3 = ((uint16_t) calibBuffer[11] << 8) | calibBuffer[10];
	data->dig_P4 = ((uint16_t) calibBuffer[13] << 8) | calibBuffer[12];
	data->dig_P5 = ((uint16_t) calibBuffer[15] << 8) | calibBuffer[14];
	data->dig_P6 = ((uint16_t) calibBuffer[17] << 8) | calibBuffer[16];
	data->dig_P7 = ((uint16_t) calibBuffer[19] << 8) | calibBuffer[18];
	data->dig_P8 = ((uint16_t) calibBuffer[21] << 8) | calibBuffer[20];
	data->dig_P9 = ((uint16_t) calibBuffer[23] << 8) | calibBuffer[22];
}

void forceBMP280Measurement(uint16_t slaveAddress, uint16_t modeRegisterAddress,
		uint16_t statusRegisterAddress) {
	uint8_t buffer;
	uint8_t modeData = FORCE_MODE;
	HAL_I2C_Mem_Write(&hi2c1, slaveAddress, modeRegisterAddress, sizeof(uint8_t), &modeData, sizeof(buffer), STANDARD_TIMEOUT);
	do {
		HAL_I2C_Mem_Read(&hi2c1, slaveAddress, statusRegisterAddress, sizeof(uint8_t), &buffer, sizeof(buffer), STANDARD_TIMEOUT);
	} while (buffer & MEMORY_NOT_READY_FLAG );
}

void getRawMeasurmentData(uint16_t slaveAddress,
		uint16_t rawDataRegisterAddress, rawData * data) {
	uint8_t dataBuffer[BUFFER_SIZE_RAW_DATA ];

	HAL_I2C_Mem_Read(&hi2c1, slaveAddress, rawDataRegisterAddress, sizeof(uint8_t), dataBuffer, sizeof(dataBuffer) / sizeof(uint8_t), STANDARD_TIMEOUT);

	data->pMSB = dataBuffer[0];
	data->pLSB = dataBuffer[1];
	data->pXLSB = dataBuffer[2];
	data->tMSB = dataBuffer[3];
	data->tLSB = dataBuffer[4];
	data->tXLSB = dataBuffer[5];
}

void parseData(rawData * raw, parsedData * data) {
	uint32_t lsb;
	uint32_t msb;
	uint32_t xlsb;

	msb = (uint32_t) raw->pMSB << MSB_SHIFT;
	lsb = (uint32_t) raw->pLSB << LSB_SHIFT;
	xlsb = (uint32_t) raw->pXLSB >> XLSB_SHIFT;
	data->parsedPressureData = msb | lsb | xlsb;

	msb = (uint32_t) raw->tMSB << MSB_SHIFT;
	lsb = (uint32_t) raw->tLSB << LSB_SHIFT;
	xlsb = (uint32_t) raw->tXLSB >> XLSB_SHIFT;
	data->parsedTemperatureData = msb | lsb | xlsb;
}

void calculateTemperature(parsedData * parsed, calibrationData * calibData) {
	double var1;
	double var2;

	var1 = ((double) parsed->parsedTemperatureData) / 16384.0
			- ((double) calibData->dig_T1) / 1024.0;
	var1 = var1 * ((double) calibData->dig_T2);
	var2 = (((double) parsed->parsedTemperatureData) / 131072.0
			- ((double) calibData->dig_T1) / 8192.0);
	var2 = (var2 * var2) * ((double) calibData->dig_T3);
	parsed->t_fine = (int32_t) (var1 + var2);
	parsed->temperature = (var1 + var2) / 5120.0;
}

void calculatePressure(parsedData * parsed, calibrationData * calibData) {
	double var1;
	double var2;
	double var3;
	double pressure;

	var1 = ((double) parsed->t_fine / 2.0) - 64000.0;
	var2 = var1 * var1 * ((double) calibData->dig_P6) / 32768.0;
	var2 = var2 + var1 * ((double) calibData->dig_P5) * 2.0;
	var2 = (var2 / 4.0) + (((double) calibData->dig_P4) * 65536.0);
	var3 = ((double) calibData->dig_P3) * var1 * var1 / 524288.0;
	var1 = (var3 + ((double) calibData->dig_P2) * var1) / 524288.0;
	var1 = (1.0 + var1 / 32768.0) * ((double) calibData->dig_P1);
	/* avoid exception caused by division by zero */
	if (var1) {
		pressure = 1048576.0 - (double) parsed->parsedPressureData;
		pressure = (pressure - (var2 / 4096.0)) * 6250.0 / var1;
		var1 = ((double) calibData->dig_P9) * pressure * pressure
				/ 2147483648.0;
		var2 = pressure * ((double) calibData->dig_P8) / 32768.0;
		pressure = pressure
				+ (var1 + var2 + ((double) calibData->dig_P7)) / 16.0;

	} else { /* Invalid case */
		pressure = INVALID_PRESSURE;
	}

	parsed->pressure = pressure / PASCAL_TO_MILLIBAR_DIVISION_FACTOR;
}

double getPressure() {
	uint16_t modeRegisterAddress = 0xF4;
	uint16_t statusRegisterAddress = 0xF3;
	uint16_t slaveAddressBMP280 = 0x77 << 1;
	uint16_t rawDataRegisterAddress = 0xF7;
	uint16_t startAddressCalibData = 0x88;

	calibrationData calibData;
	parsedData parsed;
	rawData raw;

	xSemaphoreTake(I2CBusMutexHandle, PRESSURE_MUTEX_TAKE_TIME);
	// Get calibration data
	getCalibrationData(slaveAddressBMP280, startAddressCalibData, &calibData);

	// Force sensor to measure and wait for sensor to be done
	forceBMP280Measurement(slaveAddressBMP280, modeRegisterAddress,
			statusRegisterAddress);

	//get raw data for calculations
	getRawMeasurmentData(slaveAddressBMP280, rawDataRegisterAddress, &raw);
	xSemaphoreGive(I2CBusMutexHandle);
	// Parse data to make ready for calculation and delete raw data
	parseData(&raw, &parsed);

	// Calculate temperature
	calculateTemperature(&parsed, &calibData);

	// Calculate pressure
	calculatePressure(&parsed, &calibData);

	//return parsed.pressure;
	return parsed.pressure;
}

/*
 INPUT: requires pointer to a buffer to store the two data bytes, a pointer to the command to be send
 and the size of the buffer in bytes.
 OUTPUT: returns a zero (ABORTED) if the buffer was not large enough and a one (SUCCES) if retrieval was succesful
 FUNCTION: gets data of from the is7021
 */
uint8_t get_data_from_is7021(uint8_t * buffer, uint8_t * command,
		uint8_t bufferSize) {
	if (bufferSize < 2)
		return ABORTED ;
	else {
		xSemaphoreTake(I2CBusMutexHandle, STANDARD_MUTEX_TAKE_TIME);
		HAL_I2C_Master_Transmit(&hi2c1, ADDRESS_OF_is7021, command, 1, STANDARD_TIMEOUT);
		osDelay(23);
		HAL_I2C_Master_Receive(&hi2c1, ADDRESS_OF_is7021, buffer, 2, STANDARD_TIMEOUT);
		xSemaphoreGive(I2CBusMutexHandle);
		return SUCCES ;
	}

}

/*
 INPUT: the input of the function requires a pointer to a buffer, with the temprature data
 stored in the first two bytes, and the length of the buffer
 The minimal amount of space required is 4 bytes.
 OUTPUT: returns a zero (ABORTED) if the buffer was not large enough and a one (SUCCES) if conversion was succcesfull
 FUNCTION: this functions takes the first two bytes in the buffer and
 converts them to a string and stores this string in the first three bytes of the buffer.
 The buffer always requires a storage space in the back for a point within the string.
 */
uint8_t convert_data_to_temp_string(uint8_t * buffer, uint8_t bufferLength) {
	if (bufferLength < 5)
		return ABORTED ;
	else {
		uint16_t data = buffer[0] << MSB_OFFSET | buffer[1];
		int tempratureTimesTen = (int) roundf(
				((((data * 175.72) / 65536) - 46.85) * 100));
		itoa(tempratureTimesTen, (char *) buffer, 10);
		buffer[bufferLength - 1] = buffer[2];
		buffer[2] = '.';
		buffer[3] = buffer[bufferLength - 1];
		buffer[4] = '\0';
		return SUCCES ;
	}
}

/*
 INPUT: the input of the function requires a pointer to a buffer, with the humidity data
 stored in the first two bytes, and the length of the buffer
 The minimal amount of space required in the buffer is 2 bytes.
 OUTPUT: returns a zero (ABORTED) if the buffer was not large enough and a one (SUCCES) if conversion was succcesfull
 FUNCTION: this functions takes the first two bytes in the buffer and
 converts them to a string and stores this string in the first two bytes of the buffer.
 */
uint8_t convert_data_to_humid_string(uint8_t * buffer, uint8_t bufferLength) {
	if (bufferLength < 3)
		return ABORTED ;
	else {
		uint16_t data = buffer[0] << MSB_OFFSET | buffer[1];
		int humidTimesTen = (int) roundf(((((data * 125) / 65536) - 6) * 100));
		itoa(humidTimesTen, (char *) buffer, 10);
		buffer[2] = '\0';
		return SUCCES ;
	}
}
/* USER CODE END 4 */

/* StartTaskTemperature function */
void StartTaskTemperature(void const * argument) {

	/* USER CODE BEGIN 5 */
	uint8_t commandLoadTemp = 0xE3;

	uint8_t buffer[ MAX_BUFFER_SIZE];

	/* Infinite loop */
	for (;;) {
		get_data_from_is7021(buffer, &commandLoadTemp, MAX_BUFFER_SIZE);

		convert_data_to_temp_string(buffer, MAX_BUFFER_SIZE);
		uint8_t str[5];
		strcpy(str,buffer);
		sprintf(buffer, "%s degree Celsius\n", str);
		xSemaphoreTake(UART2BusMutexHandle, UART_MUTEX_TIMEOUT);
		HAL_UART_Transmit(&huart2,buffer, strlen(buffer), 100);
		xSemaphoreGive(UART2BusMutexHandle);
		osDelay(STANDARD_OS_DELAY);
	}
	/* USER CODE END 5 */
}

/* startTaskHumidity function */
void startTaskHumidity(void const * argument) {
	uint8_t commandLoadHumidity = 0xE5;

	uint8_t buffer[MAX_BUFFER_SIZE];

	/* Infinite loop */
	for (;;) {
		get_data_from_is7021(buffer, &commandLoadHumidity, MAX_BUFFER_SIZE);

		convert_data_to_humid_string(buffer, MAX_BUFFER_SIZE);
		uint8_t str[3];
		strcpy(str,buffer);
		sprintf(buffer, "%s percent humid\n", str);
		xSemaphoreTake(UART2BusMutexHandle, UART_MUTEX_TIMEOUT);
		HAL_UART_Transmit(&huart2, buffer, strlen(buffer), STANDARD_TIMEOUT);
		xSemaphoreGive(UART2BusMutexHandle);
		osDelay(STANDARD_OS_DELAY);
	}
}

/* startTaskPressure function */
void startTaskPressure(void const * argument) {
	/* USER CODE BEGIN startTaskPressure */
	/* Infinite loop */
	uint8_t buffer[MAX_BUFFER_SIZE];
	memset(buffer, '\n', MAX_BUFFER_SIZE);

	for (;;) {
		double pressure = getPressure();
		sprintf(buffer, "%d millibar\n", (uint32_t)pressure);
		xSemaphoreTake(UART2BusMutexHandle, UART_MUTEX_TIMEOUT);
		HAL_UART_Transmit(&huart2, buffer, (uint8_t)strlen(buffer), STANDARD_TIMEOUT);
		xSemaphoreGive(UART2BusMutexHandle);
		osDelay(STANDARD_OS_DELAY);
	}
	/* USER CODE END startTaskPressure */
}

/**
 * @brief  Period elapsed callback in non blocking mode
 * @note   This function is called  when TIM1 interrupt took place, inside
 * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
 * a global variable "uwTick" used as application time base.
 * @param  htim : TIM handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	/* USER CODE BEGIN Callback 0 */

	/* USER CODE END Callback 0 */
	if (htim->Instance == TIM1) {
		HAL_IncTick();
	}
	/* USER CODE BEGIN Callback 1 */

	/* USER CODE END Callback 1 */
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  file: The file name as string.
 * @param  line: The line in file as a number.
 * @retval None
 */
void _Error_Handler(char *file, int line) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	 tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
