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

            // Points & lines
            void DrawPixel(int x, int y, Colour colour = C_WHITE);

            void DrawLine(int x1, int y1, int x2, int y2, Colour colour = C_WHITE);
            void DrawLine(int x1, int y1, int x2, int y2, float thickness, Colour colour = C_WHITE);

            // Primitives
            void DrawRectangle(int x, int y, int width, int height, Colour colour = C_WHITE, bool outline = false, float thickness = 1.0f);
            void DrawRectangle(int x, int y, int width, int height, float rotation, Vector2 origin = {0.0f, 0.0f}, Colour colour = C_WHITE);
            void DrawRectangleColours(int x, int y, int width, int height, Colour c1, Colour c2, Colour c3, Colour c4);
            void DrawRectangleRounded(int x, int y, int width, int height, float radius = 8.0f, Colour colour = C_WHITE, bool outline = false, float thickness = 1.0f);

            void DrawCircle(int x, int y, float radius, Colour colour = C_WHITE, bool outline = false, float thickness = 1.0f);
            void DrawCircle(int x, int y, float radius, Colour innerColour, Colour outerColour);
            void DrawEllipse(int x, int y, float radiusH, float radiusV, Colour colour = C_WHITE, bool outline = false, float thickness = 1.0f);

            void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Colour = C_WHITE, bool outline = false);

            // Text
            void DrawText(std::string text, int x, int y, int size = 20, Colour colour = C_WHITE);
            
            // Textures
            void DrawTexture(
                Texture texture,
                int x, int y,
                float scaleX, float scaleY,
                float rotation,
                Vector2 origin,
                Colour blendColour = C_WHITE
            );

            void DrawTexture(
                Texture texture,
                int x, int y,
                float scaleX = 1.0f, float scaleY = 1.0f,
                float rotation = 0.0f,
                Colour blendColour = C_WHITE
            );

            void DrawTexture(
                Texture texture,
                Rectangle src,
                Rectangle dest,
                Colour blendColour = C_WHITE
            );

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
            void Destroy();

            // Constructors
            Surface(int width, int height, Colour colour = C_BLACK);
            Surface();
    };
}