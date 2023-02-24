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

find ./Engine/src/ -maxdepth 1 -type f | while read file; do
    fname=$(basename $file)
    cmd="clang++ -c -o Engine/tmp/$fname.o $file -IEngine/include -std=c++17"
    echo $cmd
    ${cmd}
done

echo "Building static libraries..."
rm Engine/bin/linux64/libGalaEngine.a
ar rcs Engine/bin/linux64/libGalaEngine.a Engine/tmp/*.o

# Cleaning up
echo "Removing temporary directories..."
rm -r Engine/tmp