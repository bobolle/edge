#include <stdint.h>

#pragma once

void photoresistor_init(uint8_t signal_pin);
uint16_t photoresistor_read(uint8_t signal_pin);
