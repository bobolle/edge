#include "hardware/gpio.h"

void pump_init(uint8_t pump_pin)
{
    gpio_init(pump_pin);
    gpio_set_dir(pump_pin, GPIO_OUT);
    gpio_put(pump_pin, 0);
}

void pump_toggle(uint8_t pump_pin, uint8_t status)
{
    gpio_put(pump_pin, status);
}
