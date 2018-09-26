#pragma region proto
//proto datatypes
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;
typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef signed long int32_t;
typedef uint32_t I2C_HandleTypeDef;

//protovariables
I2C_HandleTypeDef hi2c1;

//protofunctions
HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
osDelay(uint32_t milliseconds);
#pragma endregion

#include <stdlib.h>

//Custom data structures for BMP280
typedef struct{
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
}calibrationData;

typedef struct{
    uint8_t tMSB;
    uint8_t tLSB;
    uint8_t tXLSB;
    uint8_t pMSB;
    uint8_t pLSB;
    uint8_t pXLSB;
}rawData;

typedef struct{
    uint32_t parsedPressureData;
    uint32_t parsedTemperatureData;
    int32_t t_fine;
    double temperature;
    double pressure;
}parsedData;

typedef struct{
    uint16_t modeRegisterAddress;
    uint16_t statusRegisterAddress;
    uint16_t slaveAddressBMP280;
    uint16_t rawDataRegisterAddress;
    uint16_t startAddressCalibData;
}BMP280Handle;

BMP280Handle * createBMP280Handle(
    uint16_t modeRegisterAddress,
    uint16_t statusRegisterAddress,
    uint16_t slaveAddressBMP280,
    uint16_t rawDataRegisterAddress,
    uint16_t startAddressCalibData
){
    BMP280Handle * handle = malloc(sizeof(BMP280Handle));
    handle->modeRegisterAddress = modeRegisterAddress;
    handle->statusRegisterAddress = statusRegisterAddress;
    handle->slaveAddressBMP280 = slaveAddressBMP280 << 1;
    handle->rawDataRegisterAddress = rawDataRegisterAddress;
    handle->startAddressCalibData = startAddressCalibData;
    return handle;
}

calibrationData * getCalibrationData(BMP280Handle * BMP280){
    uint8_t calibBuffer[24];
    HAL_I2C_Mem_Read(&hi2c1, BMP280->slaveAddressBMP280, BMP280->startAddressCalibData, 24, calibBuffer , 24, 100);
    calibrationData * data = malloc(sizeof(calibrationData));

    data->dig_T1 = ((uint16_t)calibBuffer[1] << 8) | calibBuffer[0];
    data->dig_T2 = (int16_t)((uint16_t)calibBuffer[3] << 8) | calibBuffer[2];
    data->dig_T3 = (int16_t)((uint16_t)calibBuffer[5] << 8) | calibBuffer[4];
    data->dig_P1 = ((uint16_t)calibBuffer[7] << 8) | calibBuffer[6];
    data->dig_P2 = (int16_t)((uint16_t)calibBuffer[9] << 8) | calibBuffer[8];
    data->dig_P3 = (int16_t)((uint16_t)calibBuffer[11] << 8) | calibBuffer[10];
    data->dig_P4 = (int16_t)((uint16_t)calibBuffer[13] << 8) | calibBuffer[12];
    data->dig_P5 = (int16_t)((uint16_t)calibBuffer[15] << 8) | calibBuffer[14];
    data->dig_P6 = (int16_t)((uint16_t)calibBuffer[17] << 8) | calibBuffer[16];
    data->dig_P7 = (int16_t)((uint16_t)calibBuffer[19] << 8) | calibBuffer[18];
    data->dig_P8 = (int16_t)((uint16_t)calibBuffer[21] << 8) | calibBuffer[20];
    data->dig_P1 = (int16_t)((uint16_t)calibBuffer[23] << 8) | calibBuffer[22];
    
    return data;    
}

void forceBMP280Measurement(BMP280Handle * BMP280){
        uint8_t buffer[1];
        uint8_t modeData = 0b00100101;
        HAL_I2C_Mem_Write(&hi2c1, BMP280->slaveAddressBMP280, BMP280->modeRegisterAddress, 1, &modeData, 1, 100);
        
        do{
            HAL_I2C_Mem_Read(&hi2c1, BMP280->slaveAddressBMP280, BMP280->statusRegisterAddress, 1, buffer, 1, 100);
        }while(buffer[0] & 0x8);
}

rawData * getRawMeasurmentData(BMP280Handle * BMP280){
    rawData * data = malloc(sizeof(rawData));
    uint8_t dataBuffer[6];
    HAL_I2C_Mem_Read(&hi2c1, BMP280->slaveAddressBMP280, BMP280->rawDataRegisterAddress, 6, dataBuffer, 6, 100);

    data->pMSB = dataBuffer[0];
    data->pLSB = dataBuffer[1];
    data->pXLSB = dataBuffer[2];
    data->tMSB = dataBuffer[3];
    data->tLSB = dataBuffer[4];
    data->tXLSB = dataBuffer[5];

    return data;
}

