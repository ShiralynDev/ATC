/*
#include <emscripten/emscripten.h>
EMSCRIPTEN_KEEPALIVE
*/ // Use this code when compiling to WASM/JS
//Todo: make JS use the DLL and build a wrapper instead of WASM

#define STH Vmax //Största Tillåtna Hastighet
// "Translating" The Swedish railway terms to the general English railway terms to make it work with both
// Also this is a programming warcrime I believe

struct ATCData {
	int Vmax;	//saved in km/h
	int Length;	//saved in meters

};

__declspec(dllexport) int thisReturnsOne() {
	return 1;
}
