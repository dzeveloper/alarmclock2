#include "Player.h"

#include <Arduino_FreeRTOS.h>

Player::Player(Beeper *beeper) {
    this->beeper = beeper;
};

#define isdigit(n) (n >= '0' && n <= '9')

void Player::play_rtttl(char *p) {
    int notes[50] = {
            0, 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494,
            523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988,
            1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976,
            2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951
    };

    byte default_dur = 4;
    byte default_oct = 6;
    int bpm = 63;
    int num;
    long wholenote;
    long duration;
    byte note;
    byte scale;

    while (*p != ':') p++;
    p++;

    if (*p == 'd') {
        p++;
        p++;
        num = 0;
        while (isdigit(*p)) {
            num = (num * 10) + (*p++ - '0');
        }
        if (num > 0) default_dur = (byte) num;
        p++;
    }

    if (*p == 'o') {
        p++;
        p++;
        num = *p++ - '0';
        if (num >= 3 && num <= 7) default_oct = (byte) num;
        p++;
    }

    if (*p == 'b') {
        p++;
        p++;
        num = 0;
        while (isdigit(*p)) {
            num = (num * 10) + (*p++ - '0');
        }
        bpm = num;
        p++;
    }

    wholenote = (60 * 1000L / bpm) * 4;

    while (*p) {
        num = 0;
        while (isdigit(*p)) {
            num = (num * 10) + (*p++ - '0');
        }

        if (num) duration = wholenote / num;
        else duration = wholenote / default_dur;

        note = 0;

        switch (*p) {
            case 'c':
                note = 1;
                break;
            case 'd':
                note = 3;
                break;
            case 'e':
                note = 5;
                break;
            case 'f':
                note = 6;
                break;
            case 'g':
                note = 8;
                break;
            case 'a':
                note = 10;
                break;
            case 'b':
                note = 12;
                break;
            case 'p':
            default:
                note = 0;
        }
        p++;

        if (*p == '#') {
            note++;
            p++;
        }
        if (*p == '.') {
            duration += duration / 2;
            p++;
        }
        if (isdigit(*p)) {
            scale = (byte) (*p - '0');
            p++;
        } else {
            scale = default_oct;
        }
        if (*p == ',')
            p++;

        if (note) {
            beeper->beep(notes[(scale - 4) * 12 + note], (int) duration);
        } else {
            beeper->noBeep((int) duration);
        }

//        if (note) {
//            beeper->beep(notes[(scale - 4) * 12 + note], duration);
//            delay(duration);
//            noTone(3);
//        } else {
//            delay(duration);
//        }
    }
}