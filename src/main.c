#include <stdio.h>
#include "pico/stdlib.h"
#include "wifi.h"
#include "mqtt.h"

int main(void)
{
    stdio_init_all();

    if (wifi_connect()) {
        printf("could not connect to wifi\n");
    }

    cyw43_arch_deinit();

    return 0;
}
