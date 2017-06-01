#define ALARMCLOCK_BUFFER_LENGTH 40

#include <Arduino.h>

//#define configASSERT( x )     if( ( x ) == 0 ) for (;;){tone(3, 3000, 3000); delay(3000);}

#include <DS1307RTC.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <TimedAction.h>

#include <Button/Button.h>
#include <Light/Light.h>
#include <Beeper/Beeper.h>
#include <CommandExecutor.h>
#include <Alarm/Alarm.h>

//#include <LCD_1602_RUS.h>

Button buttonBack = Button(A0, 86, 130),
        buttonSel = Button(A0, 42, 86),
        buttonUp = Button(A1, 86, 130),
        buttonDown = Button(A1, 42, 86);

Light light = Light(2, LED_BUILTIN);
Beeper beeper = Beeper(3);
SoftwareSerial BTSerial(8, 7); // RX, TX
LiquidCrystal_I2C lcd(63, 16, 2);
Player player(&beeper);
AlarmsExecutor alarmsExecutor(&light, &player);
CommandExecutor<HardwareSerial> executor(&Serial, &lcd, &RTC, &beeper, &light, &player, &alarmsExecutor);

void print2digits(int number) {
    if (number >= 0 && number < 10) {
        lcd.print('0');
    }
    lcd.print(number);
}

void updateTime();

void checkButton();

void serialAction();

void playAction();

TimedAction updateTimeA = TimedAction(1000, updateTime),
        checkButtonA = TimedAction(10, checkButton),
        serialA = TimedAction(100, serialAction),
        playerA = TimedAction(1, playAction);

void setup() {
    beeper.beep(300, 200);
    beeper.beep(450, 200);

    Serial.begin(9600);
    BTSerial.begin(9600);

    lcd.begin(); // for 16 x 2 LCD module
    lcd.backlight();
    lcd.clear();
    player.setRepeat(false);
}

void loop() {
    updateTimeA.check();
    checkButtonA.check();
    serialA.check();
    playerA.check();
}

void updateTime() {
    tmElements_t tm;

    lcd.home();
    if (RTC.read(tm)) {
        print2digits(tm.Hour);
        lcd.print(':');
        print2digits(tm.Minute);
        lcd.print(':');
        print2digits(tm.Second);
        lcd.setCursor(0, 1);
        print2digits(tm.Day);
        lcd.print('/');
        print2digits(tm.Month);
        lcd.print('/');
        lcd.print(tmYearToCalendar(tm.Year));
    } else {
        if (RTC.chipPresent()) {
            lcd.println("The RTC is stopped.");
            beeper.beep(400, 3000);
            delay(5000);
            tm.Year = 30;
            tm.Month = 0;
            tm.Day = 0;
            tm.Hour = 0;
            tm.Minute = 0;
            tm.Second = 0;
            RTC.write(tm);
        } else {
            lcd.println("No RTC presented");
            beeper.beep(800, 3000);
            delay(5000);
        }
        lcd.clear();
    }
    alarmsExecutor.check(tm);
}

void checkButton() {
    if (buttonBack.check()) {
        beeper.beep(1500, 300);
    }
    if (buttonSel.check()) {
        beeper.beep(500, 300);
    }
    if (buttonUp.check()) {
        light.turnOn();
        delay(1000);
        light.turnOff();
    }
    if (buttonDown.check()) {
        beeper.click();
    }
}

void serialAction() {
    char buf[ALARMCLOCK_BUFFER_LENGTH];

//    if (BTSerial.available()) {
//        int i = 0;
//        for (; BTSerial.available(); i++) {
//            buf[i] = (char) BTSerial.read();
//        }
//        buf[i] = 0;
//
//        executor.execute(buf);
//    }

    if (Serial.available()) {
        int i = 0;
        for (; Serial.available(); i++) {
            buf[i] = (char) Serial.read();
        }
        buf[i] = 0;

        executor.execute(buf);
    }
//    Serial.println(sizeof(Alarm));
}

void playAction() {
    player.play();
};