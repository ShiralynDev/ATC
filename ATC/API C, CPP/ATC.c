#ifdef _WIN32
#define ATC_API __declspec(dllexport)
#else
#define ATC_API __attribute__((visibility("default")))
#endif

#include "ATC.h"

static struct ATCUnit ATC = { 0 };

// Resets the ATC unit
ATC_API void resetATC() {
	ATC = (struct ATCUnit){ 0 };
}

// Turn ATC on/off
ATC_API void powerATC(bool arg) {
	ATC.power = arg;
}

// Sets the shunting of the ATC unit
ATC_API void shunting(bool arg) {
	ATC.shunting = arg;
}

//preIndicator

// ATC error

// balise error

// speeding lamp

//mainIndicator

//ATC break

/// <summary>
/// Takes a bool to turn on / off the Release Button
/// </summary>
/// <param name="bool arg"></param>
/// <returns>Returns 0 on valid and 1 on invalid</returns>
ATC_API int releaseButton(bool arg) {
	if (ATC.power != true || ATC.ATCBrakeLamp == 0)
		return 1;
	ATC.releaseButton = arg;
	return 0;
}

/// <summary>
/// Takes a bool to turn on / off the Increase Button
/// </summary>
/// <param name="bool arg"></param>
/// <returns>Returns 0 on valid and 1 on invalid</returns>
ATC_API int increaseButton(bool arg) {
	if (ATC.power != true || ATC.increaseLamp == 0) 
		return 1;
	ATC.increaseButton = arg;
	return 0;
}

ATC_API int brakeSystemSwitch(bool arg) {
	if (ATC.power != true)
		return 1;
	ATC.brakeSystemSwitch = arg;
	return 0;
}

ATC_API int dangerPass(bool arg) {
	if (ATC.power != true)
		return 1;
	ATC.dangerPass = arg;
	return 0;
}

ATC_API void setBrightness(float brightness) {
	ATC.brightness = brightness;
}

ATC_API void setVolume(float volume) {
	ATC.volume = volume;
 }