#ifdef _WIN32
#define ATC_API __declspec(dllexport)
#else
#define ATC_API __attribute__((visibility("default")))
#endif

#include "ATC.h"

static struct ATCUnit ATC = {0};
static struct ATCButtonStates ATCButtons = {0};

ATC_API int thisReturnsOne() {
	return 1;
}

ATC_API void resetATC() {
	ATC = (struct ATCUnit){0};
	ATCButtons = (struct ATCButtonStates ){0}; // if they for some reason were not alredy false
}

ATC_API struct ATCUnit getATCData() {
	return ATC;
}

ATC_API void shunting(bool arg) {
	ATC.shunting = arg;
}

//preIndicator

//mainIndicator

ATC_API void releaseButton(bool arg) {
	ATCButtons.releaseButton = arg;
}

ATC_API void increaseButton(bool arg) {
	ATCButtons.increaseButton = arg;
}

ATC_API void brakeSystemSwitch(bool arg) {
	ATC.brakeSystemSwitch = arg;
}

ATC_API void dangerPass(bool arg) {
	ATC.dangerPass = arg;
}

 