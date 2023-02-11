// Project: GalaEngine Demo
// File: Demo_Assets.hpp
// Description: Demonstrates siomple asset management via AssetManager.
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <GalaEngine/EngineInfo.hpp>
#include <GalaEngine/Game.hpp>
#include <GalaEngine/Colour.hpp>
#include <iostream>
#include <cmath>
#include <filesystem>
#include <thread>
#include <future>

class Demo_Assets : public GalaEngine::Game {
    public:
        enum class View {
            Loaded,
            Available
        } currentView = View::Loaded;

        int mouseCursor = MOUSE_CURSOR_DEFAULT;

        float scroll = 0.0f;
        float scrollLimit = 0.0f;

        bool showWholeSprite = false;
        bool showWholeTexture = false;

        int availableAssetsCount = 0;

        const GalaEngine::Colour textureCardColour  = {0xdd, 0x00, 0x22, 0xff};
        const GalaEngine::Colour spriteCardColour   = {0xdd, 0xdd, 0x22, 0xff};
        const GalaEngine::Colour tilesetCardColour  = {0x00, 0xdd, 0x22, 0xff};
        const GalaEngine::Colour soundCardColour    = {0x00, 0xaa, 0xdd, 0xff};
        const GalaEngine::Colour fontCardColour     = {0xaa, 0x22, 0xdd, 0xff};

        // Game class overrides
        void OnLoad();
        void OnDraw();
        void OnUpdate();
        void OnUnload();

        // GUI Components
        void GUI_TitleBar();
        bool GUI_Button(const std::string &text, const int x, const int y, const int width, const int height, const GalaEngine::Colour colour = {0xff, 0xff, 0xff, 0xff});
        bool GUI_TextureCard(const int x, const int y, const std::string &resName);
        bool GUI_SpriteCard(const int x, const int y, const std::string &resName);
        bool GUI_TilesetCard(const int x, const int y, const std::string &resName);
        bool GUI_SoundCard(const int x, const int y, const std::string &resName);
        bool GUI_FontCard(const int x, const int y, const std::string &resName);

        // Views
        void View_Loaded();
        void View_Available();

        // Misc.
        void LoadAllResources();

        // Constructor
        Demo_Assets();
};