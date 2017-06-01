#include "Player.h"

Player::Player(Beeper *beeper) {
    this->beeper = beeper;
    this->curSong = (char *) songs[0];
    this->doPlay = false;
    this->repeat = false;
    resetSong();
};

void Player::setSong(char *song) {
    this->curSong = song;
    resetSong();
}

void Player::pause() {
    doPlay = false;
}

void Player::start() {
    doPlay = true;
}

void Player::setRepeat(boolean repeat) {
    this->repeat = repeat;
}

void Player::resetSong() {
    noteLnk = curSong;

    while (*noteLnk != ':') noteLnk++;
    noteLnk++;

    if (*noteLnk == 'd') {
        noteLnk++;
        noteLnk++;
        num = 0;
        while (isdigit(*noteLnk)) {
            num = (num * 10) + (*noteLnk++ - '0');
        }
        if (num > 0) default_dur = (byte) num;
        noteLnk++;
    }

    if (*noteLnk == 'o') {
        noteLnk++;
        noteLnk++;
        num = *noteLnk++ - '0';
        if (num >= 3 && num <= 7) default_oct = (byte) num;
        noteLnk++;
    }

    if (*noteLnk == 'b') {
        noteLnk++;
        noteLnk++;
        num = 0;
        while (isdigit(*noteLnk)) {
            num = (num * 10) + (*noteLnk++ - '0');
        }
        bpm = num;
        noteLnk++;
    }

    wholenote = (60 * 1000L / bpm) * 4;
}

int notes[50] = {
        0, 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494,
        523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988,
        1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976,
        2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951
};

#define isdigit(n) (n >= '0' && n <= '9')

void Player::play() {
    if (doPlay && *noteLnk) {
        num = 0;
        while (isdigit(*noteLnk)) {
            num = (num * 10) + (*noteLnk++ - '0');
        }

        if (num) duration = wholenote / num;
        else duration = wholenote / default_dur;

        note = 0;

        switch (*noteLnk) {
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
        noteLnk++;

        if (*noteLnk == '#') {
            note++;
            noteLnk++;
        }
        if (*noteLnk == '.') {
            duration += duration / 2;
            noteLnk++;
        }
        if (isdigit(*noteLnk)) {
            scale = (byte) (*noteLnk - '0');
            noteLnk++;
        } else {
            scale = default_oct;
        }
        if (*noteLnk == ',')
            noteLnk++;

        if (note) {
            beeper->beep(notes[(scale - 4) * 12 + note], (int) duration);
        } else {
            beeper->noBeep((int) duration);
        }

        if (!*(noteLnk + sizeof(noteLnk))) {
            if (repeat) {
                resetSong();
                play();
            } else pause();
        }
    }
}

bool Player::getRepeat() {
    return repeat;
}

bool Player::isPlaying() {
    return doPlay;
}
