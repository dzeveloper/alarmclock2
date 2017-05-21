#ifndef ALARMCLOCK_COMMANDEXECUTOR_H
#define ALARMCLOCK_COMMANDEXECUTOR_H

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DS1307RTC.h>
#include <TimeLib.h>
#include <SoftwareSerial.h>

#include <Beeper/Beeper.h>
#include <Light/Light.h>
#include <Player/Player.h>

#define ALARMCLOCK_BUFFER_LENGTH 40

template<class Serial_T>
class CommandExecutor {
    Serial_T *serial;
    LiquidCrystal_I2C *lcd;
    DS1307RTC *rtc;
    Beeper *beeper;
    Light *light;
//    Player* player;
public:
//    CommandExecutor(Serial_T *serial, LiquidCrystal_I2C *lcd, DS1307RTC *rtc, Beeper *beeper, Light *light, Player* player);
    CommandExecutor(Serial_T *serial, LiquidCrystal_I2C *lcd, DS1307RTC *rtc, Beeper *beeper, Light *light);

    void execute(char *cmd);
};


#endif //ALARMCLOCK_COMMANDEXECUTOR_H
