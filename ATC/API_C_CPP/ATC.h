#include <stdbool.h>

#define växling shunting
#define förIndikator preIndicator
#define balis balise
#define bromsverksomkopplare brakeSystemSwitch
#define stoppassage dangerPass
#define STH Vmax //Största Tillåtna Hastighet
#define retardationstal redardationRate
#define Överskridande exceedance
#define lossningsKnapp releaseButton

// "Translating" The Swedish railway terms to the general English railway terms to make it work with both
// Also this is a programming warcrime I believe

struct ATCUnit {

	int currentSpeed;
	int currentDrivingSpeed;
};