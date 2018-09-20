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

uint8_t startAddressCalibData = 0x88;

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
}calibData;

typedef struct{
    uint8_t MSB;
    uint8_t LSB;
    uint8_t XLSB;
}rawPressureData;

typedef struct{
    uint8_t MSB;
    uint8_t LSB;
    uint8_t XLSB;
}rawTempData;

typedef struct{
    uint32_t parsedPressureData;
    uint32_t parsedTemperatureData;
}parsedData;

double getPressure(){
    const uint16_t modeRegisterAddress = 0xF4;
    const uint16_t statusRegisterAddress = 0xF3;
    const uint16_t slaveAddressBMP280 = 0x77 << 1;
    const uint16_t temperatureRegisterAddress = 0xFA;
    const uint16_t pressureRegisterAddress = 0xF7;

    uint8_t modeRegisterData = 0b00100101;
    uint8_t buffer[10];

    rawPressureData rawPressure;
    rawTempData rawTemp;

    HAL_I2C_Mem_Write(&hi2c1, slaveAddressBMP280, modeRegisterAddress, 1, &modeRegisterData, 1, 100);
    do{
         HAL_I2C_Mem_Read(&hi2c1, slaveAddressBMP280, statusRegisterAddress, 1, buffer, 1, 100);
    }while(buffer[0] & 0x8);

}
