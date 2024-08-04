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
	bool power;
	bool shunting;
	bool shuntingLamp;
	int preIndicator;
	bool ATCErrorLamp;
	bool baliseErrorLamp;
	bool speedingLamp;
	int mainIndicator;
	int ATCBrakeLamp;
	bool releaseButton;
	int increaseLamp;
	bool increaseButton;
	bool increaseLamp;
	bool brakeSystemSwitch;
	bool dangerPass;
	float brightness;
	float volume;
	bool confirmButton;
	bool confirmLight;
	int Vmax;				//saved in km/h
	int length;				//saved in meters
	int applyTime;
	int redardationRate;	// saved in m/s2 // if 258 then Stax D // if 298 then normal setting
	int exceedance;			// saved in percentage
	bool lampError;
	char sound[2];

	int currentSpeed;
	int currentDrivingSpeed;
};