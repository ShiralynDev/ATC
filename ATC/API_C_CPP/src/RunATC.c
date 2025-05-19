#include "RunATC.h"
#include "ATCData.h"
#include <time.h>
#include <stdio.h>
#include "ATCInternalFunctions.h"

long long getCurrentTimeMS() {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return (long long)ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}

void startupSequence() {
    int startupTime = 0;
    int ms = getCurrentTimeMS();
    if (internalData.ms == 0) {
        internalData.ms = ms;
    }
    if (startupTime == 0) {
        if (internalData.ABBVersion) startupTime = 5000;
        if (!internalData.ABBVersion) startupTime = 8000;
    }

    if (ms - internalData.ms <= 100) {
        turnOnAll();
        ATCReturn.toneF1 = false;
        ATCReturn.toneF2 = false;
        return;
    }
    turnOffAll();

    if (ms - internalData.ms <= 300) return;

    if (ms - internalData.ms <= 500) {
        ATCReturn.ATCError = true;
        ATCReturn.toneF1 = true;
        return;
    }
    ATCReturn.ATCError = false;
    ATCReturn.toneF1 = false;

    if (internalData.ABBVersion) {
        ATCReturn.mainIndicator0 = '4';
        ATCReturn.mainIndicator1 = '0';
        ATCReturn.mainIndicator2 = '1';

        if (ms - internalData.ms >= 700) {
            ATCReturn.mainIndicator0 = '4';
            ATCReturn.mainIndicator1 = '0';
            ATCReturn.mainIndicator2 = '0';
        }

        if (ms - internalData.ms >= 3000) {
            ATCReturn.mainIndicator0 = '4';
            ATCReturn.mainIndicator1 = '1';
            ATCReturn.mainIndicator2 = '0';
        }

        if (ms - internalData.ms >= 4000) {
            ATCReturn.mainIndicator0 = '4';
            ATCReturn.mainIndicator1 = '1';
            ATCReturn.mainIndicator2 = '1';
        }
    } else {
        ATCReturn.mainIndicator1 = '0';

        if (ms - internalData.ms >= 1000) ATCReturn.mainIndicator1 = '1';
        if (ms - internalData.ms >= 1500) ATCReturn.mainIndicator1 = '2';
        if (ms - internalData.ms >= 1600) ATCReturn.mainIndicator1 = '3';
        if (ms - internalData.ms >= 2300) ATCReturn.mainIndicator1 = '4';
        if (ms - internalData.ms >= 3000) ATCReturn.mainIndicator1 = '5';
        if (ms - internalData.ms >= 7000) ATCReturn.mainIndicator1 = '6';
    }

    if (ms - internalData.ms >= startupTime) {
        ATCReturn.mainIndicator0 = ' ';
        ATCReturn.mainIndicator1 = ' ';
        ATCReturn.mainIndicator2 = ' ';
        ATCReturn.ATCError = true;
        ATCReturn.toneF1 = true;
        ATCReturn.toneF2 = true;
        if (ATC.dataEntryButton) {
            internalData.dataEntryButtonPressed = true;
            turnOnAll();
            ATCReturn.ATCError = false;
            ATCReturn.toneF1 = false;
        }
        if (!ATC.dataEntryButton && internalData.dataEntryButtonPressed) {
            turnOffAll();
            ATCReturn.ATCStatus = 1;
            internalData.startup = 2;
            internalData.ms = 0;
            internalData.dataEntryButtonPressed = false;
        }
    }
}