cmake_minimum_required(VERSION 3.20)
project(ATC)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(extern/ShiraNet)

add_subdirectory(ATC_Dator)
#add_subdirectory(ATC_Panel/C++/DebugPanel)
add_subdirectory(ATC_Panel/C++/ExtendedDebugPanel)
#add_subdirectory(ATC_Panel/C++/SimplePanel)