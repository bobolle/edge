cmake_minimum_required(VERSION 3.13)

set(LIBRARY_PROJECT "${PROJECT_NAME}-lib")
set(EXECUTABLE_PROJECT "${PROJECT_NAME}")

add_library(${LIBRARY_PROJECT})

target_sources(${LIBRARY_PROJECT}
    PRIVATE
        mqtt.c
        wifi.c
        moisture.c
        photoresistor.c
        pump.c
        ultrasonic.c
)

target_include_directories(${LIBRARY_PROJECT}
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/lwip
)

target_link_libraries(${LIBRARY_PROJECT}
    pico_stdlib
    pico_cyw43_arch_lwip_threadsafe_background
    pico_lwip_mqtt
    hardware_gpio
    hardware_adc
)

target_compile_definitions(${LIBRARY_PROJECT}
    PRIVATE
        WIFI_SSID=\"${WIFI_SSID}\"
        WIFI_PASSWD=\"${WIFI_PASSWD}\"
)

add_executable(${EXECUTABLE_PROJECT} main.c)

target_link_libraries(${EXECUTABLE_PROJECT}
    ${LIBRARY_PROJECT}
)

pico_enable_stdio_usb(${EXECUTABLE_PROJECT} 1)
pico_enable_stdio_uart(${EXECUTABLE_PROJECT} 1)
pico_add_extra_outputs(${EXECUTABLE_PROJECT})
