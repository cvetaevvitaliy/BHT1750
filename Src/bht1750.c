#include "bht1750.h"


/**
 * Sensor I2C initialisation - power up the sensor
 * @param config - pointer to BHT1750 config
 * @param handle - pointer to BHT1750 handle
 */
void bht1750_init(bht1750_config* config, bht1750* handle){

	// Set configuration
	handle->config = *config;

	// Prepare state buffer
	handle->buffer[0] = BHT1750_POWER_UP;

	// Write POWER_UP state on the sensor
	HAL_I2C_Master_Transmit(handle->config.i2c, BHT1750_I2C_ADDRESS, handle->buffer, 1, 100);
}

/**
 * Power down the sensor
 * @param handle - pointer to BHT1750 handle
 */
void bht1750_powerDown(bht1750* handle){
	// Check the current state
	if(
			handle->config.state == BHT1750_CONT_HRES_MODE ||
			handle->config.state == BHT1750_CONT_HRES_MODE2 ||
			handle->config.state == BHT1750_CONT_LRES_MODE
	   )
	{
		// If we are in continuous reading mode we can power down the sensor
		handle->config.state = BHT1750_POWER_DOWN;
		// Prepare the buffer
		handle->buffer[0] = BHT1750_POWER_DOWN;
		// Write POWER_DOWN state on the sensor
		HAL_I2C_Master_Transmit(handle->config.i2c, BHT1750_I2C_ADDRESS, handle->buffer, 1, 100);
	}
	// In one time reading mode, the sensor automatically turns off after one reading
}

/**
 * Power up the sensor
 * @param handle - pointer to BHT1750 handle
 */
void bht1750_powerUp(bht1750* handle){
	// Check the current state
	if(
			handle->config.state == BHT1750_POWER_DOWN ||
			handle->config.state == BHT1750_ONCE_HRES_MODE ||
			handle->config.state == BHT1750_ONCE_HRES_MODE2 ||
			handle->config.state == BHT1750_ONCE_LRES_MODE
	  )
	{
		// If we are in continuous reading mode we can power down the sensor
		handle->config.state = BHT1750_POWER_UP;
		// Prepare the buffer
		handle->buffer[0] = BHT1750_POWER_UP;
		// Write POWER_UP state on the sensor
		HAL_I2C_Master_Transmit(handle->config.i2c, BHT1750_I2C_ADDRESS, handle->buffer, 1, 100);
	}
}

/**
 * Reset the sensor
 * @param handle - pointer to BHT1750 handle
 */
void bht1750_reset(bht1750* handle){
	bht1750_powerDown(handle);
	bht1750_powerUp(handle);
}


/**
 * Read once the value from the sensor and then turn off the IC
 * @param handle - pointer to BHT1750 handle
 * @param state - BHT1750 mode / state
 */
int bht1750_readOnce(bht1750* handle, BHT1750_STATE state){
	// Restart the sensor
	bht1750_reset(handle);

	switch(state){
	// Read once in HRES mode
	case BHT1750_ONCE_HRES_MODE:
		// Prepare state buffer
		handle->buffer[0] = BHT1750_ONCE_HRES_MODE;
		// Write HRES continuous mode state on the sensor
		HAL_I2C_Master_Transmit(handle->config.i2c, BHT1750_I2C_ADDRESS, handle->buffer, 1, 100);
		// Wait for the first reading
		HAL_Delay(180);
		// Read lux information
		HAL_I2C_Master_Receive(handle->config.i2c, BHT1750_I2C_ADDRESS, handle->buffer, 2, 100);
		handle->rawLuxValue = handle->buffer[0]<<8 | handle->buffer[1]; // Create 16 bit value
		// Save the state into configuration - once mode will always turn off the sensor to save energy
		handle->config.state = BHT1750_POWER_DOWN;
		// Calculate and return the lux value
		return bht1750_transformValue(handle->rawLuxValue, handle->config.state);
		break;
	// Read once in HRES mode2
	case BHT1750_ONCE_HRES_MODE2:
		// Prepare state buffer
		handle->buffer[0] = BHT1750_ONCE_HRES_MODE2;
		// Write HRES continuous mode state on the sensor
		HAL_I2C_Master_Transmit(handle->config.i2c, BHT1750_I2C_ADDRESS, handle->buffer, 1, 100);
		// Wait for the first reading
		HAL_Delay(180);
		// Read lux information
		HAL_I2C_Master_Receive(handle->config.i2c, BHT1750_I2C_ADDRESS, handle->buffer, 2, 100);
		handle->rawLuxValue = handle->buffer[0]<<8 | handle->buffer[1]; // Create 16 bit value
		// Save the state into configuration - once mode will always turn off the sensor to save energy
		handle->config.state = BHT1750_POWER_DOWN;
		// Calculate and return the lux value
		return bht1750_transformValue(handle->rawLuxValue, handle->config.state);
		break;
	// Read once in LRES mode
	case BHT1750_ONCE_LRES_MODE:
		// Prepare state buffer
		handle->buffer[0] = BHT1750_ONCE_LRES_MODE;
		// Write HRES continuous mode state on the sensor
		HAL_I2C_Master_Transmit(handle->config.i2c, BHT1750_I2C_ADDRESS, handle->buffer, 1, 100);
		// Wait for the first reading
		HAL_Delay(50);
		// Read lux information
		HAL_I2C_Master_Receive(handle->config.i2c, BHT1750_I2C_ADDRESS, handle->buffer, 2, 100);
		handle->rawLuxValue = handle->buffer[0]<<8 | handle->buffer[1]; // Create 16 bit value
		// Save the state into configuration - once mode will always turn off the sensor to save energy
		handle->config.state = BHT1750_POWER_DOWN;
		// Calculate and return the lux value
		return bht1750_transformValue(handle->rawLuxValue, handle->config.state);
		break;
	// Default case -> Read once resolution mode not supported
	default:
		return 0;
		break;
	}
}


