cmake_minimum_required(VERSION 3.13)
set(PICO_BOARD pico_w)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(edge C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

if (NOT DEFINED WIFI_SSID)
    message(FATAL_ERROR "add -DWIFI_SSID=SSID flag or set env.")
endif()

if (NOT DEFINED WIFI_PASSWD)
    message(FATAL_ERROR "add -DWIFI_PASSWD=PASSWD flag or set env.")
endif()

pico_sdk_init()

add_subdirectory(src)
