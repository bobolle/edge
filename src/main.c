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

    // MQTT connection init
    mqtt_init();
    mqtt_connect();

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
        // send photoresistor data to hub
        uint16_t photoresistor_value = photoresistor_read(27);
        publish_sensor_read("light", photoresistor_value);
        printf("photoresistor value: %u\n", photoresistor_value);
        
        // send moisture data to hub
        uint16_t moisture_value = moisture_read(26, 16);
        publish_sensor_read("moisture", moisture_value);
        printf("moisture value: %u\n", moisture_value);

        if (moisture_value > 3000)
        {
            printf("pump toggled on\n");
            pump_toggle(15, 1);
            gpio_put(5, 1);
            sleep_ms(3000);

            printf("pump toggled off\n");
            pump_toggle(15, 0);
            gpio_put(5, 0);
        }

        sleep_ms(1000);
    }

    return 0;
}
