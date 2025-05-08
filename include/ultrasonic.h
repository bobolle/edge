#pragma once

#include "pico/stdlib.h"
#include "hardware/timer.h"

typedef struct {
    uint8_t trigger_pin;
    uint8_t echo_pin;
} ultrasonic_pins_t;

int ultrasonic_init(uint8_t trigger_pin, uint8_t echo_pin);
int ultrasonic_get_pulse_duration(uint64_t timeout);
void echo_callback(uint gpio, uint32_t events);
