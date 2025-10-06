#include "ATCDataInput.h"
#include "ATCData.h"
#include "ATCInternalFunctions.h"

void dataInputSequence() {
    int ms = getCurrentTimeMS();
    if (internalData.ms == 0) {
        internalData.ms = ms;
        ATCReturn.increaseLamp = false;
        ATCReturn.dataEntryLamp = false;
        internalData.dataEntryButtonPressed = false;
    }

    if (ms - internalData.ms >= 500) {
        ATCReturn.increaseLamp = !ATCReturn.increaseLamp;
        ATCReturn.dataEntryLamp = !ATCReturn.dataEntryLamp;
        internalData.ms = ms;
    }

    if (ATC.dataEntryButton) {
        internalData.dataEntryButtonPressed = true;
        turnOnAll();
        ATCReturn.ATCError = false;
        ATCReturn.toneF1 = false;
    }
    if (!ATC.dataEntryButton && internalData.dataEntryButtonPressed) {
        turnOffAll();
        internalData.ms = 0;
        internalData.dataEntryButtonPressed = false;
        internalData.startup = 3;
    }

    return;
}