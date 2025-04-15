cmake_minimum_required(VERSION 3.13)
set(PICO_BOARD pico_w)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
project(edge C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (NOT DEFINED WIFI_SSID)
    message(FATAL_ERROR "add -DWIFI_SSID=SSID flag or set env.")
endif()

if (NOT DEFINED WIFI_PASSWD)
    message(FATAL_ERROR "add -DWIFI_PASSWD=PASSWD flag or set env.")
endif()

pico_sdk_init()

add_library(mqtt
    src/mqtt.c
)

target_include_directories(mqtt
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/lwip
        ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(mqtt
    pico_stdlib
    pico_cyw43_arch_lwip_threadsafe_background
    pico_lwip_mqtt
)

add_library(wifi
    src/wifi.c
)

target_compile_definitions(wifi
    PRIVATE
        WIFI_SSID=\"${WIFI_SSID}\"
        WIFI_PASSWD=\"${WIFI_PASSWD}\"
)

target_include_directories(wifi
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${CMAKE_CURRENT_LIST_DIR}/lwip
)

target_link_libraries(wifi
    pico_stdlib
    pico_cyw43_arch_lwip_threadsafe_background
)

add_library(photoresistor
    src/photoresistor.c
)

target_include_directories(photoresistor
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(photoresistor
    hardware_adc
)

#target_sources(mqtt PRIVATE ${PICO_SDK_PATH}/lib/lwip/src/apps/mqtt/mqtt.c)

add_executable(edge
    src/main.c
)

target_link_libraries(edge
    pico_stdlib
    wifi
    mqtt
    photoresistor
)

pico_enable_stdio_usb(edge 1)
pico_enable_stdio_uart(edge 1)
pico_add_extra_outputs(edge)
