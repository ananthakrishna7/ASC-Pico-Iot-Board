# Ultrasonic Distance Sensor

![BMP280 Sensor](https://cdn.shopify.com/s/files/1/0559/1970/6265/files/What_is_Ultrasonic_Sensor_fac21db5-c2aa-4894-b7e5-05aa9a1bb468_480x480.png?v=1662815986)

In this example, the RPi Pico is interfaced with an Ultrasonic Distance Sensor (HC-SR04).
The distance to the nearest obstacle is calculated. The inbuilt LED is blinked rapidly if the obstacle
is nearby, and blinked less frequently if the obstacle is further away.

## Components used
1. Raspberry Pi Pico
2. USB connector
2. HC-SR04 Sensor

## Connections

| HC-SR04 Pin | RPi Pico pin|
| -----------|-----------------|
| Vcc | 5V |
| Gnd | GND |
| Trig | 8 |
| Echo | 7 |

## Expected Output
The LED blinks at a frequency inversely proportional to the distance of the nearest obstacle.
The distance to the nearest obstacle is also sent to the computer via USB Serial.

