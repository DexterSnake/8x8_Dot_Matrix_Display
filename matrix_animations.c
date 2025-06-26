#include <stdint.h>
#include "matrix_animations.h"
#include "shift_register.h"
#include "pico/stdlib.h"

#define LED_MATRIX_WIDTH 8
#define LED_MATRIX_HEIGHT 8

void Light_LED(struct ShiftRegister *sr_in,struct ShiftRegister *sr_out, uint8_t r, uint8_t c)
{
    if (r > LED_MATRIX_WIDTH || c > LED_MATRIX_HEIGHT || (r==4 && c==6)) {
        return; // Dead LED or out of bounds
    }
    uint8_t data = 0;
    data |= (1 << r-1);
    Shift_Out(sr_in, data);
    data |= (1 << c-1);
    Shift_Out(sr_out, ~data);
}

void Clear_LED(struct ShiftRegister *sr_in, struct ShiftRegister *sr_out)
{
    gpio_put(sr_in->clear_pin, 0);
    Shift_Out(sr_out, ~0x00); // Clear output shift register
    gpio_put(sr_in->clear_pin, 1);
}


void Running_LED(struct ShiftRegister *sr_in, struct ShiftRegister *sr_out)
{
        for (int s = 10; s < 120; s=s+10){
            for( int r = 3; r <= 5; r++) {
                for (int c = 1; c <= 2; c++) {
                    Light_LED(sr_in, sr_out, r, c);
                    sleep_ms(s);
                    Clear_LED(sr_in, sr_out);
                    sleep_ms(s);
                }
        }
        s=s+10;
        for( int r = 5; r >= 3; r--) {
                for (int c = 2; c >= 1; c--) {
                    if ((c==1 && r==3) || (c==2 && r==5)) {
                        continue;
                    }
                    Light_LED(sr_in, sr_out, r, c);
                    sleep_ms(s);
                    Clear_LED(sr_in, sr_out);
                    sleep_ms(s);
                }
        }
    }
        for (int s = 120; s>10; s=s-10) {
            for( int r = 3; r <= 5; r++) {
                for (int c = 1; c <= 2; c++) {
                    Light_LED(sr_in, sr_out, r, c);
                    sleep_ms(s);
                    Clear_LED(sr_in, sr_out);
                    sleep_ms(s);
                }
        }
        s=s-10;
        for( int r = 5; r >= 3; r--) {
                for (int c = 2; c >= 1; c--) {
                    if ((c==1 && r==3) || (c==2 && r==5)) {
                        continue;;
                    }
                    Light_LED(sr_in, sr_out, r, c);
                    sleep_ms(s);
                    Clear_LED(sr_in, sr_out);
                    sleep_ms(s);
                }
        }
        
    }
}

void picture_draw(struct ShiftRegister *sr_in, struct ShiftRegister *sr_out, uint8_t row_data[8]) //column multiplex by row
{   
    for (int r = 0; r<8 ; r++)
        {
            Shift_Out(sr_in,(1<<r));
            Shift_Out(sr_out,~(row_data[r]));
            sleep_us(500);
        }
}

void animate(struct ShiftRegister *sr_in, struct ShiftRegister *sr_out, uint8_t frames, uint8_t data[frames][8],uint8_t delay_ms,bool reverse) {
    if (reverse==0) {
        for (uint8_t x = 0; x < frames; x++) {
            uint64_t start = time_us_64();
            while (time_us_64() - start < delay_ms*1000) {  // in microseconds
                picture_draw(sr_in, sr_out, data[x]);
            }
        }
    }
    else {
        for (int8_t x = frames-1; x >= 0; x--) {
            uint64_t start = time_us_64();
            while (time_us_64() - start < delay_ms*1000) {  // in microseconds
                picture_draw(sr_in, sr_out, data[x]);
            }
        }
    }
    
}
