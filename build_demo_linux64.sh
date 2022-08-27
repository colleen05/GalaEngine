
#!/bin/bash

# Introduction
echo "Building GalaEngine DEMO [linux64]..."

# Setting up directories
echo "Creating directories..."
mkdir -p Demo/bin/linux64

# Compiling
echo "Compiling executable..."

clang++ -o Demo/bin/linux64/Demo Engine/src/*.cpp Demo/src/*.cpp -IEngine/include -IDemo/include -LEngine/lib/linux64 -lraylib -std=c++17

# Static linking approach (broken):
# clang++ -o Demo/bin/linux64/Demo Demo/src/*.cpp -IEngine/include -IDemo/include -LEngine/lib/linux64 -LEngine/bin/linux64 -lraylib -lGalaEngine -std=c++17