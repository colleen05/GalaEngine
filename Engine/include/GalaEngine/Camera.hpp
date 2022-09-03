// Project: GalaEngine
// File: Camera.hpp
// Description: Camera class
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <raylib.h>

namespace GalaEngine {
    class Camera {
        public:
            Vector2 position = {0.0f, 0.0f};
            Vector2 size = {640.0f, 480.0f};

            Camera(int x, int y, int width, int height);
            Camera();
    };
}