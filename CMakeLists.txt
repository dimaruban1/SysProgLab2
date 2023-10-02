cmake_minimum_required(VERSION 3.26)
project(SysProgLab2 C)

set(CMAKE_C_STANDARD 11)

add_executable(SysProgLab2 main.c
        automata/automata.h
        automata/automata.c)
