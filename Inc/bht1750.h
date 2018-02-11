/*
 * bht1750.h
 *
 *  Created on: Feb 9, 2018
 *      Author: laalex
 */

#ifndef BHT1750_H_
#define BHT1750_H_

#define STM32F0 // This should be defined at runtime


// TODO: Add support for multiple STM32XX
#if defined STM32F0
#include "stm32f0xx_hal.h"
#endif

#include <stdbool.h>

/**
 * Sensor address
 * Please refer to the datasheet to see when to use one of the two i2c addresses for this sensor
 */
#define BHT1750_I2C_ADDRESS 0x23<<1 // ADDR L
//#define BHT1750_I2C_ADDRESS 0x5C<<1 // ADDR H

/**
 * Sensor state/mode
 */
typedef enum {
	/**
	 * Sensor power up
	 */
	BHT1750_POWER_DOWN = 0x00,
	/**
	 * Sensor sleep
	 */
	BHT1750_POWER_UP = 0x01,
	/**
	 * Reset sensor
	 */
	BHT1750_RESET = 0x07,
	/**
	 * Continuous high resolution mode 1
	 */
	BHT1750_CONT_HRES_MODE = 0x10,
	/**
	 * Continuous high resolution mode 2
	 */
	BHT1750_CONT_HRES_MODE2 = 0x11,
	/**
	 * Continuous low resolution mode
	 */
	BHT1750_CONT_LRES_MODE = 0x13,
	/**
	 * One time high resolution mode
	 */
	BHT1750_ONCE_HRES_MODE = 0x20,
	/**
	 * One time high resolution mode 2
	 */
	BHT1750_ONCE_HRES_MODE2 = 0x21,
	/**
	 * One time low resolution mode
	 */
	BHT1750_ONCE_LRES_MODE = 0x23
} BHT1750_STATE;

/**
 * Configuration structure
 */
typedef struct {
	/**
	 *  I2C Handle
	 */
	I2C_HandleTypeDef* i2c;

	/**
	 * Mode
	 */
	volatile BHT1750_STATE state;

} bht1750_config;

/**
 * Sensor handle structure
 */
typedef struct {
	/**
	 * Buffer used for sending and receiving data via i2c
	 */
	uint8_t buffer[5];

	/**
	 * Raw lux value
	 */
	unsigned int rawLuxValue;


	/**
	 * Configuration of the sensor
	 */
	bht1750_config config;
} bht1750;


/**
 * Sensor I2C initialisation - power up the sensor
 * @param config - pointer to BHT1750 config
 * @param handle - pointer to BHT1750 handle
 */
void bht1750_init(bht1750_config*, bht1750*);

/**
 * Power down the sensor
 * @param handle - pointer to BHT1750 handle
 */
void bht1750_powerDown(bht1750*);

/**
 * Power up the sensor
 * @param handle - pointer to BHT1750 handle
 */
void bht1750_powerUp(bht1750*);

/**
 * Reset the sensor
 * @param handle - pointer to BHT1750 handle
 */
void bht1750_reset(bht1750*);

/**
 * Read once the value from the sensor and then turn off the IC
 * @param handle - pointer to BHT1750 handle
 * @param state - BHT1750 mode / state
 */
int bht1750_readOnce(bht1750*, BHT1750_STATE);


/**
 * Continuous mode reading
 * @param handle - pointer to BHT1750 handle
 * @param mode - BHT1750 mode/state
 */
int bht1750_readContinuous(bht1750*, BHT1750_STATE);


/**
 * Formula to calculate the real lux value
 * @param rawLuxValue - raw lux value read from the sensor
 * @param mode - BHT1750 mode/state
 */
int bht1750_transformValue(int, BHT1750_STATE);

#endif /* BHT1750_H_ */
