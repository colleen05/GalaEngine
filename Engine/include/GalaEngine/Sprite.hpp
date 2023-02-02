// Project: GalaEngine
// File: Sprite.hpp
// Description: Sprite class
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <raylib.h>
#include <vector>

namespace GalaEngine {
    /*! @brief Sprite structure
     *  @details Data required for drawing sprites.
     */
    struct Sprite {
        Texture texture;                    //!< Sprite texture.
        Vector2 origin;                     //!< Origin of the sprite.
        std::vector<Rectangle> frameRects;  //!< Vector of frame rectangles within texture.
    };
}