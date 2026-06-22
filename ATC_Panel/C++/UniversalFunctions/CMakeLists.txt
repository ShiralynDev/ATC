file(GLOB NETWORKING_SOURCES networking/*.cpp)
file(GLOB DRAWING_SOURCES drawing/*.cpp)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../../../ATC_Universal)
file(GLOB ATCUniversalSources ${CMAKE_CURRENT_LIST_DIR}/../../../ATC_Universal/*.cpp)

add_library(ATCUniversalFunctions STATIC
    ${NETWORKING_SOURCES}
    ${DRAWING_SOURCES}
)

target_include_directories(ATCUniversalFunctions PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/networking
    ${CMAKE_CURRENT_SOURCE_DIR}/drawing
)

target_link_libraries(ATCUniversalFunctions PUBLIC
    ShiraNet
)