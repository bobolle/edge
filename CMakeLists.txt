cmake_minimum_required(VERSION 3.13)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
project(edge C CXX ASM)

set(PICO_BOARD pico_w)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(edge
    src/main.c
    src/wifi.c
    src/mqtt.c
)

target_include_directories(edge PRIVATE ${CMAKE_CURRENT_LIST_DIR}/lwip)
target_include_directories(edge PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${PICO_SDK_PATH}/lib/lwip/src/apps/mqtt/mqtt.c)

target_link_libraries(edge
    pico_stdlib
    pico_cyw43_arch_lwip_threadsafe_background
)

pico_enable_stdio_usb(edge 1)
pico_enable_stdio_uart(edge 1)
pico_add_extra_outputs(edge)
