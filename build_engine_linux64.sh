#!/bin/bash

# Because of issues with static linking...
echo "THIS SCRIPT IS PRETTY USELESS FOR NOW :-)"
echo "PLEASE WAIT UNTIL STATIC LINKING WORKS PROPERLY."
echo "ANYWAY..."

# Introduction
echo "Building GalaEngine [linux64]..."

# Setting up directories
echo "Creating directories..."
mkdir -p Engine/bin/linux64
mkdir -p Engine/tmp

# Compiling
echo "Compiling object files..."
clang++ -c -o Engine/tmp/EngineInfo.o Engine/src/EngineInfo.cpp -IEngine/include -std=c++17
clang++ -c -o Engine/tmp/Window.o Engine/src/Window.cpp -IEngine/include -std=c++17

echo "Building static libraries..."
rm Engine/bin/linux64/libGalaEngine.a
ar rcs Engine/bin/linux64/libGalaEngine.a Engine/tmp/EngineInfo.o Engine/tmp/Window.o

# Cleaning up
echo "Removing temporary directories..."
rm -r Engine/tmp