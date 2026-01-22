cmake_minimum_required(VERSION 3.20)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

project(ATC_Dator)
set(CMAKE_CXX_STANDARD 20) # Use C++ 20
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Release mode
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(BUILD_SHARED_LIBS ON)
set(BUILD_EXAMPLES OFF)

file(GLOB SOURCES ${CMAKE_CURRENT_LIST_DIR}/src/*.cpp)
file(GLOB_RECURSE UniversalFunctionsSources ${CMAKE_CURRENT_LIST_DIR}/../UniversalFunctions/*.cpp)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

# Create the executable
add_executable(ATC_Dator ${SOURCES} ${UniversalFunctionsSources})

target_include_directories(ATC_Dator PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../UniversalFunctions
)

# Apply Release mode specific settings
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    # Add optimization flags
    target_compile_options(ATC_Dator PRIVATE -O3)
    
    # Optionally, strip symbols to reduce binary size
    if (NOT WIN32)
        target_link_options(ATC_Dator PRIVATE -s)
    endif()
endif()
