// Project: GalaEngine
// File: Sprite.hpp
// Description: Sprite class
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#include <raylib.h>
#include <vector>

namespace GalaEngine {
    struct Sprite {
        Texture texture;                   // Source texture
        Vector2 origin;                     // Origin
        std::vector<Rectangle> frameRects;  // Frame rectangles
    };
}