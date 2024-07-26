
add_executable(fade_led
        fade_led.c
)

target_link_libraries(fade_led
        pico_stdlib
        hardware_pwm
)

pico_add_extra_outputs(fade_led)

