#ifdef _WIN32
#define ATC_API __declspec(dllimport)
#else
#define ATC_API extern
#endif

extern "C" {
    ATC_API int thisReturnsOne();
}

#include <iostream>

int main() {
    std::cout << "Hello world!";
    std::cout << thisReturnsOne();
    return 0;
}