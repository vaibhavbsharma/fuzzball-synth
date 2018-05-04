cmake_minimum_required(VERSION 3.10)
project(rc4enc_conc)

set(CMAKE_CXX_STANDARD 11)

include_directories(. /export/scratch/vaibhav/mbedtls-install/include)

add_executable(rc4enc_conc
        adaptor_types.h
        calc_num_adaptors.h
        functions.h
        generate_adaptors.h
        generate_struct_adaptors.h
        PinMonitor.cpp
        PinMonitor.h
        SignalHandlers.h
        struct_adaptor.c
        synth-conc-simple-struct.pl
        two-funcs-conc.c
        constants.h)
