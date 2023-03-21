// Project: GalaEngine
// File: Demo_NSlices.hpp
// Description: Demo for demonstrating 9-slices.
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <GalaEngine/EngineInfo.hpp>
#include <GalaEngine/Game.hpp>
#include <GalaEngine/Colour.hpp>
#include <GalaEngine/BackgroundLayer.hpp>
#include <GalaEngine/EntityLayer.hpp>
#include <GalaEngine/TileLayer.hpp>
#include <GalaEngine/Tileset.hpp>
#include <iostream>
#include <cmath>

class Demo_NSlices : public GalaEngine::Game {
    public:
        bool showPreview = false;

        Rectangle slicePreview = {32.0f, 32.0f, 96.0f, 96.0f};
        Rectangle sliceWindow = {32.0f, 32.0f, 96.0f, 96.0f};

        std::string currentNSlice = "numbers";

        // Game class overrides
        void OnLoad();
        void OnDraw();
        void OnUpdate();
        void OnUnload();

        // Constructor
        Demo_NSlices();
};