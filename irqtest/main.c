#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h" // Import pwm controll
#include "hardware/irq.h" // Import irq controll


const uint led_pin = PICO_DEFAULT_LED_PIN;

const uint slice_num = 4; // ch 4.5.2. in RP2040 Datasheet

const uint button_pin = 14;

bool increasing = true;

void my_pwm_irq(){
    static uint16_t level = 0;
    //static bool increasing = true;

    pwm_clear_irq(slice_num); //clear the IRQ flag for PWM WRAP

    if (increasing){
        level++;
        if(level >= 255)
            increasing = false;
    }
    else{
        level--;
        if(level <= 2)
            increasing = true;
    }
    
    pwm_set_gpio_level(led_pin, level * level); // squaring the value makes it more linear
}


void my_button_irq(){
    static absolute_time_t current_time;
    static absolute_time_t time_delay;
    current_time = get_absolute_time();

    gpio_acknowledge_irq(button_pin, GPIO_IRQ_EDGE_RISE);

    if (absolute_time_diff_us(current_time, time_delay) <= 0 || is_nil_time(current_time)){
        time_delay = delayed_by_ms(current_time, 5000);
        increasing = !increasing;
    }
}


int main() {

    pwm_clear_irq(slice_num); //paranoia clear of irq
    pwm_set_irq_enabled(slice_num, true); //enable the irq flagging on pwm wrap
    // The irq will get flagged every time the pwm loops around

    irq_set_exclusive_handler(PWM_IRQ_WRAP, my_pwm_irq); //declare my_pwm_irq as function called
    irq_set_enabled(PWM_IRQ_WRAP, true); //enable the irq handler for this (actually calls the mask)

    gpio_set_function(button_pin, GPIO_FUNC_SIO); //SIO = Software (defined) Input Output
    gpio_pull_up(button_pin);
    gpio_set_dir(button_pin, false);
    gpio_set_irq_enabled_with_callback(button_pin, GPIO_IRQ_EDGE_FALL, true, &my_button_irq);


    // ------- PWM Below --------

    gpio_set_function(led_pin, GPIO_FUNC_PWM); //set led pin to pwm output

    pwm_config conf = pwm_get_default_config(); //create pwm config instance 
    pwm_config_set_clkdiv(&conf, 5); //set the clock divider. Not divided by the value though??
    pwm_init(slice_num, &conf, true); //start the pwm

    while(true){
        continue;
    }

}