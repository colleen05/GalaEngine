// Project: GalaEngine
// File: Window.hpp
// Description: Window creation and management class.
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <raylib.h>
#include <string>
#include <GalaEngine/Surface.hpp>

namespace GalaEngine {
    class Window {
        private:
            std::string _title;
            int _width, _height;
            int _targetFPS;

        public:
            Surface surface;

            // Initialisation, drawing, and destruction
            void Init();
            void Render();
            void Exit();

            // Status getters
            bool ShouldClose();
            int GetWidth();
            int GetHeight();

            // Constructors
            Window(std::string title, int width, int height, int targetFPS = 60);
            Window();
    };
}