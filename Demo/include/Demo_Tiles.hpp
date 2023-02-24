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
            Foreground
        };

        EditLayer targetLayer   = EditLayer::Background;
        
        bool viewBackgroundTiles = true;
        bool viewForegroundTiles = true;

        GalaEngine::TileLayer *lay_bgTiles  = nullptr;
        GalaEngine::TileLayer *lay_fgTiles  = nullptr;
        GalaEngine::Layer     *lay_flagView = nullptr;

        GalaEngine::Sprite *spr_layerViews = {0};

        int selectionX = 0;
        int selectionY = 0;
        bool selectionInBounds = false;
        uint16_t brushTile = 0;

        bool viewFlags = false;
        bool viewGrid = true;

        // Game class overrides
        void OnLoad();
        void OnDraw();
        void OnUpdate();
        void OnUnload();

        // Editor
        bool GUI_Button(const std::string &text, const int x, const int y, const int w, const int h, const bool highlighted = false);

        void GUI_Picker();
        void GUI_BrushPreview(const int x, const int y);
        void GUI_LayerToggle(const int x, const int y);
        void GUI_FlagsToggle(const int x, const int y);
        void GUI_GridToggle(const int x, const int y);
        void GUI_ViewSelector(const int x, const int y);
        
        void DrawTileGrid();
        void DrawTileFlags();

        // Constructor
        Demo_Tiles();
};