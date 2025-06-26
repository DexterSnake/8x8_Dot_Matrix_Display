#ifndef SHIFT_REGISTER_H
#define SHIFT_REGISTER_H

#include <stdint.h>

struct ShiftRegister {
    uint8_t data_pin;
    uint8_t clock_pin;
    uint8_t clear_pin;
    uint8_t latch_pin;
};

void init_ShiftRegister(struct ShiftRegister *sr, uint8_t data_pin, uint8_t clock_pin, uint8_t clear_pin, uint8_t latch_pin);
void Shift_Out(struct ShiftRegister *sr, uint8_t data);


#endif
