// Project: GalaEngine
// File: Demo_Cameras.hpp
// Description: Demo for the camera system.
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <GalaEngine/EngineInfo.hpp>
#include <GalaEngine/Game.hpp>
#include <iostream>
#include <cmath>

class Demo_Cameras : public GalaEngine::Game {
    public:
        GalaEngine::TileLayer *lay_tiles;
        int activeCamera = 0;
        bool showCameraNumbers = true;

        // Custom functions
        void SetupRoomTiles();

        // Game class overrides
        void OnLoad();
        void OnDraw();
        void OnUpdate();
        void OnUnload();

        // Constructor
        Demo_Cameras();
};