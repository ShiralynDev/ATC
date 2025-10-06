#include "ATCStartup.h"
#include "ATCData.h"
#include <stdio.h>
#include <math.h>
#include "ATCInternalFunctions.h"

bool floatCompare(float a, float b) {
    return fabsf(a - b) < 0.1;
}

void startupSequence() { // Rewrite for better "stages" system and better times aswell as use the brake during startup
    // https://bransch.trafikverket.se/contentassets/438381cb6c794b85a28d090b0c280b70/handbok--trvinfra-90001-v1_0.pdf // Page 18 for error codes
    /*
    To be added:
    Preind 01 MainInd 0   2 cabs activated
    Preind 02 MainInd 0   No contact with the panel
    Preind 03 MainInd 0   No contact with the "manöverenheten"

    // translate
       1 Hastighetsmätarkonstanter
    2    Hastighetsmätaringångar
    02 2 Lokanpassningsfel
       3 Transmissionstest (Transmission = sändare/mottagare + antenn)
    02 3 Fel i antenn / kabel / transmissionskassett.
    06 3 Balisupptäckt med sändaren frånslagen

       4 Bromstryck m.m.
    01 4 Tryckgivarfel
    02 4 Tryckgivarfel
    03 4 Systembroms obehörigt aktiv
    04 4 Nödbromsreläkontakt obehörigt öppen
    05 4 Huvudledningstrycket < 4,0 bar
    06 4 Huvudledningstrycket > 5,5 bar
    07 4 Huvudledningstrycket har ej stabiliserats (får variera högst 0,2 bar på 3 sekunder)

       6 Systemnödbromsning
    01 6 Någon reläkontakt öppnar ej
    07 6 Trycksänkning på 0,6 bar har ej uppmätts inom 0,5 sekunder efter prov av systemnödbroms

    Alredy added:
       5 Systembromsning
    01 5 Trycksänkningen < 0,25 bar
    06 5 Efter lossning har trycket ej stigit minst 0,12 bar

    11 0   "thumb wheel" Vmax, right, wrong/wrongly
    12 0   "thumb wheel" Vmax, left, wrong/wrongly
    13 0   "thumb wheel" train length, wrong/wrongly
    14 0 Tumhjul Retardation, höger felaktigt
    15 0 Tumhjul Retardation, mitten felaktigt
    16 0 Tumhjul Retardation, vänster felaktigt
    17 0 Tumhjul Bromstillsättningstid, höger felaktigt
    18 0 Tumhjul Bromstillsättningstid, vänster 
    32 0 Button Stop passage pressed
    41 0 Button Input pressed
    42 0 Button Shunting pressed
    43 0 Button Increase pressed
    44 0 Button Release pressed
    */
   
    ATCReturn.ATCStatus = 1;

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

        if (ATC.STHDial2 % 2) { // move to error check function or something
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
        if (ATC.dataEntryButton && !(ms - internalData.ms >= startupTime)) {
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


        if (!internalData.achived)
            ATCReturn.requestedBrakePressure = 5.0f;

        if (floatCompare(ATC.brakePressure, 5.0f) && !internalData.achived && ms - internalData.ms >= 3000) {
            ATCReturn.requestedBrakePressure = 4.0f;
            internalData.achived = true;
        }
        
        if (internalData.achived && floatCompare(ATC.brakePressure, 4.0f) && !internalData.achived1) {
            internalData.achived1 = true;
            ATCReturn.requestedBrakePressure = 5.0f;
        }

        if (internalData.achived1 && floatCompare(ATC.brakePressure, 5.0f) && !internalData.achived2)
            internalData.achived2 = true;
        
        if (ms - internalData.ms >= 7000 && !internalData.achived2) { // startup failed
            internalData.failed = true;
            if (ATC.brakePressure < 4.12f) { // Failed to increase pressure by 0.12 bar, error code 06 5
                ATCReturn.preIndicator1 = '0';
                ATCReturn.preIndicator2 = '6';
            }
            if (ATC.brakePressure > 4.75f) { // Failed to lower pressure by 0.25 or more bar, error code 01 5
                ATCReturn.preIndicator1 = '0';
                ATCReturn.preIndicator2 = '1';
            }
        } 

        if (ms - internalData.ms >= 7000 && internalData.achived2) { // no fail
            ATCReturn.mainIndicator1 = '6';
            ATCReturn.requestedBrakePressure = 0.0f;
        }

        if (internalData.failed) {
            ATCReturn.ATCStatus = 0;
            internalData.startup = 0;
            internalData.ms = 0;
            internalData.dataEntryButtonPressed = false;
            internalData.failed = false;
        }
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
            internalData.startup = 2;
            internalData.ms = 0;
            internalData.dataEntryButtonPressed = false;
            internalData.achived = false;
            internalData.achived1 = false;
            internalData.achived2 = false;
        }
    }
}