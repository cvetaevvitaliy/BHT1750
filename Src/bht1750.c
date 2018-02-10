/*
 * bht1750.c
 *
 *  Created on: Feb 9, 2018
 *      Author: laalex
 */

#include "bht1750.h"


/**
 * Sensor I2C initialisation
 */
void bht1750_init(bht1750_config* config, bht1750* handle){

	// Set configuration
	handle->config = *config;

	// Prepare state buffer
	handle->buffer[0] = BHT1750_POWER_UP;

	// Write POWER_UP state on the sensor
	HAL_I2C_Master_Transmit(handle->config.i2c, BHT1750_I2C_ADDRESS, handle->buffer, 1, 100);

	// Prepare state buffer
	handle->buffer[0] = BHT1750_CONT_HRES_MODE;

	// Save the state into configuration
	handle->config.state = BHT1750_CONT_HRES_MODE;

	// Write HRES continuous mode state on the sensor
	HAL_I2C_Master_Transmit(handle->config.i2c, BHT1750_I2C_ADDRESS, handle->buffer, 1, 100);

	// Wait for the first reading
	HAL_Delay(180);
}


/**
 * Return LUX reading
 */
int bht1750_getValue(bht1750* handle){
	// Calculated returnValue
	int returnValue = 0.0;

	// Get the value in rawLux
	HAL_I2C_Master_Receive(handle->config.i2c, BHT1750_I2C_ADDRESS, &handle->buffer, 2, 100);
	handle->rawLuxValue = handle->buffer[0]<<8 | handle->buffer[1]; // Create 16 bit value

	// Calculate actual lux value
	returnValue = (handle->rawLuxValue / 1.2) / 65535;

	return returnValue;
}
