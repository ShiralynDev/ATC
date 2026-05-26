#include "startup.hpp"
#include <cmath>

void ATC::Startup::errors(ATCData &data, internalATCData &internalData, ATCReturnData &returnData) {
    if (std::trunc(data.STHDial2) != data.STHDial2) { // move to error check function or something // only in phase 0 of startup?
        internalData.failed = true;
        returnData.mainIndicator1 = '0';
        returnData.preIndicator1 = '1';
        returnData.preIndicator2 = '1';
    }
    if (std::trunc(data.STHDial1) != data.STHDial1) {
        internalData.failed = true;
        returnData.mainIndicator1 = '0';
        returnData.preIndicator1 = '1';
        returnData.preIndicator2 = '2';
    }
    if (std::trunc(data.lengthDial) != data.lengthDial) {
        internalData.failed = true;
        returnData.mainIndicator1 = '0';
        returnData.preIndicator1 = '1';
        returnData.preIndicator2 = '3';
    }
    if (std::trunc(data.retardationDial3) != data.retardationDial3) {
        internalData.failed = true;
        returnData.mainIndicator1 = '0';
        returnData.preIndicator1 = '1';
        returnData.preIndicator2 = '4';
    }
    if (std::trunc(data.retardationDial2) != data.retardationDial2) {
        internalData.failed = true;
        returnData.mainIndicator1 = '0';
        returnData.preIndicator1 = '1';
        returnData.preIndicator2 = '5';
    }
    if (std::trunc(data.retardationDial1) != data.retardationDial1) {
        internalData.failed = true;
        returnData.mainIndicator1 = '0';
        returnData.preIndicator1 = '1';
        returnData.preIndicator2 = '6';
    }
    if (std::trunc(data.applyTimeDial2) != data.applyTimeDial2) {
        internalData.failed = true;
        returnData.mainIndicator1 = '0';
        returnData.preIndicator1 = '1';
        returnData.preIndicator2 = '7';
    }
    if (std::trunc(data.applyTimeDial1) != data.applyTimeDial1) {
        internalData.failed = true;
        returnData.mainIndicator1 = '0';
        returnData.preIndicator1 = '1';
        returnData.preIndicator2 = '8';
    }
    if (std::trunc(data.overrideDial) != data.overrideDial) {
        internalData.failed = true;
        returnData.mainIndicator1 = '0';
        returnData.preIndicator1 = '1';
        returnData.preIndicator2 = '9';
    }
    if (data.stopPassageButton) {
        internalData.failed = true;
        returnData.mainIndicator1 = '0';
        returnData.preIndicator1 = '3';
        returnData.preIndicator2 = '2';
    }
    if (data.dataEntryButton) {
        internalData.failed = true;
        returnData.mainIndicator1 = '0';
        returnData.preIndicator1 = '4';
        returnData.preIndicator2 = '1';
    }
    if (data.shuntingButton) {
        internalData.failed = true;
        returnData.mainIndicator1 = '0';
        returnData.preIndicator1 = '4';
        returnData.preIndicator2 = '2';
    }
    if (data.increaseButton) {
        internalData.failed = true;
        returnData.mainIndicator1 = '0';
        returnData.preIndicator1 = '4';
        returnData.preIndicator2 = '3';
    }
    if (data.releaseButton) {
        internalData.failed = true;
        returnData.mainIndicator1 = '0';
        returnData.preIndicator1 = '4';
        returnData.preIndicator2 = '4';
    }
}