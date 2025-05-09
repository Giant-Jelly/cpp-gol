#!/bin/bash
mkdir -p build/mac
echo "Building for mac..."
g++ -std=c++17 main.cpp -g -ggdb -w -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2 -lSDL2_image -lSDL2_ttf -o build/mac/main
echo "Running..."
./build/mac/main