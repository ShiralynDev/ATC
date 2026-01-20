#include "ATCErrors.h"
#include "ATCData.h"

void startupErrors() {
    if (ATC.STHDial2 % 2) { // move to error check function or something // only in phase 0 of startup?
        internalData.failed = true;
        ATCReturn.mainIndicator1 = '0';
        ATCReturn.preIndicator1 = '1';
        ATCReturn.preIndicator2 = '1';
    }
    if (ATC.STHDial1 % 2) {
        internalData.failed = true;
        ATCReturn.mainIndicator1 = '0';
        ATCReturn.preIndicator1 = '1';
        ATCReturn.preIndicator2 = '2';
    }
    if (ATC.lengthDial % 2) {
        internalData.failed = true;
        ATCReturn.mainIndicator1 = '0';
        ATCReturn.preIndicator1 = '1';
        ATCReturn.preIndicator2 = '3';
    }
    if (ATC.retardationDial3 % 2) {
        internalData.failed = true;
        ATCReturn.mainIndicator1 = '0';
        ATCReturn.preIndicator1 = '1';
        ATCReturn.preIndicator2 = '4';
    }
    if (ATC.retardationDial2 % 2) {
        internalData.failed = true;
        ATCReturn.mainIndicator1 = '0';
        ATCReturn.preIndicator1 = '1';
        ATCReturn.preIndicator2 = '5';
    }
    if (ATC.retardationDial1 % 2) {
        internalData.failed = true;
        ATCReturn.mainIndicator1 = '0';
        ATCReturn.preIndicator1 = '1';
        ATCReturn.preIndicator2 = '6';
    }
    if (ATC.applyTimeDial2 % 2) {
        internalData.failed = true;
        ATCReturn.mainIndicator1 = '0';
        ATCReturn.preIndicator1 = '1';
        ATCReturn.preIndicator2 = '7';
    }
    if (ATC.applyTimeDial1 % 2) {
        internalData.failed = true;
        ATCReturn.mainIndicator1 = '0';
        ATCReturn.preIndicator1 = '1';
        ATCReturn.preIndicator2 = '8';
    }
    if (ATC.overrideDial % 2) {
        internalData.failed = true;
        ATCReturn.mainIndicator1 = '0';
        ATCReturn.preIndicator1 = '1';
        ATCReturn.preIndicator2 = '9';
    }
    if (ATC.stopPassageButton) {
        internalData.failed = true;
        ATCReturn.mainIndicator1 = '0';
        ATCReturn.preIndicator1 = '3';
        ATCReturn.preIndicator2 = '2';
    }
    if (ATC.dataEntryButton) {
        internalData.failed = true;
        ATCReturn.mainIndicator1 = '0';
        ATCReturn.preIndicator1 = '4';
        ATCReturn.preIndicator2 = '1';
    }
    if (ATC.shuntingButton) {
        internalData.failed = true;
        ATCReturn.mainIndicator1 = '0';
        ATCReturn.preIndicator1 = '4';
        ATCReturn.preIndicator2 = '2';
    }
    if (ATC.increaseButton) {
        internalData.failed = true;
        ATCReturn.mainIndicator1 = '0';
        ATCReturn.preIndicator1 = '4';
        ATCReturn.preIndicator2 = '3';
    }
    if (ATC.releaseButton) {
        internalData.failed = true;
        ATCReturn.mainIndicator1 = '0';
        ATCReturn.preIndicator1 = '4';
        ATCReturn.preIndicator2 = '4';
    }
}