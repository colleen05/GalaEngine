// Project: GalaEngine
// File: Window.hpp
// Description: Window creation and management class.
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <raylib.h>
#include <string>

namespace GalaEngine {
    class Window {
        private:
            std::string _title;
            int _width, _height;
            int _targetFPS;

        public:
            // Initialisation & destruction
            void Init();
            void Exit();

            // Status getters
            bool ShouldClose();

            // Constructors
            Window(std::string title, int width, int height, int targetFPS = 60);
            Window();
    };
}