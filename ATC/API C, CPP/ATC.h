#include <stdbool.h>

#define växling shunting
#define förIndikator preIndicator
#define balis balise
#define bromsverksomkopplare brakeSystemSwitch
#define stoppassage dangerPass
#define STH Vmax //Största Tillåtna Hastighet
#define retardationstal redardationRate
#define överskridande exceedance
#define lossningsKnapp releaseButton

// "Translating" The Swedish railway terms to the general English railway terms to make it work with both
// Also this is a programming warcrime I believe

struct ATCUnit {
	bool shunting;
	bool shuntingLamp;
	int preIndicator;
	bool ATCErrorLamp;
	bool baliseErrorLamp;
	bool speedingLamp;
	int mainIndicator;
	bool ATCBrakeLamp;
	bool increaseLamp;
	bool brakeSystemSwitch;
	bool dangerPass;
	int brightness;
	int volume;
	int Vmax;				//saved in km/h
	int length;				//saved in meters
	int redardationRate;	// saved in m/s2 // if 258 then Stax D // if 298 then normal setting
	int exceedance;			// saved in percentage
	char sound[2];
};

struct ATCButtonStates {
	bool releaseButton;
	bool increaseButton;
};