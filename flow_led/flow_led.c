#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

int ledPins[] = {16, 17, 18, 19, 20, 21, 22, 26, 27, 28};

int length = sizeof(ledPins) / sizeof(ledPins[0]);

int main()
{
    stdio_init_all();
    for (int i = 0; i < length; i++)
    {
        gpio_init(ledPins[i]);
        gpio_set_dir(ledPins[i], GPIO_OUT);
    }
    while(true){
        for (int i = 0; i < length; i++)
        {
            gpio_put(ledPins[i], 1);
            sleep_ms(500);
            gpio_put(ledPins[i], 0);
        }
        for (int i = length - 1; i > -1; i--)
        {
            gpio_put(ledPins[i], 1);
            sleep_ms(500);
            gpio_put(ledPins[i], 0);
        }
    }
}