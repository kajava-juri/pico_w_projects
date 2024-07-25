
add_executable(flow_led
        flow_led.c
)

target_link_libraries(flow_led
        pico_stdlib
        pico_cyw43_arch_none
)

pico_add_extra_outputs(flow_led)

