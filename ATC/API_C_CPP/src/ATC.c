#ifdef _WIN32
#define ATC_API __declspec(dllexport)
#else
#define ATC_API __attribute__((visibility("default")))
#endif
#include <unistd.h>
#include <stdio.h>
#include "ATCData.h"
#include "RunATC.h"

struct internalATCData internalData = { 0 };
struct ATCData ATC = { 0 };
struct ATCReturnData ATCReturn = { 0 };

int thisReturnsOne() {
    return 1;
}

void setATCData(struct ATCData data) {
    if (data.currentSpeed != NULL)
        ATC.currentSpeed = data.currentSpeed;
    ATC.dataEntryButton = data.dataEntryButton;
}

struct ATCReturnData runATC(struct ATCData data) {
    setATCData(data);
    if (internalData.startup == 0) { // This gets skipped when started cus internalData.startup == 2 at that point
        ATCReturn.ATCStatus = 0;
        return ATCReturn;
    }
    if (internalData.startup == 1)
        startupSequence();

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