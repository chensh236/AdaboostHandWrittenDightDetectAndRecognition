#! /usr/bin/bash

# remove the old parsed file if exist
if [ -f main ]; then
    rm main
fi

if [ -f CMakeCache.txt ]; then
    rm CMakeCache.txt
fi

if [ -f Makefile ]; then
    rm Makefile
fi

if [ -f cmake_install.cmake ]; then
    rm cmake_install.cmake
fi

if [ -d "CMakeFiles" ]; then
	rm -r CMakeFiles
fi

cmake .
make
./main `ls ../image`