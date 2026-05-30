# Arduino Alarm Clock

## Overview

An Arduino-based digital alarm clock developed using the Arduino UNO and DS1307 Real-Time Clock (RTC) module. The system displays real-time date and time on a 16×2 LCD and supports four independently configurable alarms with EEPROM-based storage.

## Aim

To design and implement a microcontroller-based digital alarm clock capable of displaying accurate real-time date and time while providing configurable alarm notifications.

## Features

- Real-time clock using DS1307 RTC
- Date and day display
- 16×2 LCD user interface
- Four independently configurable alarms
- Enable/disable individual alarms
- EEPROM storage for alarm settings
- Push-button based configuration
- Audible buzzer notifications
- Manual alarm control
- RTC battery backup support

## Components Used

- Arduino UNO
- DS1307 RTC Module
- 16×2 LCD Display
- 4 Push Buttons
- Active Buzzer
- Breadboard
- Jumper Wires
- RTC Backup Battery

## Working Principle

The DS1307 RTC module continuously maintains current time and date information. Arduino UNO reads this data through I2C communication and displays it on the LCD.

Users can configure up to four alarms using push buttons. Alarm settings are stored in EEPROM memory, allowing them to persist even after power loss.

When the current time matches an enabled alarm time, the buzzer is activated to alert the user.

## Repository Structure

text Arduino-Alarm-Clock/ │ ├── README.md ├── code/ │   └── AlarmClock.ino │ ├── docs/ │   ├── aim.md │   ├── introduction.md │   ├── components.md │   ├── working-principle.md │   ├── algorithm.md │   ├── procedure.md │   ├── precautions.md │   └── conclusion.md │ └── diagrams/ 

## Future Improvements

- Snooze functionality
- 12-hour AM/PM display mode
- Custom alarm tones
- OLED display support
- Temperature monitoring
- Wireless time synchronization

## Author

Arnav Malik