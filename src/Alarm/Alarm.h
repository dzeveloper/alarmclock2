#ifndef ALARMCLOCK_ALARMINTERVAL_H
#define ALARMCLOCK_ALARMINTERVAL_H

#include <HID.h>
#include <EEPROM.h>
#include <Light/Light.h>
#include <Player/Player.h>

#include "Time.h"

class Alarm {
public:
    Time start, end;
    bool doPlay, doLight;
    int songIdx;

    Alarm(Time start, Time end, bool doLight = true, bool doPlay = false, boolean melodyIdx = 0) {
        this->start = start;
        this->end = end;
        this->doLight = doLight;
        this->doPlay = doPlay;
        this->songIdx = melodyIdx;
    }

    bool between(Time t) {
        return t > start && t < end;
    }
};

class AlarmsExecutor {
    Light *light;
    Player *player;

    Alarm alarmsBuf[length];
public:
    AlarmsExecutor(Light *light, Player *player) {
        this->light = light;
        this->player = player;

        for (int i = 0; i < length; i++) {
            EEPROM.get(i, alarmsBuf[i]);
        }
    }

    void set(int idx, Alarm *alarm) {
        EEPROM.put(idx % length, *alarm);
        alarmsBuf[idx % length] = *alarm;
    }

    Alarm get(int idx) {
        return alarmsBuf[idx % length];
    }

    constexpr static int length = 10;

    void check(Time t) {
        for (int i = 0; i < length; i++) {
            if (alarmsBuf[i].between(t)) {
                if (alarmsBuf[i].doLight) {
                    light->turnOn();
                }
                if (alarmsBuf[i].doPlay) {
                    player->setRepeat(true);
                    player->setSong((char *) player->songs[alarmsBuf[i].songIdx % player->songsLength]);
                }
            }
        }
    }
};


#endif //ALARMCLOCK_ALARMINTERVAL_H
