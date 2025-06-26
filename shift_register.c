#include "shift_register.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"


#define delay_time 0 // Delay time in microseconds


void init_ShiftRegister(struct ShiftRegister *sr, uint8_t data_pin, uint8_t clock_pin, uint8_t clear_pin ,uint8_t latch_pin)
{
    sr->data_pin = data_pin;
    sr->clock_pin = clock_pin;
    sr->clear_pin = clear_pin;
    sr->latch_pin = latch_pin;

    gpio_init(sr->data_pin);
    gpio_set_dir(sr->data_pin, GPIO_OUT);

    gpio_init(sr->clock_pin);
    gpio_set_dir(sr->clock_pin, GPIO_OUT);
    
    if (clear_pin != 0xFF) { // 0xFF means "not given"
        gpio_init(sr->clear_pin);
        gpio_set_dir(sr->clear_pin, GPIO_OUT);
        gpio_put(sr->clear_pin, 1); // Set clear pin high initially
    }
    if (latch_pin != 0xFF) { // 0xFF means "not given"
        gpio_init(sr->latch_pin);
        gpio_set_dir(sr->latch_pin, GPIO_OUT);
    }
}

void Shift_Out(struct ShiftRegister *sr, uint8_t data)
{
    for (int i = 0; i < 8; i++) {
        gpio_put(sr->data_pin, (data & (1 << (7 - i))) ? 1 : 0); // MSB first
        gpio_put(sr->clock_pin, 1);
        sleep_us(0);  // This is necessary for some reason, won't work without.
        gpio_put(sr->clock_pin, 0);
        if (sr->latch_pin != 0xFF) {
            gpio_put(sr->latch_pin, 1);
            sleep_us(delay_time);
            gpio_put(sr->latch_pin, 0);
        }
        
    }
}

