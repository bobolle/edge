#include "moisture.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

void moisture_init(uint8_t sensor_pin, uint8_t power_pin)
{
    adc_init();
    adc_gpio_init(sensor_pin);

    gpio_init(sensor_pin);
    gpio_init(power_pin);

    gpio_set_dir(sensor_pin, GPIO_IN);
    gpio_set_dir(power_pin, GPIO_OUT);

    gpio_put(power_pin, 0);
}

uint16_t moisture_read(uint8_t sensor_pin, uint8_t power_pin)
{
    if (sensor_pin == 26)
    {
        adc_select_input(0);

        gpio_put(power_pin, 1);
        sleep_ms(100);

        uint16_t value = adc_read();

        gpio_put(power_pin, 0);

        return value;
    }

    return 0;
}
