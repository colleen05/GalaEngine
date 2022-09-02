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
            Vector2 position;
            Vector2 size;

            Camera();
    };
}