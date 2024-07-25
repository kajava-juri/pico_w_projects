
add_executable(blink_led
        blink_led.c
)

target_link_libraries(blink_led
        pico_stdlib
        pico_cyw43_arch_none
)

pico_add_extra_outputs(blink_led)

