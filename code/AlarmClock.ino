#include <Wire.h>          
#include <LiquidCrystal.h> 
#include <EEPROM.h>
#include <RTClib.h>        

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

#define bt_clock   A0
#define bt_up      A1
#define bt_down    A2
#define bt_timer   A3
#define buzzer     11

RTC_DS1307 rtc;

char daysOfTheWeek[7][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

int hh = 0, mm = 0, ss = 0, dd = 0, bb = 0, yy = 0;
String Day = "  ";

int StartHH = 0, StartMM = 0, FinishHH = 0, FinishMM = 0, setMode = 0, setAlarm = 0, alarmMode = 1;
int Start1HH, Start1MM, Finish1HH, Finish1MM, Start2HH, Start2MM, Finish2HH, Finish2MM;
int Start3HH, Start3MM, Finish3HH, Finish3MM, Start4HH, Start4MM, Finish4HH, Finish4MM;

int timer1, timer2, timer3, timer4;
int stop = 0, mode = 0, flag = 0;
bool blinkState = true;
unsigned long lastBlinkTime = 0;

void setup() {
  pinMode(bt_clock, INPUT_PULLUP);
  pinMode(bt_up,    INPUT_PULLUP);
  pinMode(bt_down,  INPUT_PULLUP);
  pinMode(bt_timer, INPUT_PULLUP);

  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);

  lcd.begin(16, 2);
  lcd.print(" Real Time Clock ");
  lcd.setCursor(0, 1);
  lcd.print("  4-Timer Setup  ");

  if (!rtc.begin()) {
    lcd.clear();
    lcd.print("RTC NOT FOUND!");
    while (1); 
  }

  if (!rtc.isrunning()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  delay(2000);
  lcd.clear();
  ReadEeprom();
}

void loop() {
  DateTime now = rtc.now();
  Day = daysOfTheWeek[now.dayOfTheWeek()];

  // Handle Blinking Timing
  if (millis() - lastBlinkTime > 300) {
    blinkState = !blinkState;
    lastBlinkTime = millis();
  }

  if (setMode == 0) {
    hh = now.hour();
    mm = now.minute();
    ss = now.second();
    dd = now.day();
    bb = now.month();
    yy = now.year();
  }

  if (setAlarm == 0) {
    lcd.setCursor(0, 0);
    if (hh < 10) lcd.print("0"); lcd.print(hh);
    lcd.print(":");
    if (mm < 10) lcd.print("0"); lcd.print(mm);
    lcd.print(":");
    if (ss < 10) lcd.print("0"); lcd.print(ss);
    lcd.print("        ");

    lcd.setCursor(1, 1);
    lcd.print(Day);
    lcd.print(" ");
    if (dd < 10) lcd.print("0"); lcd.print(dd);
    lcd.print("/");
    if (bb < 10) lcd.print("0"); lcd.print(bb);
    lcd.print("/");
    lcd.print(yy);
  }

  setupClock();
  setTimer();
  blinking();

  // Alarm logic
  bool isAlarming = false;
  if (timer1 == 1 && alarmMode == 1 && hh == Start1HH && mm == Start1MM) isAlarming = true;
  if (timer2 == 1 && alarmMode == 1 && hh == Start2HH && mm == Start2MM) isAlarming = true;
  if (timer3 == 1 && alarmMode == 1 && hh == Start3HH && mm == Start3MM) isAlarming = true;
  if (timer4 == 1 && alarmMode == 1 && hh == Start4HH && mm == Start4MM) isAlarming = true;

  digitalWrite(buzzer, isAlarming ? HIGH : LOW);
  delay(50);
}

void blinking() {
  if (!blinkState) {
    if (setAlarm < 2 && setMode == 1) { lcd.setCursor(0, 0);  lcd.print("  "); }
    if (setAlarm < 2 && setMode == 2) { lcd.setCursor(3, 0);  lcd.print("  "); }
    if (setAlarm < 2 && setMode == 3) { lcd.setCursor(6, 0);  lcd.print("  "); }
    if (setAlarm < 2 && setMode == 4) { lcd.setCursor(1, 1);  lcd.print("   "); }
    if (setAlarm < 2 && setMode == 5) { lcd.setCursor(5, 1);  lcd.print("  "); }
    if (setAlarm < 2 && setMode == 6) { lcd.setCursor(8, 1);  lcd.print("  "); }
    if (setAlarm < 2 && setMode == 7) { lcd.setCursor(11, 1); lcd.print("    "); }

    if (setMode == 0 && setAlarm == 1 && mode == 0) { lcd.setCursor(2, 1); lcd.print("  "); }
    if (setMode == 0 && setAlarm == 2 && mode == 0) { lcd.setCursor(6, 1); lcd.print("  "); }
    if (setMode == 0 && setAlarm == 3 && mode == 0) { lcd.setCursor(10, 1); lcd.print("  "); }
    if (setMode == 0 && setAlarm == 4 && mode == 0) { lcd.setCursor(13, 1); lcd.print("  "); }

    if (setMode == 0 && setAlarm == 1 && mode > 0) { lcd.setCursor(11, 0); lcd.print("  "); }
    if (setMode == 0 && setAlarm == 2 && mode > 0) { lcd.setCursor(14, 0); lcd.print("  "); }
    if (setMode == 0 && setAlarm == 3 && mode > 0) { lcd.setCursor(11, 1); lcd.print("  "); }
    if (setMode == 0 && setAlarm == 4 && mode > 0) { lcd.setCursor(14, 1); lcd.print("  "); }
  }
}

void setupClock() {
  if (setMode == 8) {
    rtc.adjust(DateTime(yy, bb, dd, hh, mm, ss));
    lcd.clear();
    setMode = 0;
  }

  if (setAlarm > 0) alarmMode = 0;

  if (digitalRead(bt_clock) == 0 && flag == 0) {
    flag = 1;
    if (setAlarm > 0) { WriteEeprom(); setAlarm = 1; mode = 5; }
    else { setMode++; }
    digitalWrite(buzzer, HIGH); delay(50); digitalWrite(buzzer, LOW);
  }

  if (digitalRead(bt_timer) == 0 && flag == 0) {
    flag = 1;
    if (setMode > 0) { setMode = 8; }
    else {
      setAlarm++;
      if (setAlarm > 4) {
        setAlarm = 1;
        WriteEeprom();
        mode++;
        ReadEeprom();
        if (mode > 4) { mode = 0; setAlarm = 0; alarmMode = 1; lcd.clear(); }
      }
    }
    lcd.clear();
    digitalWrite(buzzer, HIGH); delay(50); digitalWrite(buzzer, LOW);
  }

  if (setAlarm == 1 && mode == 5) {
    lcd.clear(); lcd.print("Saved!"); delay(1000); lcd.clear();
    setAlarm = 0; mode = 0; alarmMode = 1;
  }

  if (digitalRead(bt_clock) == 1 && digitalRead(bt_timer) == 1) flag = 0;

  if (digitalRead(bt_up) == 0) {
    if (setMode > 0) {
      if (setMode == 1) hh++; if (setMode == 2) mm++; if (setMode == 5) dd++; if (setMode == 6) bb++; if (setMode == 7) yy++;
    } else {
      if (mode == 0) {
        if (setAlarm == 1) timer1 = 1; if (setAlarm == 2) timer2 = 1; if (setAlarm == 3) timer3 = 1; if (setAlarm == 4) timer4 = 1;
      } else {
        if (setAlarm == 1) StartHH++; if (setAlarm == 2) StartMM++; if (setAlarm == 3) FinishHH++; if (setAlarm == 4) FinishMM++;
      }
    }
    digitalWrite(buzzer, HIGH); delay(150); digitalWrite(buzzer, LOW); // Debounce delay
  }

  if (digitalRead(bt_down) == 0) {
    if (setMode > 0) {
      if (setMode == 1) hh--; if (setMode == 2) mm--; if (setMode == 5) dd--; if (setMode == 6) bb--; if (setMode == 7) yy--;
    } else {
      if (mode == 0) {
        if (setAlarm == 1) timer1 = 0; if (setAlarm == 2) timer2 = 0; if (setAlarm == 3) timer3 = 0; if (setAlarm == 4) timer4 = 0;
      } else {
        if (setAlarm == 1) StartHH--; if (setAlarm == 2) StartMM--; if (setAlarm == 3) FinishHH--; if (setAlarm == 4) FinishMM--;
      }
    }
    digitalWrite(buzzer, HIGH); delay(150); digitalWrite(buzzer, LOW); // Debounce delay
  }

  // Bounds
  if (hh > 23) hh = 0; if (hh < 0) hh = 23;
  if (mm > 59) mm = 0; if (mm < 0) mm = 59;
  if (StartHH > 23) StartHH = 0; if (StartHH < 0) StartHH = 23;
  if (StartMM > 59) StartMM = 0; if (StartMM < 0) StartMM = 59;
}

void setTimer() {
  if (setMode == 0 && setAlarm > 0 && mode > 0) {
    lcd.setCursor(0, 0); lcd.print("Timer"); lcd.print(mode); lcd.print(" On :");
    lcd.setCursor(11, 0);
    if (StartHH < 10) lcd.print("0"); lcd.print(StartHH);
    lcd.print(":");
    if (StartMM < 10) lcd.print("0"); lcd.print(StartMM);

    lcd.setCursor(0, 1); lcd.print("Timer"); lcd.print(mode); lcd.print(" Off:");
    lcd.setCursor(11, 1);
    if (FinishHH < 10) lcd.print("0"); lcd.print(FinishHH);
    lcd.print(":");
    if (FinishMM < 10) lcd.print("0"); lcd.print(FinishMM);
  }

  if (setMode == 0 && setAlarm > 0 && mode == 0) {
    lcd.setCursor(0, 0); lcd.print(" T1   T2   T3   T4 ");
    lcd.setCursor(0, 1);
    lcd.print(timer1 == 1 ? "  A " : "  D ");
    lcd.print(timer2 == 1 ? "  A " : "  D ");
    lcd.print(timer3 == 1 ? "  A " : "  D ");
    lcd.print(timer4 == 1 ? "  A " : "  D ");
  }
}

void ReadEeprom() {
  Start1HH = EEPROM.read(11); Start1MM = EEPROM.read(12); Finish1HH = EEPROM.read(13); Finish1MM = EEPROM.read(14);
  Start2HH = EEPROM.read(21); Start2MM = EEPROM.read(22); Finish2HH = EEPROM.read(23); Finish2MM = EEPROM.read(24);
  Start3HH = EEPROM.read(31); Start3MM = EEPROM.read(32); Finish3HH = EEPROM.read(33); Finish3MM = EEPROM.read(34);
  Start4HH = EEPROM.read(41); Start4MM = EEPROM.read(42); Finish4HH = EEPROM.read(43); Finish4MM = EEPROM.read(44);

  if (mode == 1) { StartHH = Start1HH; StartMM = Start1MM; FinishHH = Finish1HH; FinishMM = Finish1MM; }
  if (mode == 2) { StartHH = Start2HH; StartMM = Start2MM; FinishHH = Finish2HH; FinishMM = Finish2MM; }
  if (mode == 3) { StartHH = Start3HH; StartMM = Start3MM; FinishHH = Finish3HH; FinishMM = Finish3MM; }
  if (mode == 4) { StartHH = Start4HH; StartMM = Start4MM; FinishHH = Finish4HH; FinishMM = Finish4MM; }

  timer1 = EEPROM.read(1); timer2 = EEPROM.read(2); timer3 = EEPROM.read(3); timer4 = EEPROM.read(4);
}

void WriteEeprom() {
  if (mode == 1) { EEPROM.write(11, StartHH); EEPROM.write(12, StartMM); EEPROM.write(13, FinishHH); EEPROM.write(14, FinishMM); Start1HH = StartHH; Start1MM = StartMM; }
  if (mode == 2) { EEPROM.write(21, StartHH); EEPROM.write(22, StartMM); EEPROM.write(23, FinishHH); EEPROM.write(24, FinishMM); Start2HH = StartHH; Start2MM = StartMM; }
  if (mode == 3) { EEPROM.write(31, StartHH); EEPROM.write(32, StartMM); EEPROM.write(33, FinishHH); EEPROM.write(34, FinishMM); Start3HH = StartHH; Start3MM = StartMM; }
  if (mode == 4) { EEPROM.write(41, StartHH); EEPROM.write(42, StartMM); EEPROM.write(43, FinishHH); EEPROM.write(44, FinishMM); Start4HH = StartHH; Start4MM = StartMM; }
  EEPROM.write(1, timer1); EEPROM.write(2, timer2); EEPROM.write(3, timer3); EEPROM.write(4, timer4);
}