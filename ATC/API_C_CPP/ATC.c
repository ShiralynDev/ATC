#ifdef _WIN32
#define ATC_API __declspec(dllexport)
#else
#define ATC_API __attribute__((visibility("default")))
#endif

#include "ATC.h"

static struct ATCUnit ATC = { 0 };

ATC_API int thisRetunsOne() {
    return 1;
}