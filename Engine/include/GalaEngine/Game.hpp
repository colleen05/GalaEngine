// Project: GalaEngine
// File: Game.hpp
// Description: Game class
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <GalaEngine/Window.hpp>
#include <GalaEngine/Surface.hpp>
#include <GalaEngine/Scene.hpp>
#include <iostream>
#include <array>

namespace GalaEngine {
    struct GameInfo {
        std::string title;          // Title that will be displayed in the window.
        std::string description;    // Description of the game.
        std::string author;         // Author(s) of the game.

        int defaultWidth;   // Default width for game window.
        int defaultHeight;  // Default height for game window.

        AssetPathLayout assetPaths; // Path layout for assets.
    };

    class Game {
        protected:
            GameInfo _info;
            bool _shouldEnd = false;
            std::array<bool, KEY_KP_EQUAL> _keyStates;

        public:
            GalaEngine::Window       *window;   // Game window
            GalaEngine::Scene        *scene;    // Scene
            GalaEngine::AssetManager *assets;   // AssetManager
            GalaEngine::InputManager *input;    // InputManager

            virtual void OnLoad();
            virtual void OnUpdate();
            virtual void OnDraw();
            virtual void OnUnload();

            void Start();
            void End();
            
            Game(GameInfo info);
            Game();
    };
}