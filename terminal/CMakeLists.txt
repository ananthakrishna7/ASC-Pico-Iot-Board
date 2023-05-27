add_executable(terminal
	src/main.c
)
pico_enable_stdio_usb(terminal 1)
pico_add_extra_outputs(terminal)
target_link_libraries(terminal
	pico_stdlib
)
