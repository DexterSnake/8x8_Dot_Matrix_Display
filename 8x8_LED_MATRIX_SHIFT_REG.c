#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "matrix_animations.h"
#include "shift_register.h"
#include "animations.h"

int main()
{
    struct ShiftRegister Input_SR;
    init_ShiftRegister(&Input_SR, 17, 15, 13, 0xFF);
    struct ShiftRegister Output_SR;
    init_ShiftRegister(&Output_SR, 16, 14, 12, 0xFF);

    while (true) {
        //Running_LED(&Input_SR, &Output_SR);
        //picture_draw(&Input_SR,&Output_SR, (uint8_t[]){0x00,0x66,0x99,0x81,0x81,0x42,0x24,0x18}); 

        // https://gurgleapps.com/tools/matrix
        // uint8_t animation_data[2][8] = { // Heart beating
        //     {0x00, 0x66, 0x99, 0x81, 0x81, 0x42, 0x24, 0x18}, // Frame 0
        //     {0x66, 0xFF, 0x99, 0x81, 0x81, 0xC3, 0x66, 0x3C}  // Frame 1
        // };
        uint8_t delay_between_frames_ms = 25; //25ms is 40Hz
        animate(&Input_SR,&Output_SR,(sizeof(animation_fill_from_center)/sizeof(animation_fill_from_center[0])),animation_fill_from_center,delay_between_frames_ms,0);
        sleep_ms(500);
        animate(&Input_SR,&Output_SR,(sizeof(animation_fill_from_center)/sizeof(animation_fill_from_center[0])),animation_fill_from_center,delay_between_frames_ms,1);
    }
}