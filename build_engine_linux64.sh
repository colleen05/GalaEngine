#!/bin/bash

# Introduction
echo "Building GalaEngine [linux64]..."

# Setting up directories
echo "Creating directories..."
mkdir -p Engine/bin/linux64
mkdir -p Engine/tmp

echo "Compiling object files..."
clang++ -c -o Engine/tmp/GalaEngine.o Engine/src/*.cpp -IEngine/include -std=c++17

echo "Building static libraries..."
ar rcs Engine/bin/linux64/libGalaEngine.a Engine/tmp/GalaEngine.o

echo "Removing temporary directories..."
rm -r Engine/tmp