#include "pico/stdlib.h"
#include "wifi.h"
#include "mqtt.h"
#include "photoresistor.h"
#include "moisture.h"

int main(void)
{
    stdio_init_all();

    if (wifi_connect())
    {
        printf("could not connect to wifi\n");
    }

    mqtt_init();
    mqtt_connect();
    photoresistor_init(27);
    moisture_init(26, 16);

    while (1)
    {
        uint16_t photoresistor_value = photoresistor_read(27);
        printf("photoresistor value: %u\n", photoresistor_value);
        publish_read("light", photoresistor_value);
        
        uint16_t moisture_value = moisture_read(26, 16);
        printf("moisture value: %u\n", moisture_value);
        publish_read("moisture", moisture_value);

        sleep_ms(10000);
    }

    return 0;
}
