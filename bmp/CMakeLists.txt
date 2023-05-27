add_executable(bmp
	src/main.c
	src/bmp280.c
)
target_include_directories(bmp
	PUBLIC include
)

pico_add_extra_outputs(bmp)
pico_enable_stdio_usb(bmp 1)
target_link_libraries(bmp
	pico_stdlib
	hardware_i2c
)
