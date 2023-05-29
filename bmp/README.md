# BMP280

![BMP280 Sensor](https://europe1.discourse-cdn.com/arduino/original/4X/d/d/3/dd3f0bd7d229efd4393773ea04eecf502c4e5cba.jpeg)

This example interfaces the Raspberry Pi Pico with a BMP280 temperature and pressure
sensor using the hardware I2C interface

## Components used
1. Raspberry Pi Pico
1. USB connector
1. BMP280 Sensor

## Connections

| BMP280 Pin | RPi Pico pin|
| -----------|-----------------|
| VCC | 5V |
| GND | GND |
| SCL | IO5/SCL |
| SDA | IO4/SDA |

## Expected Output
The RPi Pico sends the measured temperature and pressure via USB to the computer.
Monitor the USB Serial port on your computer to verify the functioning.
