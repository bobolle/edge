#include <stdio.h>
#include "pico/cyw43_arch.h"

int wifi_connect()
{
    if (cyw43_arch_init())
    {
        return 1;
    }

    cyw43_arch_enable_sta_mode();

    if (cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWD, CYW43_AUTH_WPA2_AES_PSK, 10000))
    {
        return 1;
    }

    return 0;
}
