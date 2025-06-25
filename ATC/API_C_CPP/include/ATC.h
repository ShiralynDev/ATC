#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <time.h>

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

struct internalATCData {
	int startup; // 0 = off, 1 = startup, 2 = running/data input, 3 = running, data inputed
	int ms;
	bool dataEntryButtonPressed;
	bool ABBVersion; // SRT/ATSS/Ansaldo on false, ABB on true
	bool achived; // Used as a general varible to save data
	bool achived1; // Used as a general varible to save data
	bool achived2; // Used as a general varible to save data
};

struct ATCData {
	int currentSpeed;
	bool dataEntryButton;
	float brakePressure;
};

struct ATCReturnData {
	int ATCStatus; // 0 = off, 1 = on
	bool toneF1;
	bool toneF2;
	bool shuntingLamp;
	char preIndicator0;
	char preIndicator1;
	char preIndicator2;
	bool ATCError;
	bool BaliseError;
	bool speeding;
	char mainIndicator0;
	char mainIndicator1;
	char mainIndicator2;
	bool releaseLamp;
	bool increaseLamp;
	bool dataEntryLamp;
	bool smallError;
	float requestedBrakePressure;
};

int thisReturnsOne();

void initATC();
void setATCData(struct ATCData data); // Updates the ATC's data with the inputed data, will not update to null values
struct ATCReturnData runATC(struct ATCData data); // The function to process ATC data (preferably ran on another thread)
void toggleATC(int on); // Toggle startup, 1 = startup/started, 0 = off/turn off, 2 = skip startup/started
void toggleSystemType(bool useABB); // true = use ABB, false = use SRT/ATSS/Ansaldo
bool getSystemType();

#ifdef __cplusplus
}
#endif
