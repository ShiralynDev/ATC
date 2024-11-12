cmake_minimum_required(VERSION 3.10)
project(ATCLib)

# Set the library type (SHARED for DLL/.so, STATIC for static library)
add_library(ATCLib SHARED ATC.c)

# Define the export macro for Windows builds
if(WIN32)
    target_compile_definitions(ATCLib PRIVATE _EXPORTING)
endif()

# Specify output properties
set_target_properties(ATCLib PROPERTIES
    OUTPUT_NAME "ATCLib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

message(FATAL ${ATCLIB})