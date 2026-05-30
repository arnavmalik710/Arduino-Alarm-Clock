# Arduino Alarm Clock

## Overview

An Arduino-based digital alarm clock built using the Arduino UNO and DS1307 RTC module. The system displays real-time date and time on a 16×2 LCD and supports up to four configurable alarms with buzzer notification.

## Aim

To design and implement a microcontroller-based alarm clock capable of displaying real-time date and time and generating alarm notifications at preset timings.

## Features

- Real-time clock using DS1307 RTC
- Date and day display
- 16×2 LCD user interface
- Four configurable alarms
- Push-button based configuration
- Buzzer alarm notification
- EEPROM storage for alarm settings
- Manual alarm control
- Battery-backed timekeeping through RTC module

## Components Used

- Arduino UNO
- DS1307 RTC Module
- 16×2 LCD Display
- 4 Push Buttons
- Active Buzzer
- Jumper Wires
- Breadboard
- RTC Backup Battery

## Repository Structure

- code/ – Arduino source code
- docs/ – Project documentation
- diagrams/ – Block diagram, circuit diagram and flowchart

## Working

The Arduino continuously reads date and time data from the DS1307 RTC module. The current time is displayed on the LCD while the user can configure alarms using push buttons. When the current time matches a stored alarm value, the buzzer is activated.

## Future Improvements

- Snooze functionality
- OLED display support
- Multiple alarm profiles
- Temperature monitoring
- Wireless time synchronization

## Author

Arnav Malik