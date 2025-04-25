#include "pico/stdlib.h"
#include "wifi.h"
#include "mqtt.h"
#include "photoresistor.h"
#include "moisture.h"
#include "pump.h"

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
    pump_init(15);

    while (1)
    {
        uint16_t photoresistor_value = photoresistor_read(27);
        printf("photoresistor value: %u\n", photoresistor_value);
        
        uint16_t moisture_value = moisture_read(26, 16);
        printf("moisture value: %u\n", moisture_value);

        if (moisture_value < 3000)
        {
            pump_toggle(15, 1);
        }
        else
        {
            pump_toggle(15, 0);
        }

        sleep_ms(1000);
    }

    return 0;
}
