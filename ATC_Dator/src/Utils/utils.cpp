#include "utils.hpp"

void ATC::turnOffAll(ATCReturnData &returnData) {
    returnData.ATCError = false;
    returnData.toneF1 = false;
    returnData.toneF2 = false;
    returnData.shuntingLamp = false;
    returnData.preIndicator0 = ' ';
    returnData.preIndicator1 = ' ';
    returnData.preIndicator2 = ' ';
    returnData.ATCError = false;
    returnData.BaliseError = false;
    returnData.speeding = false;
    returnData.mainIndicator0 = ' ';
    returnData.mainIndicator1 = ' ';
    returnData.mainIndicator2 = ' ';
    returnData.releaseLamp = false;
    returnData.increaseLamp = false;
    returnData.dataEntryLamp = false;
    returnData.smallError = false;
}

void ATC::turnOnAll(ATCReturnData &returnData) {
    returnData.ATCError = true;
    returnData.toneF1 = true;
    returnData.toneF2 = true;
    returnData.shuntingLamp = true;
    returnData.preIndicator0 = '8';
    returnData.preIndicator1 = '8';
    returnData.preIndicator2 = '8';
    returnData.ATCError = true;
    returnData.BaliseError = true;
    returnData.speeding = true;
    returnData.mainIndicator0 = '8';
    returnData.mainIndicator1 = '8';
    returnData.mainIndicator2 = '8';
    returnData.releaseLamp = true;
    returnData.increaseLamp = true;
    returnData.dataEntryLamp = true;
    returnData.smallError = true;
}