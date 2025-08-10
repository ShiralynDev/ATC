cmake_minimum_required(VERSION 3.20)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

project(ATCEXAMPLE)
set(CMAKE_CXX_STANDARD 20) # Use C++ 20
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Release mode
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(BUILD_SHARED_LIBS ON)
set(BUILD_EXAMPLES OFF)

add_subdirectory(./extern/raylib)
include_directories(./extern/raylib/) 

include_directories(./extern/RaylibAdditions) 
file(GLOB_RECURSE RAYLIB_ADDITIONS_SOURCES ./extern/RaylibAdditions/*.cpp)

file(GLOB SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_subdirectory(../../ATC/API_C_CPP ATCAPI)
include_directories(../../ATC/API_C_CPP/include)

# Create the executable
add_executable(ATCEXAMPLE ${SOURCES} ${RAYLIB_ADDITIONS_SOURCES})

# Link libraries
target_link_libraries(ATCEXAMPLE PRIVATE raylib)
target_link_libraries(ATCEXAMPLE PRIVATE ATCAPI)

# Apply Release mode specific settings
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    # Add optimization flags
    target_compile_options(ATCEXAMPLE PRIVATE -O3)
    
    # Optionally, strip symbols to reduce binary size
    if (NOT WIN32)
        target_link_options(ATCEXAMPLE PRIVATE -s)
    endif()
endif()
