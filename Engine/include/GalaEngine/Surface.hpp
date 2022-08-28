// Project: GalaEngine
// File: Surface.hpp
// Description: Surface class with drawing functions for sprites; an advanced wrapper for textures.
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#include <raylib.h>
#include <GalaEngine/Sprite.hpp>
#include <GalaEngine/Colour.hpp>

namespace GalaEngine {
    class Surface {
        public:
            Texture texture;

            void DrawSprite(Sprite sprite, int frame, int x, int y, float scaleX = 1.0f, float scaleY = 1.0f, float rotation = 0.0f, Colour blendColour = C_WHITE);

            void Update();
            Image GetImage();

            Surface(int width, int height);
            Surface();
    };
}