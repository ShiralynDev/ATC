#include "startup.hpp"
#include "ATCData.hpp"
#include "../Utils/utils.hpp"

#include <chrono>

int ATC::Startup::ms = 0;

bool floatCompare(float a, float b) {
    if (a - b > 0.01 || a - b > -0.01)
        return true;
    return false;
}

void ATC::startupSequence(ATCData &data, internalATCData &internalData, ATCReturnData &returnData, bool isCabA) { // Rewrite for better "stages" system and better times aswell as use the brake during startup
    // https://bransch.trafikverket.se/contentassets/438381cb6c794b85a28d090b0c280b70/handbok--trvinfra-90001-v1_0.pdf // Page 18 for error codes
    /*
    To be added:
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

    if (isCabA != internalData.isCabA) {
        returnData.preIndicator1 = '0';
        returnData.preIndicator2 = '1';
        returnData.mainIndicator1 = '0';
        return;
    }

    returnData.ATCStatus = 1;

    // I hate this timebased system
    int startupTime = 0;
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    int ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    if (ATC::Startup::ms == 0) {
        internalData.startup = 1;
        ATC::Startup::ms = ms;
    }

    if (startupTime == 0) {
        if (internalData.ABBVersion)
            startupTime = 5000;
        if (!internalData.ABBVersion)
            startupTime = 8000;
    }

    if (ms - ATC::Startup::ms <= 100) {
        ATC::turnOnAll(returnData);
        returnData.toneF1 = false;
        returnData.toneF2 = false;
        return;
    }

    if (ms - ATC::Startup::ms <= 120) {
        ATC::turnOffAll(returnData);
        return;
    }

    if (ms - ATC::Startup::ms <= 300)
        return;

    if (ms - ATC::Startup::ms <= 500) {
        returnData.ATCError = true;
        returnData.toneF1 = true;
        return;
    }
    returnData.ATCError = false;
    returnData.toneF1 = false;

    if (internalData.ABBVersion) {
        returnData.mainIndicator0 = '4';
        returnData.mainIndicator1 = '0';
        returnData.mainIndicator2 = '1';

        if (ms - ATC::Startup::ms >= 700) {
            returnData.mainIndicator0 = '4';
            returnData.mainIndicator1 = '0';
            returnData.mainIndicator2 = '0';
        }

        if (ms - ATC::Startup::ms >= 3000) {
            returnData.mainIndicator0 = '4';
            returnData.mainIndicator1 = '1';
            returnData.mainIndicator2 = '0';
        }

        if (ms - ATC::Startup::ms >= 4000) {
            returnData.mainIndicator0 = '4';
            returnData.mainIndicator1 = '1';
            returnData.mainIndicator2 = '1';
        }
    } else {
        returnData.mainIndicator1 = '0';

        if (ms - ATC::Startup::ms >= 1000)
            returnData.mainIndicator1 = '1';
        if (ms - ATC::Startup::ms >= 1500)
            returnData.mainIndicator1 = '2';
        if (ms - ATC::Startup::ms >= 1600)
            returnData.mainIndicator1 = '3';
        if (ms - ATC::Startup::ms >= 2300)
            returnData.mainIndicator1 = '4';
        if (ms - ATC::Startup::ms >= 3000)
            returnData.mainIndicator1 = '5';

        if (ms - ATC::Startup::ms >= 1000) // phase 1
            ATC::Startup::errors(data, internalData, returnData);

        if (!internalData.achived)
            returnData.requestedBrakePressure = 5.0f;

        if (floatCompare(data.brakePressure, 5.0f) && !internalData.achived && ms - ATC::Startup::ms >= 3000) {
            returnData.requestedBrakePressure = 4.0f;
            internalData.achived = true;
        }

        if (internalData.achived && floatCompare(data.brakePressure, 4.0f) && !internalData.achived1) {
            internalData.achived1 = true;
            returnData.requestedBrakePressure = 5.0f;
        }

        if (internalData.achived1 && floatCompare(data.brakePressure, 5.0f) && !internalData.achived2)
            internalData.achived2 = true;

        if (ms - ATC::Startup::ms >= 7000 && !internalData.achived2) { // startup failed
            internalData.failed = true;
            if (data.brakePressure < 4.12f) { // Failed to increase pressure by 0.12 bar, error code 06 5
                returnData.preIndicator1 = '0';
                returnData.preIndicator2 = '6';
            }
            if (data.brakePressure > 4.75f) { // Failed to lower pressure by 0.25 or more bar, error code 01 5
                returnData.preIndicator1 = '0';
                returnData.preIndicator2 = '1';
            }
        }

        if (ms - ATC::Startup::ms >= 7000 && internalData.achived2) { // no fail
            returnData.mainIndicator1 = '6';
            returnData.requestedBrakePressure = 0.0f;
        }

        if (internalData.failed) {
            returnData.ATCStatus = 0;
            internalData.startup = 0;
            ATC::Startup::ms = 0;
            internalData.dataEntryButtonPressed = false;
            internalData.failed = false;
        }
    }

    if (ms - ATC::Startup::ms >= startupTime) {
        returnData.mainIndicator0 = ' ';
        returnData.mainIndicator1 = ' ';
        returnData.mainIndicator2 = ' ';
        returnData.ATCError = true;
        returnData.toneF1 = true;
        returnData.toneF2 = true;
        if (data.dataEntryButton) {
            internalData.dataEntryButtonPressed = true;
            ATC::turnOnAll(returnData);
            returnData.ATCError = false;
            returnData.toneF1 = false;
        }
        if (!data.dataEntryButton && internalData.dataEntryButtonPressed) {
            ATC::turnOffAll(returnData);
            internalData.startup = 2;
            ATC::Startup::ms = 0;
            internalData.dataEntryButtonPressed = false;
            internalData.achived = false;
            internalData.achived1 = false;
            internalData.achived2 = false;
        }
    }
}