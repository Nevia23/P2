#include <iostream>
#include "orario.h"

orario::orario (int o, int m, int s) {
    if (o < 0 || o > 23 || m < 0 || m > 59 || s < 0 || s > 59) {
        sec = 0;
    } else {
        sec = o*3600 + m*60 + s;
    }
}

orario::orario (int o, int m) {
    if (o < 0 || o > 23 || m < 0 || m > 59) {
        sec = 0;
    } else {
        sec = o*3600 + m*60;
    }
}

orario::orario (int o) {
    if (o < 0 || o > 23) {
        sec = 0;
    } else {
        sec = o*3600;
    }
}

orario::orario () {
    sec = 0;
}

int orario::Ore () {
    return sec / 3600;
}

int orario::Minuti () {
    return (sec / 60) % 60;
}

int orario::Secondi () {
    return sec % 60;
}

orario orario::operator+ (orario o) const {
    orario aux;
    aux.sec = (sec + o.sec) % 86400;
    return aux;
}

orario orario::operator- (orario o) const {
    orario aux;
    aux.sec = (sec - o.sec);
    aux.sec > 0 ? return aux : return 86400 + aux;
}

bool orario::operator== (orario o) const {
    sec == o.sec ? return true : return false;
}

bool orario::operator> (orario o) const {
    sec > o.sec ? return true : return false;
}

bool orario::operator< (orario o) const {
    sec < o.sec ? return true : return false;
}