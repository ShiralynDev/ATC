#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

/*
#define växling shunting
#define förIndikator preIndicator
#define balis balise
#define bromsverksomkopplare brakeSystemSwitch
#define stoppassage dangerPass
#define STH Vmax //Största Tillåtna Hastighet
#define retardationstal redardationRate
#define Överskridande exceedance
#define lossningsKnapp releaseButton
Ignore for now, might be added back later
*/

// "Translating" The Swedish railway terms to the general English railway terms to make it work with both
// Also this is a programming warcrime I believe

/*
Plan:
Use a "callback" function to run everything
Allow using functions to set ATC aswell as allowing passing it trough the runCallbacks function, data should be null-able in the callbacks function incase... 
the developer want to set the data in their functions for pressing a button ect
*/

struct ATCData {
	int currentSpeed;
	int currentDrivingSpeed;
};

struct ATCReturnData {
	int ATCStatus;
};

int thisReturnsOne();

#ifdef __cplusplus
}
#endif
