cmake_minimum_required(VERSION 3.15)
project(data_program_2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(data_program_2
        addfield.c
        addfield.h
        addrecord.c
        addrecord.h
        deletefield.c
        deletefield.h
        deleterecord.c
        deleterecord.h
        editrecord.c
        editrecord.h
        fileio.c
        fileio.h
        main.c
        print.c
        print.h
        structures.h)
