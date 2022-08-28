// Project: GalaEngine
// File: Surface.hpp
// Description: Surface class with drawing functions for sprites; an advanced wrapper for textures.
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <raylib.h>
#include <GalaEngine/Sprite.hpp>
#include <GalaEngine/Colour.hpp>

namespace GalaEngine {
    class Surface {
        public:
            RenderTexture texture;
            Colour clearColour;

            void DrawText(std::string text, int x, int y, int size = 20, Colour colour = C_WHITE);
            void DrawSprite(
                Sprite sprite, int frame,
                int x, int y,
                float scaleX = 1.0f, float scaleY = 1.0f,
                float rotation = 0.0f,
                Colour blendColour = C_WHITE
            );

            void Clear(Colour colour);
            void Clear();
            void Update();
            Image GetImage();

            Surface(int width, int height, Colour colour = C_BLACK);
            Surface();
    };
}