#include <stdint.h>

#pragma once

void moisture_init(uint8_t sensor_pin, uint8_t power_pin);
uint16_t moisture_read(uint8_t sensor_pin, uint8_t power_pin);
