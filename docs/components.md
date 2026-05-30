# Description of Components

## Arduino UNO

Arduino UNO is an ATmega328P-based microcontroller board used as the main controller in this project. It processes all the input and output operations including time reading, LCD interfacing, button control, and alarm activation.

### Features
- ATmega328P microcontroller
- 14 digital I/O pins
- 6 analog input pins
- USB programming support
- Operating voltage: 5V
- Clock frequency: 16 MHz

## DS1307 RTC Module

The DS1307 Real Time Clock module is used to maintain accurate time and date information. It communicates with Arduino using the I2C communication protocol through SDA and SCL pins.

The RTC module includes a backup battery which allows it to continue tracking time even when external power is disconnected.

## 16×2 LCD Display

The 16×2 LCD module is used to display real-time information such as hours, minutes, seconds, date, and alarm status. The LCD provides an easy user interface for the project.

## Push Buttons

Push buttons are used for setting the clock time and alarm values. Different buttons are assigned for increment, decrement, and setting operations.

## Buzzer

The buzzer is used as the alarm output device. When the preset alarm time matches the current RTC time, the Arduino activates the buzzer to generate an audible alert.