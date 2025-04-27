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
    ATCReturn.mainIndicator2 = '0';

    if (seconds - internalData.seconds >= 5) {
        ATCReturn.mainIndicator0 = ' ';
        ATCReturn.mainIndicator1 = ' ';
        ATCReturn.mainIndicator2 = ' ';
        ATCReturn.ATCStatus = 1;
        internalData.startup = 2;
        internalData.seconds = 0;
    }

    return ATCReturn;
}