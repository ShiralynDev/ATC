#include "ATCDataInput.h"
#include "ATCData.h"

void dataInputSequence() {
    int ms = getCurrentTimeMS();
    if (internalData.ms == 0) {
        internalData.ms = ms;
        ATCReturn.increaseLamp = false;
        ATCReturn.dataEntryLamp = false;
    }

    if (ms - internalData.ms >= 500) {
        ATCReturn.releaseLamp = !ATCReturn.increaseLamp;
        ATCReturn.dataEntryLamp = !ATCReturn.dataEntryLamp;
        internalData.ms = ms;
    }

    return;
}