#include "pico/stdlib.h"
#include "wifi.h"
#include "mqtt.h"
#include "photoresistor.h"
#include "moisture.h"
#include "pump.h"

int main(void)
{
    stdio_init_all();

    // Wifi connection init
    if (wifi_connect())
    {
        printf("could not connect to wifi\n");
    }
    else
    {
        printf("connected to wifi\n");
    }

    // MQTT connection init
    mqtt_connect();
    err_t err = mqtt_sub("edge/+/set/moisture");
    if (err != ERR_OK)
    {
        printf("could not sub to topic\n");
    }

    err = mqtt_sub("edge/+/get/moisture");
    if (err != ERR_OK)
    {
        printf("could not sub to topic\n");
    }

    err = mqtt_sub("edge/+/get/photoresistor");
    if (err != ERR_OK)
    {
        printf("could not sub to topic\n");
    }

    err = mqtt_sub("edge/+/set/photoresistor");
    if (err != ERR_OK)
    {
        printf("could not sub to topic\n");
    }

    // Photoresistor init
    photoresistor_init(27);

    // Moisture sensor init
    moisture_init(26, 16);

    // Pump init
    pump_init(15);

    // Pump status LED init
    gpio_init(5);
    gpio_set_dir(5, GPIO_OUT);
    gpio_put(5, 0);

    while (1)
    {
        if (moisture_value > moisture_threshold)
        {
            printf("pump toggled on\n");
            pump_toggle(15, 1);
            gpio_put(5, 1);
            sleep_ms(3000);

            printf("pump toggled off\n");
            pump_toggle(15, 0);
            gpio_put(5, 0);
        }

        sleep_ms(5000);
    }

    return 0;
}
