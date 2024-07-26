#include "pico/stdlib.h"
#include <stdio.h>
#include "pico/time.h"
#include "hardware/pwm.h"
#include "hardware/irq.h"

#define DELAY 500
const uint LED_PIN = 15;

//More complicated example: https://github.com/jondurrant/RPIPicoPWMExamples

void on_pwm_wrap() {
    // As I understand
    // when the counter reaches the wrap (TOP), this interrupt handler gets called
    // and changes the duty cycle by increasing/decreasing the level up to (max 16 bits)
    // with squaring the number that is 8 bits
    //
    // The higher the duty cycle (level) the brighter the LED
    // Also, the duty cycle changes slightly every time it wraps becose the
    // fade variable changes every cycle
    static int fade = 0;
    static bool going_up = true;
    // Clear the interrupt flag that brought us here
    pwm_clear_irq(pwm_gpio_to_slice_num(LED_PIN));

    if (going_up) {
        ++fade;
        if (fade > 255) {
            fade = 255;
            going_up = false;
        }
    } else {
        --fade;
        if (fade < 0) {
            fade = 0;
            going_up = true;
        }
    }
    // Square the fade value to make the LED's brightness appear more linear
    // Note this range matches with the wrap value
    pwm_set_gpio_level(LED_PIN, fade * fade);
}

int main(){
    gpio_set_function(LED_PIN, GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(LED_PIN);

    pwm_clear_irq(slice_num);
    pwm_set_irq_enabled(slice_num, true);
    irq_set_exclusive_handler(PWM_IRQ_WRAP, on_pwm_wrap);
    irq_set_enabled(PWM_IRQ_WRAP, true);

    // I guess the default wrap value is max 16 bit value

    //Does frequency matter other than controlling the fading time??

    pwm_config config = pwm_get_default_config();
    // Set divider, reduces counter clock to sysclock/this value
    // The higher the divider the slower the pulsating - the frequency decreases and the time to comple a cycle is slower (?but the duty cycle remains the same?)
    pwm_config_set_clkdiv(&config, 8.f);
    // Load the configuration into our PWM slice, and set it running.
    pwm_init(slice_num, &config, true);

    // Everything after this point happens in the PWM interrupt handler, so we
    // can twiddle our thumbs
    while (1)
        tight_loop_contents();
}