/*
 * bht1750.h
 *
 *  Created on: Feb 9, 2018
 *      Author: laalex
 */

#ifndef BHT1750_H_
#define BHT1750_H_

#define STM32F0

#if defined STM32F0
#include "stm32f0xx_hal.h"
#endif

#include <stdbool.h>

/**
 * Sensor address
 */
#define BHT1750_I2C_ADDRESS 0x23<<1


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
 * Sensor handle
 */
typedef struct {
	/**
	 * Buffer used for sending and receiving data
	 */
	unsigned int buffer[5];

	/**
	 * Lux value
	 */
	unsigned int rawLuxValue;


	/**
	 * Config
	 */
	bht1750_config config;
} bht1750;

/**
 * Sensor I2C initialisation
 */
void bht1750_init(bht1750_config* config, bht1750* handle);

/**
 * Return lux reading
 */
int bht1750_getValue(bht1750* handle);

#endif /* BHT1750_H_ */
