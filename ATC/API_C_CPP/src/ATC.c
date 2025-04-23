#ifdef _WIN32
#define ATC_API __declspec(dllexport)
#else
#define ATC_API __attribute__((visibility("default")))
#endif

#include "ATC.h"

static struct ATCData ATC = { 0 };

int thisReturnsOne() {
    return 1;
}