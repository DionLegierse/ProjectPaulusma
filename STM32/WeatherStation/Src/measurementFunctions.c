/*
 * measurementFunctions.c
 *
 *  Created on: 2 okt. 2018
 *      Author: djleg
 */
#include "measurementFunctions.h"

void getCalibrationData(uint16_t slaveAddress, uint16_t calibrationDataAddress, calibrationData * data) {
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

void get_data_from_is7021(uint8_t * buffer, uint8_t * command) {
	xSemaphoreTake(I2CBusMutexHandle, STANDARD_MUTEX_TAKE_TIME);
	HAL_I2C_Master_Transmit(&hi2c1, ADDRESS_OF_is7021, command, 1, STANDARD_TIMEOUT);
	osDelay(23);
	HAL_I2C_Master_Receive(&hi2c1, ADDRESS_OF_is7021, buffer, 2, STANDARD_TIMEOUT);
	xSemaphoreGive(I2CBusMutexHandle);
}

int16_t convert_data_temp_to_int(uint8_t * buffer) {
	int16_t data = buffer[0] << MSB_OFFSET | buffer[1];
	return (int16_t) roundf(((((data * 175.72) / 65536) - 46.85) * 10));
}

uint16_t convert_data_humid_to_int(uint8_t * buffer) {
	uint16_t data = buffer[0] << MSB_OFFSET | buffer[1];
	return (uint16_t) roundf(((((data * 125) / 65536) - 6)));
}
