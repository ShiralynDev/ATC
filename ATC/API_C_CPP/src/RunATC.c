#include "RunATC.h"
#include "ATCData.h"
#include <time.h>
#include <stdio.h>

struct ATCReturnData startupSequence() {
    time_t seconds = time(NULL);
    if (internalData.seconds == NULL || internalData.seconds == 0) {
        internalData.seconds = seconds;
    }

    ATCReturn.mainIndicator0 = '4';
    ATCReturn.mainIndicator1 = '0';
    ATCReturn.mainIndicator2 = '1';

    if (seconds - internalData.seconds >= 0.5) {
        ATCReturn.mainIndicator0 = '4';
        ATCReturn.mainIndicator1 = '0';
        ATCReturn.mainIndicator2 = '0';
    }

    if (seconds - internalData.seconds >= 3) {
        ATCReturn.mainIndicator0 = '4';
        ATCReturn.mainIndicator1 = '1';
        ATCReturn.mainIndicator2 = '0';
    }

    if (seconds - internalData.seconds >= 4) {
        ATCReturn.mainIndicator0 = '4';
        ATCReturn.mainIndicator1 = '1';
        ATCReturn.mainIndicator2 = '1';
    }

    if (seconds - internalData.seconds >= 5) {
        ATCReturn.mainIndicator0 = ' ';
        ATCReturn.mainIndicator1 = ' ';
        ATCReturn.mainIndicator2 = ' ';
        ATCReturn.ATCError = true;
        ATCReturn.toneF1 = true;
        ATCReturn.toneF2 = true;
        if (ATC.dataEntryButton) {
            internalData.dataEntryButtonPressed = true;
            // make a function to turn on/off all
            ATCReturn.ATCError = false;
            ATCReturn.toneF1 = false;
            ATCReturn.shuntingLamp = true;
            ATCReturn.preIndicator0 = '8';
            ATCReturn.preIndicator1 = '8';
            ATCReturn.preIndicator2 = '8';
            ATCReturn.BaliseError = true;
            ATCReturn.speeding = true;
            ATCReturn.mainIndicator0 = '8';
            ATCReturn.mainIndicator1 = '8';
            ATCReturn.mainIndicator2 = '8';
            ATCReturn.releaseLamp = true;
            ATCReturn.increaseLamp = true;
            ATCReturn.dataEntryLamp = true;
            ATCReturn.smallError = true;
        }
        if (!ATC.dataEntryButton && internalData.dataEntryButtonPressed) {
            // make a function to turn on/off all
            ATCReturn.ATCError = false;
            ATCReturn.toneF1 = false;
            ATCReturn.toneF2 = false;
            ATCReturn.shuntingLamp = false;
            ATCReturn.preIndicator0 = ' ';
            ATCReturn.preIndicator1 = ' ';
            ATCReturn.preIndicator2 = ' ';
            ATCReturn.BaliseError = false;
            ATCReturn.speeding = false;
            ATCReturn.mainIndicator0 = ' ';
            ATCReturn.mainIndicator1 = ' ';
            ATCReturn.mainIndicator2 = ' ';
            ATCReturn.releaseLamp = false;
            ATCReturn.increaseLamp = false;
            ATCReturn.dataEntryLamp = false;
            ATCReturn.smallError = false;

            ATCReturn.ATCStatus = 1;
            internalData.startup = 2;
            internalData.seconds = 0;
            internalData.dataEntryButtonPressed = false;
        }
    }

    return ATCReturn;
}