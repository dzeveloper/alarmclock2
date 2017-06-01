#ifndef ALARMCLOCK_ALARMINTERVAL_H
#define ALARMCLOCK_ALARMINTERVAL_H

#include <EEPROM.h>
#include <Light/Light.h>
#include <Player/Player.h>
#include <Time.h>

#include "Time.h"

class Alarm {
public:
    Time start, end;
    bool daysOfWeek[DAYS_PER_WEEK] = {false};
    bool doPlay, doLight;
    int songIdx;

    Alarm() {
        start = Time();
        end = Time();
        doLight = false;
        doPlay = false;
        songIdx = 0;
//        for (int i = 0; i < DAYS_PER_WEEK; i++) {
//            daysOfWeek[i] = false;
//        }
    };

    Alarm(Time start, Time end, bool *daysOfWeek, bool doLight = true, bool doPlay = false, boolean songIdx = 0) {
        this->start = start;
        this->end = end;
        this->doLight = doLight;
        this->doPlay = doPlay;
        this->songIdx = songIdx;
        for (int i = 0; i < DAYS_PER_WEEK; i++) {
            this->daysOfWeek[i] = daysOfWeek[i];
        }
    }

    bool satisfy(tmElements_t t) {
        //Su, Mo, Tu, We, Th, Fr, Sa
        //1   2   3   4   5   6   7
        boolean satisfyDoW;
        if (t.Wday != dowSunday) {
            satisfyDoW = daysOfWeek[t.Wday - 2];
        } else {
            satisfyDoW = daysOfWeek[DAYS_PER_WEEK - 1];
        }
        Time time(t);
        return satisfyDoW && time > start && time < end;
    }

    bool *getDoW() {
        return daysOfWeek;
    }

    Time getStart() {
        return start;
    }

    Time getEnd() {
        return end;
    }
};

class AlarmsExecutor {
    Light *light;
    Player *player;
    constexpr static int l = 10;
    Alarm alarmsCache[l];
    bool active = false;
public:
    constexpr static int length = l;

    AlarmsExecutor(Light *light, Player *player) {
        this->light = light;
        this->player = player;

        Alarm alarm;
        for (int i = 0; i < length; i++) {
            EEPROM.get(i * sizeof(Alarm), alarm);
            alarmsCache[i] = alarm;
        }
    }

    void set(int idx, Alarm *alarm) {
        EEPROM.put(idx * sizeof(Alarm), *alarm);
        alarmsCache[idx] = *alarm;
        active = false;
    }

    Alarm get(int idx) {
        return alarmsCache[idx % length];
    }

    void check(tmElements_t t) {
        for (int i = 0; i < length; i++) {
            if (alarmsCache[i].satisfy(t)) {
                if (!active && alarmsCache[i].doLight) {
                    light->turnOn();
                }
                if (!active && alarmsCache[i].doPlay) {
                    player->setRepeat(true);
                    player->setSong((char *) player->songs[alarmsCache[i].songIdx % player->songsLength]);
                    player->start();
                }
                active = true;
                return;
            }
        }
        if (active) {
            light->turnOff();
            player->setRepeat(false);
            player->pause();
            active = false;
        }
//        Serial.println();
    }
};


#endif //ALARMCLOCK_ALARMINTERVAL_H
