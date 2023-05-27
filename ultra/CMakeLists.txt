add_executable(ultra
	src/main.c
)
pico_add_extra_outputs(ultra)
pico_enable_stdio_usb(ultra 1)
target_link_libraries(ultra
	pico_stdlib
	pico_multicore
)
