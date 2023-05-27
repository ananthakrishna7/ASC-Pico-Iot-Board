

# Compilation Instructions
1. Install CMake, and the GCC ARM compiler. On Ubuntu, the command is a follows:
```bash
sudo apt-get update
sudo apt-get install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi build-essential libstdc++-arm-none-eabi-newlib
```

2. Clone the repository 
```bash
git clone https://github.com/aadit-n3rdy/pico-sensors.git
cd pico-sensor
git submodule update --init --recursive
```

3. Set the env `PICO_SDK_PATH` environment variable
```bash
export PICO_SDK_PATH=`pwd`/pico-sdk
```

4. Create a build directory, and build the examples
```bash
mkdir build
cd build
cmake ..
```

5. Open any of the folders in the build directory, and build the .uf2 file. The following is
a demonstration for the `blink` example
```bash
cd blink
make -j4
```

6. Load the .uf2 file and execute it on the Raspberry Pi Pico