parsedData * parseData(rawData * raw){
    parsedData * parsed;

    uint32_t lsb;
    uint32_t msb;
    uint32_t xlsb;

    msb = (uint32_t)raw->pMSB << 12;
    lsb = (uint32_t)raw->pLSB << 4;
    xlsb = (uint32_t)raw->pXLSB >> 4;
    parsed->parsedPressureData = msb | lsb | xlsb;

    msb = (uint32_t)raw->tMSB << 12;
    lsb = (uint32_t)raw->tLSB << 4;
    xlsb = (uint32_t)raw->tXLSB >> 4;
    parsed->parsedTemperatureData = msb | lsb | xlsb;

    free(raw);

    return parsed;
}

void calculateTemperature(parsedData * parsed, calibrationData * calibData){
    double var1;
	double var2;
	double temperature_min = -40;
	double temperature_max = 85;

    var1 = ((double)parsed->parsedTemperatureData) / 16384.0 - ((double)calibData->dig_T1) / 1024.0;
    var1 = var1 * ((double)calibData->dig_T2);
    var2 = (((double)parsed->parsedTemperatureData) / 131072.0 - ((double)calibData->dig_T1) / 8192.0);
    var2 = (var2 * var2) * ((double)calibData->dig_T3);
    parsed->t_fine = (int32_t)(var1 + var2);
    parsed->temperature = (var1 + var2) / 5120.0;

    if (parsed->temperature < temperature_min)
		parsed->temperature = temperature_min;
	else if (parsed->temperature > temperature_max)
		parsed->temperature = temperature_max;

}

void calculatePressure(parsedData * parsed, calibrationData * calibData){
	double var1;
	double var2;
	double var3;
	double pressure_min = 30000.0;
	double pressure_max = 110000.0;

	var1 = ((double)parsed->t_fine / 2.0) - 64000.0;
	var2 = var1 * var1 * ((double)calibData->dig_P6) / 32768.0;
	var2 = var2 + var1 * ((double)calibData->dig_P5) * 2.0;
	var2 = (var2 / 4.0) + (((double)calibData->dig_P4) * 65536.0);
	var3 = ((double)calibData->dig_P3) * var1 * var1 / 524288.0;
	var1 = (var3 + ((double)calibData->dig_P2) * var1) / 524288.0;
	var1 = (1.0 + var1 / 32768.0) * ((double)calibData->dig_P1);
	/* avoid exception caused by division by zero */
	if (var1) {
		parsed->pressure = 1048576.0 - (double) parsed->parsedPressureData;
		parsed->pressure = (parsed->pressure - (var2 / 4096.0)) * 6250.0 / var1;
		var1 = ((double)calibData->dig_P9) * parsed->pressure * parsed->pressure / 2147483648.0;
		var2 = parsed->pressure * ((double)calibData->dig_P8) / 32768.0;
		parsed->pressure = parsed->pressure + (var1 + var2 + ((double)calibData->dig_P7)) / 16.0;

		if (parsed->pressure < pressure_min)
			parsed->pressure = pressure_min;
		else if (parsed->pressure > pressure_max)
			parsed->pressure = pressure_max;
	} else { /* Invalid case */
		parsed->pressure = pressure_min;
	}
}

double getPressure(){
    uint16_t modeRegisterAddress = 0xF4;
    uint16_t statusRegisterAddress = 0xF3;
    uint16_t slaveAddressBMP280 = 0x77;
    uint16_t rawDataRegisterAddress = 0xF7;
    uint16_t startAddressCalibData = 0x88;

    //setup handle for the BMP280
    const BMP280Handle * BMPHandle = createBMP280Handle(modeRegisterAddress, statusRegisterAddress, slaveAddressBMP280, rawDataRegisterAddress, startAddressCalibData);
    
    // Get calibration data
    const calibrationData * calibData = getCalibrationData(BMPHandle);

    // Force sensor to measure and wait for sensor to be done
    forceBMP280Measurement(BMPHandle);

    //get raw data for calculations
    const rawData * rawMeasurementData = getRawMeasurmentData(BMPHandle);

    // Parse data to make ready for calculation and delete raw data
    const parsedData * parsed = parseData(rawMeasurementData);

    // Calculate temperature
    calculateTemperature(parsed, calibData);

    // Calculate pressure
    calculatePressure(parsed,calibData);
    double pressure = parsed->pressure;

    //clean up after measurement
    free(BMPHandle);
    free(calibData);
    free(parsed);
    
    return pressure;
}
