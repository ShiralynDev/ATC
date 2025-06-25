#ifdef _WIN32
#define ATC_API __declspec(dllexport)
#else
#define ATC_API __attribute__((visibility("default")))
#endif
#include <unistd.h>
#include <stdio.h>
#include "ATCData.h"
#include "ATCStartup.h"
#include "ATCDataInput.h"

// https://bransch.trafikverket.se/contentassets/438381cb6c794b85a28d090b0c280b70/handbok--trvinfra-90001-v1_0.pdf

struct internalATCData internalData = { 0 };
struct ATCData ATC = { 0 };
struct ATCReturnData ATCReturn = { 0 };

int thisReturnsOne() {
    return 1;
}

void initATC() { // Run this before using the ATC
    internalData.ABBVersion = false;
    internalData.achived2 = false;
    internalData.achived1 = false;
    internalData.achived = false;
    internalData.dataEntryButtonPressed = false;
    internalData.ms = 0;
    internalData.startup = 0;
}

void setATCData(struct ATCData data) {
    ATC.currentSpeed = data.currentSpeed;
    ATC.dataEntryButton = data.dataEntryButton;
    ATC.brakePressure = data.brakePressure;
}

struct ATCReturnData runATC(struct ATCData data) {
    setATCData(data);
    if (internalData.startup == 0) { // This gets skipped when started cus internalData.startup == 2 at that point
        ATCReturn.ATCStatus = 0;
        return ATCReturn;
    }

    if (internalData.startup == 1)
        startupSequence();
    if (internalData.startup == 2)
        dataInputSequence();

    return ATCReturn;
}

void toggleATC(int on) {
    if (on >= 0 && on <= 2)
        internalData.startup = on;
}

void toggleSystemType(bool useABB) {
    internalData.ABBVersion = useABB;
}

bool getSystemType() {
    return internalData.ABBVersion;
}