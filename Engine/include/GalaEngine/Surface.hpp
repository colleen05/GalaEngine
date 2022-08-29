// Project: GalaEngine
// File: Surface.hpp
// Description: Surface class with drawing functions for sprites; an advanced wrapper for textures.
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <raylib.h>
#include <raymath.h>
#include <GalaEngine/Sprite.hpp>
#include <GalaEngine/Colour.hpp>

namespace GalaEngine {
    class Surface {
        public:
            RenderTexture texture;
            Colour clearColour;

            // Point
            void DrawPixel(int x, int y, Colour colour = C_WHITE);

            // Primitives
            void DrawRectangle(int x, int y, int width, int height, Colour colour = C_WHITE);
            void DrawRectangle(int x, int y, int width, int height, float rotation, Vector2 origin = {0.0f, 0.0f}, Colour colour = C_WHITE);
            
            // Text
            void DrawText(std::string text, int x, int y, int size = 20, Colour colour = C_WHITE);
            
            // Sprites
            void DrawSprite(
                Sprite sprite, int frame,
                int x, int y,
                float scaleX = 1.0f, float scaleY = 1.0f,
                float rotation = 0.0f,
                Colour blendColour = C_WHITE
            );

            // Misc
            void Clear(Colour colour);
            void Clear();
            Image GetImage();

            // Constructors
            Surface(int width, int height, Colour colour = C_BLACK);
            Surface();
    };
}