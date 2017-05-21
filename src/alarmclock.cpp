#define ALARMCLOCK_BUFFER_LENGTH 40

#include <Arduino.h>

//#define configASSERT( x )     if( ( x ) == 0 ) for (;;){tone(3, 3000, 3000); delay(3000);}

#include <TimeLib.h>
#include <DS1307RTC.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <TimedAction.h>
#include <Arduino_FreeRTOS.h>

#include <Button/Button.h>
#include <Light/Light.h>
#include <Beeper/Beeper.h>
#include <CommandExecutor.h>

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
//CommandExecutor<HardwareSerial> executor(&Serial, &lcd, &RTC, &beeper, &light, &player);
CommandExecutor<HardwareSerial> executor(&Serial, &lcd, &RTC, &beeper, &light);

void print2digits(int number) {
    if (number >= 0 && number < 10) {
        lcd.print('0');
    }
    lcd.print(number);
}

void UpdateTime(void *vParams);

TaskHandle_t UpdateTimeHandle;

void CheckButton(void *vParams);

void SerialAction(void *vParams);

TaskHandle_t PlayerHandle;

void PlayerAction(void *vParams);

void setup() {
    __malloc_heap_end = (char *) RAMEND;
//    __malloc_heap_start = (char *) RAMSTART;

    beeper.beep(300, 200);
    beeper.beep(450, 200);

    Serial.begin(9600);
    BTSerial.begin(9600);

    lcd.begin(); // for 16 x 2 LCD module
    lcd.backlight();
    lcd.clear();
//    xTaskCreate(UpdateTime, "UpdateTime", 136, NULL, 2, &UpdateTimeHandle);
//    xTaskCreate(UpdateTime, "UpdateTime", 230, NULL, 2, &UpdateTimeHandle);
//    xTaskCreate(CheckButton, "CheckButton", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(SerialAction, "SerialAction", 90, NULL, 2, NULL);
    xTaskCreate(PlayerAction, "PlayerAction", 250, NULL, 1, &PlayerHandle);
//    vTaskStartScheduler();
}

void loop() {}

tmElements_t tm;

void UpdateTime(void *pvParameters) {
    (void) pvParameters;
    for (;;) {
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
                vTaskDelay(5000 / portTICK_PERIOD_MS);
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
                vTaskDelay(5000 / portTICK_PERIOD_MS);
            }
            lcd.clear();
        }
        Serial.print("UT ");
        Serial.println(uxTaskGetStackHighWaterMark(NULL));
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void CheckButton(void *pvParameters) {
    (void) pvParameters;

    for (;;) {
        if (buttonBack.check()) {
            beeper.beep(1500, 300);
        }
        if (buttonSel.check()) {
            beeper.beep(500, 300);
        }
        if (buttonUp.check()) {
            light.turnOn();
            vTaskDelay(1000 / portTICK_PERIOD_MS);
            light.turnOff();
        }
        if (buttonDown.check()) {
            beeper.click();
        }
        vTaskDelay(500 / portTICK_PERIOD_MS);

        Serial.print("CheckButton ");
        Serial.println(uxTaskGetStackHighWaterMark(NULL));
    }
}


char buf[ALARMCLOCK_BUFFER_LENGTH];

void SerialAction(void *pvParameters) {
    (void) pvParameters;

    for (;;) {
        if (Serial.available()) {
            int i = 0;
            for (; Serial.available(); i++) {
                buf[i] = (char) Serial.read();
            }
            buf[i] = 0;

            executor.execute(buf);
        }

//            int i = 0;
//            for (; BTSerial.available(); i++) {
//                buf[i] = (char) BTSerial.read();
//            }
//            buf[i] = 0;
//            executor.execute(buf);
//        }
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void PlayerAction(void *vParams) {
    lcd.clear();
    lcd.print(uxTaskGetStackHighWaterMark(NULL));
    for (;;) {
        lcd.clear();
        lcd.print(uxTaskGetStackHighWaterMark(NULL));
        player.play_rtttl(Player::song);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

