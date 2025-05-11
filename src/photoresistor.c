#include "photoresistor.h"
#include "hardware/adc.h"

void photoresistor_init(uint8_t signal_pin)
{
    adc_init();
    adc_gpio_init(signal_pin);
}

uint16_t photoresistor_read(uint8_t signal_pin)
{
    if (signal_pin == 27)
    {
        adc_select_input(1);
        return adc_read();
    }

    return 0;
}
