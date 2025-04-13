add_library(wifi wifi.c)
add_library(mqtt mqtt.c)
target_link_libraries(wifi pico_stdlib pico_cyw43_arch_lwip_threadsafe_background)
target_link_libraries(mqtt pico_stdlib)
