#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/gpio.h"
#include "ultrasonic.h"
#include <stdio.h>

static ultrasonic_pins_t ultrasonic_pins;
volatile bool echo_received;
volatile absolute_time_t start_time;
volatile absolute_time_t end_time;

int ultrasonic_init(uint8_t trigger_pin, uint8_t echo_pin)
{
    ultrasonic_pins.trigger_pin = trigger_pin;
    ultrasonic_pins.echo_pin = echo_pin;

    gpio_init(trigger_pin);
    gpio_init(echo_pin);

    gpio_set_dir(trigger_pin, GPIO_OUT);
    gpio_set_dir(echo_pin, GPIO_IN);

    gpio_put(trigger_pin, 0);

    gpio_set_irq_enabled_with_callback(echo_pin, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &echo_callback);
}

void echo_callback(uint gpio, uint32_t events)
{
    if (gpio_get(ultrasonic_pins.echo_pin))
    {
        // if echo_pin is true, there's has been a rising edge.
        // when a pulse is being send the echo receiver turns on
        start_time = get_absolute_time();
    }
    else
    {
        // if echo_pin is false, there's has been a falling edge
        end_time = get_absolute_time();
        echo_received = true;
    }
}

int ultrasonic_get_pulse_duration(uint64_t timeout)
{
    echo_received = false;

    gpio_put(ultrasonic_pins.trigger_pin, 1);
    sleep_us(10);
    gpio_put(ultrasonic_pins.trigger_pin, 0);

    // store start of wait
    absolute_time_t start_wait = get_absolute_time();

    while (!echo_received)
    {
        if (absolute_time_diff_us(start_wait, get_absolute_time()) > timeout)
        {
            return -1;
        }
        tight_loop_contents();
    }

    return absolute_time_diff_us(start_time, end_time);
}
