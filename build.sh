#!/bin/bash
mkdir build
cd build
cmake ..
make
./SnakeGame
cd ..
rm -rf build
