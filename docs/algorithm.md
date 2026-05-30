# Algorithm

1. Start the system.
2. Initialize Arduino UNO, LCD, RTC module, buzzer, and push buttons.
3. Read current date and time from the DS1307 RTC module.
4. Display current date and time on the LCD screen.
5. Check for user input through push buttons.
6. If the user enters alarm-setting mode:
   - Set alarm hour and minute values.
   - Store alarm time.
7. Continuously compare current time with the stored alarm time.
8. If current time matches alarm time:
   - Activate the buzzer.
9. Continue monitoring time and user inputs.
10. Repeat the process continuously.
11. Stop only when power is disconnected.