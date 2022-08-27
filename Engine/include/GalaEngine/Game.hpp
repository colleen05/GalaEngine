// Project: GalaEngine
// File: Game.hpp
// Description: Game class
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#include <GalaEngine/Window.hpp>

namespace GalaEngine {
    struct GameInfo {
        std::string title;          // Title that will be displayed in the window.
        std::string description;    // Description of the game.
        std::string author;         // Author(s) of the game.

        int defaultWidth;   // Default width for game window.
        int defaultHeight;  // Default height for game window.

        std::string resourcePath;   // Path in which the game class will look for resources.
    };

    class Game {
        protected:
            GameInfo _info;
            bool _shouldEnd = false;

        public:
            GalaEngine::Window *window;

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