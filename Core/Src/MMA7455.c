/*
 * MMA7455.c
 *
 *  Created on: May 19, 2018
 *      Author: Jake Moomaw
 */

#include "stm32l4xx_hal.h"
#include "MMA7455.h"
#include "main.h"
#define PI  (3.14159265F);

uint8_t tx_buff20[]={0};
uint8_t tx_buff21[]={0};
uint8_t rx_buff2[]={0};

SPI_HandleTypeDef *spi_handler = &hspi1;
//I2C_HandleTypeDef *i2c_instance = &hi2c1;			//Change this to the I2C bus that you are using


void MMA7455_Init_8G()
{
	//uint8_t init_byte = MMA7455_8g_init_byte;

	tx_buff20[0] = 0x9a; //adress<<1
	tx_buff21[0] = 0x9d; //value
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, tx_buff20, 1, 10000);
	HAL_SPI_Transmit(&hspi1, tx_buff21, 1, 10000);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_SET);

	tx_buff20[0] = 0xac; //adress<<1
	tx_buff21[0] = 0x01; //value
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, tx_buff20, 1, 10000);
	HAL_SPI_Transmit(&hspi1, tx_buff21, 1, 10000);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_SET);

	//HAL_I2C_Mem_Write(&hspi1, MMA7455_I2C_ADDRESS, MMA7455_init_reg, 1, &init_byte, 1, 10000);
}

int8_t MMA7455_Read_8Bit_X(void)
{

	tx_buff20[0] = 0x0c; //adress<<1
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, tx_buff20, 1, 10000);
	HAL_SPI_Receive(spi_handler, rx_buff2, 1, 1000);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_SET);

	int8_t signed_xval = rx_buff2[0];
	return signed_xval;
}
int8_t MMA7455_Read_8Bit_Y(void)
{
	tx_buff20[0] = 0x0e; //adress<<1
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, tx_buff20, 1, 10000);
	HAL_SPI_Receive(spi_handler, rx_buff2, 1, 1000);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_SET);

	int8_t signed_yval = rx_buff2[0];
	return signed_yval;
}
int8_t MMA7455_Read_8Bit_Z(void)
{
	tx_buff20[0] = 0x10; //adress<<1
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, tx_buff20, 1, 10000);
	HAL_SPI_Receive(spi_handler, rx_buff2, 1, 1000);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_SET);

	int8_t signed_zval = rx_buff2[0];
	return signed_zval;
}


int16_t MMA7455_Read_10Bit_X(void)
{


	tx_buff20[0] = 0x00; //LSB BITS
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, tx_buff20, 1, 10000);
	HAL_SPI_Receive(spi_handler, rx_buff2, 1, 1000);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_SET);
	uint8_t temp_msb = rx_buff2[0];
	tx_buff20[0] = 0x02; //MSB BITS
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, tx_buff20, 1, 10000);
	HAL_SPI_Receive(spi_handler, rx_buff2, 1, 1000);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_SET);

	uint16_t temp = (rx_buff2[0]<<8) | temp_msb;
	int16_t ret_val = (int16_t)temp;
	if(temp>511){
		ret_val = (int16_t)temp-1024;
	}
	return ret_val;
}
int16_t MMA7455_Read_10Bit_Y(void)
{
	tx_buff20[0] = 0x04; //MSB BITS
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, tx_buff20, 1, 10000);
	HAL_SPI_Receive(spi_handler, rx_buff2, 1, 1000);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_SET);
	uint8_t temp_msb = rx_buff2[0];
	tx_buff20[0] = 0x06; //LSB BITS
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, tx_buff20, 1, 10000);
	HAL_SPI_Receive(spi_handler, rx_buff2, 1, 1000);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_SET);

	uint16_t temp = (rx_buff2[0]<<8) | temp_msb;
	int16_t ret_val = (int16_t)temp;
	if(temp>511){
		ret_val = (int16_t)temp-1024;
	}
	return ret_val;
}
int16_t MMA7455_Read_10Bit_Z(void)
{
	tx_buff20[0] = 0x08; //MSB BITS
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, tx_buff20, 1, 10000);
	HAL_SPI_Receive(spi_handler, rx_buff2, 1, 1000);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_SET);
	uint8_t temp_msb = rx_buff2[0];
	tx_buff20[0] = 0x0A; //LSB BITS
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, tx_buff20, 1, 10000);
	HAL_SPI_Receive(spi_handler, rx_buff2, 1, 1000);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4,  GPIO_PIN_SET);

	uint16_t temp = (rx_buff2[0]<<8) | temp_msb;
	int16_t ret_val = (int16_t)temp;
	if(temp>511){
		ret_val = (int16_t)temp-1024;
	}
	return ret_val;
}



/* These three functions call the two registers that supply the 10-bit values for the three axes.  Since it reads two
 * registers per axis, it is slower but more accurate.
 */


// The pitch and roll functions are based off of the 8-bit reads.

float MMA7455_Read_Pitch(void)
{
	float MMA7455_pitch_denom;
	float MMA7455_pitch_sqrt;
	float MMA7455_pitch;
	float MMA7455_pitch_num;
	int8_t MMA7455_sign = 1;
	if (MMA7455_Read_10Bit_Z() < 0)
	{
		MMA7455_sign = -1;
	}
	MMA7455_pitch_denom = MMA7455_Read_10Bit_Y() * MMA7455_Read_10Bit_Y() + MMA7455_Read_10Bit_Z() * MMA7455_Read_10Bit_Z();
	MMA7455_pitch_sqrt = sqrt(MMA7455_pitch_denom);
	MMA7455_pitch_num = MMA7455_Read_10Bit_X();
	MMA7455_pitch = (atan2f(MMA7455_pitch_num, MMA7455_sign * MMA7455_pitch_sqrt) * 180) / PI;
	return MMA7455_pitch;

}
float MMA7455_Read_Roll(void)
{
	float MMA7455_roll_denom;
	float MMA7455_roll_sqrt;
	float MMA7455_roll;
	float MMA7455_roll_num;
	int8_t MMA7455_sign = 1;
	if (MMA7455_Read_10Bit_Z() < 0)
	{
		MMA7455_sign = -1;
	}
	MMA7455_roll_denom = MMA7455_Read_10Bit_X() * MMA7455_Read_10Bit_X() + MMA7455_Read_10Bit_Z() * MMA7455_Read_10Bit_Z();
	MMA7455_roll_sqrt = sqrt(MMA7455_roll_denom);
	MMA7455_roll_num = MMA7455_Read_10Bit_Y();
	MMA7455_roll = (atan2f(MMA7455_roll_num, MMA7455_sign * MMA7455_roll_sqrt) * 180) / PI;
	return MMA7455_roll;
}




