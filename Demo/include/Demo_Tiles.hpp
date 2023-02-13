// Project: GalaEngine Demo
// File: Demo_Tiles.hpp
// Description: Tileset & tilemap demo class.
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <GalaEngine/EngineInfo.hpp>
#include <GalaEngine/Game.hpp>
#include <GalaEngine/Colour.hpp>
#include <iostream>
#include <cmath>

class Demo_Tiles : public GalaEngine::Game {
    public:
        const int tileSize = 64;
        const int tilemapWidth = 9;
        const int tilemapHeight = 9;
        const int sidebarWidth = 448;

        enum class EditMode {
            PlaceTiles,
            PickTiles
        };
        
        EditMode editMode = EditMode::PlaceTiles;

        enum class EditLayer {
            Background,
            Foreground,
            Both
        };

        EditLayer targetLayer   = EditLayer::Background;
        EditLayer viewLayer     = EditLayer::Both;

        GalaEngine::TileLayer *lay_bgTiles = nullptr;
        GalaEngine::TileLayer *lay_fgTiles = nullptr;

        int selectionX = 0;
        int selectionY = 0;
        uint16_t brushTile = 0;

        bool viewFlags = false;

        // Game class overrides
        void OnLoad();
        void OnDraw();
        void OnUpdate();
        void OnUnload();

        // Editor
        void DoPicker();
        void DrawTileGrid();

        // Constructor
        Demo_Tiles();
};