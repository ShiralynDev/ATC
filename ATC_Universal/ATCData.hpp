#pragma once

#include <sstream>

struct internalATCData {
    bool isCabA = true;
    int startup = 0; // 0 = off, 1 = startup, 2 = running/data input, 3 = running, data inputed
    bool dataEntryButtonPressed = false;
    bool ABBVersion = false; // SRT/ATSS/Ansaldo on false, ABB on true
    bool achived = false;    // Used as a general varible to save data
    bool achived1 = false;   // Used as a general varible to save data
    bool achived2 = false;   // Used as a general varible to save data
    bool failed = false;
    int vmax = 0;   // in km/h
    int length = 0; // in x * 10²m 100m = 1, 900m = 9;

    void serialize(std::ostream& out) const {
        out << startup << ' '
            << dataEntryButtonPressed << ' '
            << ABBVersion << ' '
            << achived << ' '
            << achived1 << ' '
            << achived2 << ' '
            << failed << ' '
            << vmax << ' '
            << length << ' ';
    }

    void deserialize(std::istream& in) {
        in >> startup
           >> dataEntryButtonPressed
           >> ABBVersion
           >> achived
           >> achived1
           >> achived2
           >> failed
           >> vmax
           >> length;
    }
};

struct ATCData {
    int currentSpeed = 0;

    bool shuntingButton = 0;
    bool releaseButton = 0;
    bool increaseButton = 0;
    bool stopPassageButton = 0;
    bool dataEntryButton = 0;

    float brakePressure = 0.0f;

    float STHDial1 = 0;
    float STHDial2 = 0;
    float lengthDial = 0;
    float applyTimeDial1 = 0;
    float applyTimeDial2 = 0;
    float retardationDial1 = 0;
    float retardationDial2 = 0;
    float retardationDial3 = 0;
    float overrideDial = 0;

    void serialize(std::ostream& out) const {
        out << currentSpeed << ' '
            << shuntingButton << ' '
            << releaseButton << ' '
            << increaseButton << ' '
            << stopPassageButton << ' '
            << dataEntryButton << ' '
            << brakePressure << ' '
            << STHDial1 << ' '
            << STHDial2 << ' '
            << lengthDial << ' '
            << applyTimeDial1 << ' '
            << applyTimeDial2 << ' '
            << retardationDial1 << ' '
            << retardationDial2 << ' '
            << retardationDial3 << ' '
            << overrideDial << ' ';
    }

    void deserialize(std::istream& in) {
        in >> currentSpeed
           >> shuntingButton
           >> releaseButton
           >> increaseButton
           >> stopPassageButton
           >> dataEntryButton
           >> brakePressure
           >> STHDial1
           >> STHDial2
           >> lengthDial
           >> applyTimeDial1
           >> applyTimeDial2
           >> retardationDial1
           >> retardationDial2
           >> retardationDial3
           >> overrideDial;
    }
};

struct ATCReturnData {
    int ATCStatus = 0; // 0 = off, 1 = on
    bool toneF1 = 0;
    bool toneF2 = 0;
    bool shuntingLamp = 0;
    char preIndicator0 = ' ';
    char preIndicator1 = ' ';
    char preIndicator2 = ' ';
    bool ATCError = 0;
    bool BaliseError = 0;
    bool speeding = 0;
    char mainIndicator0 = ' ';
    char mainIndicator1 = ' ';
    char mainIndicator2 = ' ';
    bool releaseLamp = 0;
    bool increaseLamp = 0;
    bool dataEntryLamp = 0;
    bool smallError = 0;
    float requestedBrakePressure = 0.0f;

    void serialize(std::ostream& out) const {
        out << ATCStatus << ' '
            << toneF1 << ' '
            << toneF2 << ' '
            << shuntingLamp << ' '
            << (int)preIndicator0 << ' '
            << (int)preIndicator1 << ' '
            << (int)preIndicator2 << ' '
            << ATCError << ' '
            << BaliseError << ' '
            << speeding << ' '
            << (int)mainIndicator0 << ' '
            << (int)mainIndicator1 << ' '
            << (int)mainIndicator2 << ' '
            << releaseLamp << ' '
            << increaseLamp << ' '
            << dataEntryLamp << ' '
            << smallError << ' '
            << requestedBrakePressure << ' ';
    }

    void deserialize(std::istream& in) {
        int p0, p1, p2, m0, m1, m2;
        in >> ATCStatus
           >> toneF1
           >> toneF2
           >> shuntingLamp
           >> p0
           >> p1
           >> p2
           >> ATCError
           >> BaliseError
           >> speeding
           >> m0
           >> m1
           >> m2
           >> releaseLamp
           >> increaseLamp
           >> dataEntryLamp
           >> smallError
           >> requestedBrakePressure;
        preIndicator0 = (char)p0;
        preIndicator1 = (char)p1;
        preIndicator2 = (char)p2;
        mainIndicator0 = (char)m0;
        mainIndicator1 = (char)m1;
        mainIndicator2 = (char)m2;
    }
};