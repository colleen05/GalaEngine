// Project: GalaEngine
// File: DrawTarget.hpp
// Description: Class for a surface-like texture container that supports drawing functions
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#include <raylib.h>
#include <GalaEngine/Sprite.hpp>
#include <GalaEngine/Colour.hpp>

namespace GalaEngine {
    class DrawTarget {
        public:
            Texture texture;

            void DrawSprite(Sprite sprite, int frame, int x, int y, float scaleX = 1.0f, float scaleY = 1.0f, float rotation = 0.0f, Colour blendColour = C_WHITE);

            void Update();
            Image GetImage();

            DrawTarget(int width, int height);
            DrawTarget();
    };
}