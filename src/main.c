#include "pico/stdlib.h"
#include "wifi.h"
#include "mqtt.h"

int main(void)
{
    stdio_init_all();

    if (wifi_connect())
    {
        printf("could not connect to wifi\n");
    }

    mqtt_init();
    mqtt_connect();

    while (1)
    {
        publish_read("light", 30);
        sleep_ms(5000);
    }

    return 0;
}
