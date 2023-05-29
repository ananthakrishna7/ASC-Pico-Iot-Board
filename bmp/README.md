# BMP280

![BMP280 Sensor](https://europe1.discourse-cdn.com/arduino/original/4X/d/d/3/dd3f0bd7d229efd4393773ea04eecf502c4e5cba.jpeg)

This example interfaces the Raspberry Pi Pico with a BMP280 temperature and pressure
sensor using the hardware I2C interface

## Components used
- Raspberry Pi Pico
- USB connector
- BMP280 Sensor

## Pinout

- VCC of BMP280 -> 3.3V out of RPi Pico (pin 39)
- GND of BMP280 -> GND of RPi Pico (pin 3)
- SCL of BMP280 -> SDL on RPi Pico (pin 9)
- SDA of BMP280 -> SDA on RPi Pico (pin 8)

## Expected Output
The RPi Pico sends the measured temperature and pressure via USB to the computer.
Monitor the USB Serial port on your computer to verify the functioning.
