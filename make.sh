#!/bin/sh -ex

mkdir -p build

clang-format -i max7219.cpp
clang-format -i max7219.h
clang-format -i main.cpp
clang-format -i animation.h
clang-format -i animationFade.h
clang-format -i animationFade.cpp
clang-format -i animationNoise.h
clang-format -i animationNoise.cpp
clang-format -i animationBars.h
clang-format -i animationBars.cpp
clang-format -i animationFace.h
clang-format -i animationFace.cpp
clang-format -i uart.h
clang-format -i uart.c

./c-compile build/uart.o uart.c
./cxx-compile build/max7219.o max7219.cpp
./cxx-compile build/animationFade.o animationFade.cpp
./cxx-compile build/animationBars.o animationBars.cpp
./cxx-compile build/animationNoise.o animationNoise.cpp
./cxx-compile build/animationFace.o animationFace.cpp
./cxx-compile build/main.o main.cpp

./cxx-link \
build/main \
build/main.o \
build/uart.o \
build/animationFade.o \
build/animationFace.o \
build/animationNoise.o \
build/animationBars.o \
build/max7219.o

./hex build/main.hex build/main