/**
 * Continuous mode reading
 * @param handle - pointer to BHT1750 handle
 * @param mode - BHT1750 mode/state
 */
int bht1750_readContinuous(bht1750* handle, BHT1750_STATE mode){

	// Check if the sensor is in power down in order to power it up
	if(handle->config.state == BHT1750_POWER_DOWN){
		bht1750_powerUp(handle);
	}

	// Check if sensor is in other continuous reading mode
	if(
			handle->config.state == BHT1750_CONT_HRES_MODE ||
			handle->config.state == BHT1750_CONT_HRES_MODE2 ||
			handle->config.state == BHT1750_CONT_LRES_MODE
	  ){
		// Reset and power up
		bht1750_reset(handle);
		bht1750_powerUp(handle);
	}


	// Init the continuous read mode
	switch(mode){
		case BHT1750_CONT_HRES_MODE:
			// Set continuous HRES mode
			// Prepare state buffer
			handle->buffer[0] = BHT1750_CONT_HRES_MODE;
			// Save the state into configuration
			handle->config.state = BHT1750_CONT_HRES_MODE;
			// Write HRES continuous mode state on the sensor
			HAL_I2C_Master_Transmit(handle->config.i2c, BHT1750_I2C_ADDRESS, handle->buffer, 1, 100);
			break;
		case BHT1750_CONT_HRES_MODE2:
			// Prepare state buffer
			handle->buffer[0] = BHT1750_CONT_HRES_MODE2;
			// Save the state into configuration
			handle->config.state = BHT1750_CONT_HRES_MODE2;
			// Write HRES continuous mode state on the sensor
			HAL_I2C_Master_Transmit(handle->config.i2c, BHT1750_I2C_ADDRESS, handle->buffer, 1, 100);
			break;
		case BHT1750_CONT_LRES_MODE:
			// Prepare state buffer
			handle->buffer[0] = BHT1750_CONT_LRES_MODE;
			// Save the state into configuration
			handle->config.state = BHT1750_CONT_LRES_MODE;
			// Write HRES continuous mode state on the sensor
			HAL_I2C_Master_Transmit(handle->config.i2c, BHT1750_I2C_ADDRESS, handle->buffer, 1, 100);
			break;
		default:
			break;
	}

	// Wait for the reading based on the reading mode
	switch(handle->config.state){
		case BHT1750_CONT_HRES_MODE:
		case BHT1750_CONT_HRES_MODE2:
			// Wait 180ms for hres reading modes
			HAL_Delay(180);
			break;
		case BHT1750_CONT_LRES_MODE:
			// Wait 50ms for lres reading mode
			HAL_Delay(50);
			break;
		default:
			// Wait 180ms in general (this won't happen)
			HAL_Delay(180);
			break;
	}


	// Get the value in rawLux
	HAL_I2C_Master_Receive(handle->config.i2c, BHT1750_I2C_ADDRESS, handle->buffer, 2, 100);
	handle->rawLuxValue = handle->buffer[0]<<8 | handle->buffer[1]; // Create 16 bit value

	// Calculate and return the lux value
	return bht1750_transformValue(handle->rawLuxValue, handle->config.state);
}

/**
 * Formula to calculate the real lux value
 * @param rawLuxValue - raw lux value read from the sensor
 * @param mode - BHT1750 mode/state
 */
int bht1750_transformValue(int rawLuxValue, BHT1750_STATE mode){
	switch(mode){
		case BHT1750_CONT_HRES_MODE:
			return rawLuxValue / 1.2;
			break;
		case BHT1750_CONT_HRES_MODE2:
			return (rawLuxValue * 0.5) / 1.2;
			break;
		case BHT1750_CONT_LRES_MODE:
			return rawLuxValue / 1.2;
			break;
		case BHT1750_ONCE_HRES_MODE:
			return rawLuxValue / 1.2;
			break;
		case BHT1750_ONCE_HRES_MODE2:
			return (rawLuxValue * 0.5) / 1.2;
			break;
		case BHT1750_ONCE_LRES_MODE:
			return rawLuxValue / 1.2;
			break;
		default:
			return rawLuxValue / 1.2;
			break;
	}
}
