// Project: GalaEngine
// File: Demo_Scene.hpp
// Description: Scene testing
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <GalaEngine/EngineInfo.hpp>
#include <GalaEngine/Game.hpp>
#include <GalaEngine/Colour.hpp>
#include <GalaEngine/BackgroundLayer.hpp>
#include <iostream>
#include <cmath>

class Demo_Scene : public GalaEngine::Game {
    public:
        Texture tex_background;
        GalaEngine::BackgroundLayer *lay_background;

        // Game class overrides
        void OnLoad();
        void OnDraw();
        void OnUpdate();
        void OnUnload();

        // Constructor
        Demo_Scene();
};