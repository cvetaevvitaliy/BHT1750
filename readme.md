# BHT1750 Sensor LIB for STM32 microcontrollers

This library was developed and tested only with *STM32F030XX*. I currently don't have other boards to test the implementation on other generations but it should work as expected. As soon as I can get any, I'll update the library.

## TODO
- Adjust the library to use interrupts (currently it's blocking)
- Add debugging improvement by adding a new enum with the action results of each method in the library
- Finish this TODO list and release version 1.0

## Usage

Just copy the `bht1750.h` from Inc folder and `bht1750.c` from Src folder to your project and see the `main.c` as a refference on how to initialise and use the library or check the section below on how to use the library

## Hardware Setup

### Wiring/pin connections
Connect the wiring as follows:

STM32 BHT1750

GND -> GND

3.3V -> VCC

SCL -> SCL

SDA -> SDA

GND -> SD0 (this will pull low the SD0 line on the sensor and the slave address will be 0x23. IF you pull high this line, you'll get the other sensor address which is 0x5C)

See the above wiring details in the following images
- TODO, add images

## How to use the library

The following steps should be performed to use the library:
1. In your main file, include the BHT1750 library by writing `#include "bht1750.h"`
2. Initialize required variables for the handle and configuration of the library as follows:
```
bht1750 lightSensor;
bht1750_config lightSensorConfig;
int luxValue;
```
3. Initialize the configuration of the sensor by setting the I2C interface handle as follows:
```
lightSensorConfig.i2c = &hi2c1; // change &hi2c1 according to your i2c interface
```
4. Initialize the library by passing the configuration:
```
bht1750_init(&lightSensorConfig, &lightSensor);
```
5. In the main loop you can use:
```
luxValue = bht1750_readContinuous(&lightSensor, BHT1750_CONT_HRES_MODE);
```
or
```
luxValue = bht1750_readOnce(&lightSensor, BHT1750_CONT_HRES_MODE);
```
In this step use the appropriate mode that you want to use in reading the lux information. For available modes please refer to the list below or check the docs:
```
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
```


### Enabling I2C interface from CubeMX and/or initialising the I2C via software:
Enable the I2C interface on your STM32 via CubeMX and make sure it is configured to use fast mode (400KHz).

## Implementation details

This library blocks the main thread using `HAL_Delay()` to perform readings of the sensor from the I2C bus. It sends the right sequences of bytes to the sensor to power it up, start measurement, do readings, etc. The library supports continuous mode reading and only once reading mode. To optimise power consumption you can use the read once method or after performing several readings you can power off the sensor.

## License

Library is licensed using GNU General Public License v3.0
