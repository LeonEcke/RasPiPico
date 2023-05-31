#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h" // Import pwm controll
#include "hardware/irq.h" // Import irq controll



int main() {

    // ------- PWM Below --------

    const uint loopover = 10000;

    const uint led_pin = PICO_DEFAULT_LED_PIN;

    gpio_set_function(led_pin, GPIO_FUNC_PWM);

    const uint slice_num = pwm_gpio_to_slice_num(led_pin);


    pwm_set_chan_level(slice_num, PWM_CHAN_B, 0);
    pwm_set_enabled(slice_num, true);

    bool increase_light = true;
    uint current_level = 1;

    while(1){
        if (increase_light){
            if (++current_level == loopover-1)
                increase_light = false;
        }
        else{
            if (--current_level == 0)
                increase_light = true;
        }
        pwm_set_chan_level(slice_num, PWM_CHAN_B, current_level);
        sleep_us(100);
    }

}


void pwm_irq(){
    printf("wrap hit\r\n");
}