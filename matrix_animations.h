#ifndef MATRIX_ANIMATIONS_H
#define MATRIX_ANIMATIONS_H

#include <stdbool.h>

struct ShiftRegister;
void Light_LED(struct ShiftRegister *sr_in, struct ShiftRegister *sr_out, uint8_t r, uint8_t c);
void Clear_LED(struct ShiftRegister *sr_in, struct ShiftRegister *sr_out);
void Running_LED(struct ShiftRegister *sr_in, struct ShiftRegister *sr_out);
void picture_draw(struct ShiftRegister *sr_in, struct ShiftRegister *sr_out, uint8_t row_data[8]);
void animate(struct ShiftRegister *sr_in, struct ShiftRegister *sr_out, uint8_t frames, uint8_t data[frames][8],uint8_t delay_ms, bool reverse);   

#endif