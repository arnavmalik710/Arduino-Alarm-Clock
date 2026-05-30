# Working Principle

The digital alarm clock system operates using Arduino UNO as the main controller and a DS1307 RTC module for accurate timekeeping.

The RTC module continuously provides real-time date and time data to the Arduino through I2C communication.

The Arduino processes this data and displays it on the 16×2 LCD module. Push buttons are used to set the current time and alarm values.

The Arduino continuously compares the current time with the preset alarm time. When both values match, the buzzer is activated to generate an alarm signal.

The RTC module uses a backup battery to maintain time data during power failure.