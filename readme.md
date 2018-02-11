# BHT1750 Sensor LIB for STM32 microcontrollers

This library was developed and tested only with *STM32F030XX*. I currently don't have other boards to test the implementation on other generations but it should work as expected. As soon as I can get any, I'll update the library.

## TODO

- Create more examples for once reading, continuous reading, different reading modes
- Photos/Videos of wiring and how it works
- Adjust the library to use interrupts (currently it's blocking)
- Add debugging improvement by adding a new enum with the action results of each method in the library
- Release version 1.0

## Usage

Just copy the `bht1750.h` from Inc folder and `bht1750.c` from Src folder to your project and see the `main.c` as a refference on how to initialise and use the library. 

## Hardware Setup

Connect the wiring as follows:

STM32 BHT1750

GND -> GND

3.3V -> VCC

SCL -> SCL

SDA -> SDA

GND -> SD0 (this will pull low the SD0 line on the sensor and the slave address will be 0x23. IF you pull high this line, you'll get the other sensor address which is 0x5C)

## Software setup
Enable the I2C interface on your STM32 and select the fast mode (400KHz)

## Implementation details

This library blocks the main thread using `HAL_Delay()` to perform readings of the sensor from the I2C bus. It sends the right sequences of bytes to the sensor to power it up, start measurement, do readings, etc. The library supports continuous mode reading and only once reading mode. To optimise power consumption you can use the read once method or after performing several readings you can power off the sensor.

## License

Library is licensed using GNU General Public License v3.0
