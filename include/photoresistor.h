#ifndef PHOTORESISTOR_H
#define PHOTORESISTOR_H

void photoresistor_init(uint8_t signal_pin);
uint16_t photoresistor_read(uint8_t signal_pin);

#endif
