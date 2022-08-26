#!/bin/bash

# Introduction
echo "Building GalaEngine DEMO [linux64]..."

# Setting up directories
echo "Creating directories..."
mkdir -p Demo/bin/linux64

echo "Compiling executable..."
clang++ -o Demo/bin/linux64/Demo Demo/src/*.cpp -IEngine/include -IDemo/include -LEngine/bin/linux64 -lGalaEngine -std=c++17