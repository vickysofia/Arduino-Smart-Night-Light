# Arduino-Smart-Night-Light
An interactive Arduino Uno R4 Wifi (or minima) night-light with automatic dimming, LCD brightness display, and random button color customization
# Arduino Smart Night-Light

An interactive, ambient-aware night-light built on the Arduino Uno R4 WiFi. The system automatically adjusts LED brightness based on room light levels, displays real-time brightness percentages on an I2C LCD, and allows user color customization via a physical button.

## Features
- **Automatic Dimming:** Increases LED brightness as room light drops below 50%.
- **Live Monitoring:** Real-time room brightness percentage displayed on a 16x2 I2C LCD.
- **Random Color Palette:** Pressing the tactile button generates a random RGB hue.
- **Dynamic Math Scaling:** Smooth integer-based PWM transitions without rounding errors.

## Hardware Components
- Arduino Uno R4 WiFi
- Photoresistor Module (Analog Light Sensor)
- RGB LED Module (PWM-controlled)
- I2C LCD 1602 Screen
- Push Button Module
- Breadboard & Jumper Wires

## Circuit Connections
| Component | Pin on Component | Arduino Pin |
| :--- | :--- | :--- |
| **Photoresistor** | AO | A0 |
| **Button Module** | OUT / Signal | D2 |
| **RGB LED** | Red / Green / Blue | D9 / D10 / D11 |
| **I2C LCD** | SDA / SCL | SDA / SCL |

## Dependencies
- `Wire.h` (Built-in)
- `LiquidCrystal_I2C` (by Frank de Brabander)
