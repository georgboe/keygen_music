# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH $ENV{PICO_SDK_PATH})

set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(keygen_music C CXX ASM)
set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wcast-align=strict")
set (CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wcast-align=strict")

set(PICO_CXX_ENABLE_EXCEPTIONS 1)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(keygen_music keygen_music.cpp 
m4p/it2drivers/sb16_m.c
m4p/it2drivers/sb16.c
m4p/it2drivers/zerovol.c
m4p/loaders/mmcmp/mmcmp.c
m4p/loaders/it.c
m4p/loaders/s3m.c
m4p/m4p.c
m4p/ft_tables.c
m4p/it_d_rm.c
m4p/it_m_eff.c
m4p/it_music.c
m4p/it_tables.c
m4p/pmp_main.c
m4p/pmp_mix.c
m4p/pmplay.c
m4p/snd_masm.c
pico_audio_i2s/audio_i2s.c
pico_audio_i2s/audio.cpp
)

pico_generate_pio_header(keygen_music ${CMAKE_CURRENT_LIST_DIR}/pico_audio_i2s/audio_i2s.pio)

pico_set_program_name(keygen_music "keygen_music")
pico_set_program_version(keygen_music "0.1")

pico_enable_stdio_uart(keygen_music 0)
pico_enable_stdio_usb(keygen_music 1)

# Add the standard library to the build
target_link_libraries(keygen_music
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(keygen_music PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/m4p
  ${CMAKE_CURRENT_LIST_DIR}/pico_audio_i2s
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)

# Add any user requested libraries
target_link_libraries(keygen_music 
        pico_stdlib
        pico_rand
        hardware_pio
        hardware_dma
        )

pico_add_extra_outputs(keygen_music)
