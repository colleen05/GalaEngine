// Project: GalaEngine
// File: Demo_Fonts.hpp
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

class Demo_Fonts : public GalaEngine::Game {
    public:
        GalaEngine::Font *font = nullptr;
        int fontSize = 20;

        GalaEngine::Colour bgColour = C_BLACK;
        GalaEngine::Colour fgColour = C_WHITE;

        // Game class overrides
        void OnLoad();
        void OnDraw();
        void OnUpdate();
        void OnUnload();

        // Constructor
        Demo_Fonts();
};