// Project: GalaEngine
// File: Surface.hpp
// Description: Surface class with drawing functions for sprites; an advanced wrapper for textures.
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <raylib.h>
#include <raymath.h>
#include <GalaEngine/NSlice.hpp>
#include <GalaEngine/Sprite.hpp>
#include <GalaEngine/Colour.hpp>

namespace GalaEngine {
    /*! @brief Surface class; essentially a drawable texture.
     *  @details This class contains a texture, and an interface to easily
     *  draw onto it.
     */
    class Surface {
        public:
            /*! @name Properties
             *  @details Basic properties for the Surface.
             */
            /// @{
            RenderTexture renderTexture;    //!< The render target.
            Colour clearColour = C_BLACK;   //!< The clear colour (background).
            /// @}


            /*! @name Drawing Primitives
             *  @details Use these functions to draw primitive shapes.
             *  @note All outlines are **inset** with **positive thickness**, and **outset** with **negative thickness**.
             */
            /// @{
            /*! @brief Draw a pixel.
             *  @details Draws a single pixel onto the **renderTexture** of
             *  specified colour.
             *  @param x The X position of the pixel.
             *  @param y The Y position of the pixel.
             *  @param colour The colour of the pixel.
             */
            void DrawPixel(int x, int y, Colour colour = C_WHITE);

            /*! @brief Draw a line.
             *  @details Draws a line onto the **renderTexture** with specified
             *  colour.
             *  @param x1 The start X position.
             *  @param y1 The start Y position.
             *  @param x2 The end X position.
             *  @param y2 The end Y position.
             *  @param colour The colour of the line.
             */
            void DrawLine(int x1, int y1, int x2, int y2, Colour colour = C_WHITE);
            /*! @brief Draw a line (with thickness).
             *  @details Draws a line onto the **renderTexture** with specified
             *  colour and thickness.
             *  @param x1 The start X position.
             *  @param y1 The start Y position.
             *  @param x2 The end X position.
             *  @param y2 The end Y position.
             *  @param thickness How thick the line is (in pixels).
             *  @param colour The colour of the line.
             */
            void DrawLine(int x1, int y1, int x2, int y2, float thickness, Colour colour = C_WHITE);

            /*! @brief Draw a rectangle.
             *  @details Draws a rectangle onto the **renderTexture** with
             *  specified colour, and an optional toggle for if the rectangle
             *  is just an outline.
             *  @param x The top-left corner's X position.
             *  @param y The top-left corner's Y position.
             *  @param width The width of the rectangle.
             *  @param height The height of the rectangle.
             *  @param colour The colour of the rectangle.
             *  @param outline Whether or not the rectangle should just be an outline.
             *  @param thickness The thickness of the outline (if any), in pixels.
             */
            void DrawRectangle(int x, int y, int width, int height, Colour colour = C_WHITE, bool outline = false, float thickness = 1.0f);
            /*! @brief Draw a rectangle (with rotation).
             *  @details Draws a rectangle onto the **renderTexture** with
             *  specified colour, rotation, and origin of rotation.
             *  @param x The top-left corner's X position (before rotation).
             *  @param y The top-left corner's Y position (before rotation).
             *  @param width The width of the rectangle (before rotation).
             *  @param height The height of the rectangle (before rotation).
             *  @param rotation The rotation of the rectangle (in degrees).
             *  @param origin Where about to do the rotation (relative to the **x** and **y** coordinates).
             *  @param colour The colour of the rectangle.
             */
            void DrawRectangle(int x, int y, int width, int height, float rotation, Vector2 origin = {0.0f, 0.0f}, Colour colour = C_WHITE);
            /*! @brief Draw a rectangle with corner colours.
             *  @details Draws a rectangle onto the **renderTexture** with
             *  specified colours (defined clockwise).
             *  @param x The top-left corner's X position.
             *  @param y The top-left corner's Y position.
             *  @param width The width of the rectangle.
             *  @param height The height of the rectangle.
             *  @param c1 The top-left corner's colour.
             *  @param c2 The top-right corner's colour.
             *  @param c3 The bottom-left corner's colour.
             *  @param c4 The bottom-right corner's colour.
             */
            void DrawRectangleColours(int x, int y, int width, int height, Colour c1, Colour c2, Colour c3, Colour c4);
            /*! @brief Draw a rounded rectangle.
             *  @details Draws a rounded rectangle onto the **renderTexture**
             *  with specified corner radius (like CSS's **border-radius**
             *  property), and an optional toggle for if the rectangle is just
             *  an outline.
             *  @param x The top-left corner's X position.
             *  @param y The top-left corner's Y position.
             *  @param width The width of the rectangle.
             *  @param height The height of the rectangle.
             *  @param radius The corner radius.
             *  @param colour The colour of the rectangle.
             *  @param outline Whether or not the rectangle should just be an outline.
             *  @param thickness The thickness of the outline (if any), in pixels.
             */
            void DrawRectangleRounded(int x, int y, int width, int height, float radius = 8.0f, Colour colour = C_WHITE, bool outline = false, float thickness = 1.0f);

            /*! @brief Draw a circle.
             *  @details Draws a circle onto the **renderTexture** with an
             *  optional toggle for if the circle is just an outline.
             *  @param x The circle centre's X position.
             *  @param y The circle centre's Y position.
             *  @param radius The radius of the circle.
             *  @param colour The colour of the circle.
             *  @param outline Whether or not the circle should just be an outline.
             *  @param thickness The thickness of the outline (if any), in pixels.
             */
            void DrawCircle(int x, int y, float radius, Colour colour = C_WHITE, bool outline = false, float thickness = 1.0f);
            /*! @brief Draw a circle with colours.
             *  @details Draws a circle onto the **renderTexture** with an
             *  inner and outer colour.
             *  @param x The circle centre's X position.
             *  @param y The circle centre's Y position.
             *  @param radius The radius of the circle.
             *  @param innerColour The inner colour of the circle.
             *  @param outerColour The outer colour of the circle.
             */
            void DrawCircle(int x, int y, float radius, Colour innerColour, Colour outerColour);
            /*! @brief Draw an ellipse.
             *  @details Draws an ellipse onto the **renderTexture** with
             *  horizontal & vertical radii, and an optional toggle for if the
             *  ellipse is just an outline.
             *  @param x The ellipse centre's X position.
             *  @param y The ellipse centre's Y position.
             *  @param radiusH The horizontal radius of the ellipse.
             *  @param radiusV The vertical radius of the ellipse.
             *  @param colour The colour of the ellipse.
             *  @param outline Whether or not the ellipse should just be an outline.
             *  @param thickness The thickness of the outline (if any), in pixels.
             */
            void DrawEllipse(int x, int y, float radiusH, float radiusV, Colour colour = C_WHITE, bool outline = false, float thickness = 1.0f);

            /*! @brief Draw a triangle.
             *  @details Draws a triangle onto the **renderTexture** with a
             *  specified colour.
             *  @param x1 First point's X position.
             *  @param y1 First point's Y position.
             *  @param x2 Second point's X position.
             *  @param y2 Second point's Y position.
             *  @param x3 Third point's X position.
             *  @param y3 Third pint's Y position.
             *  @param colour The colour of the triangle.
             *  @param outline Whether or not the triangle should just be an outline.
             */
            void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Colour colour = C_WHITE, bool outline = false);
            /// @}


            /*! @name Drawing Text
             *  @details Use these functions to draw text.
             */
            /// @{
            /*! @brief Draw text onto the **renderTexture** with font.
             *  @details Draw text with specified font.
             *  @param font The font to draw with.
             *  @param text The text of the string.
             *  @param x The top-left X position of the text.
             *  @param y The top-left Y position of the text.
             *  @param size The size of the text.
             *  @param colour The colour of the text.
             */
            void DrawText(Font font, std::string text, int x, int y, int size = 20, Colour colour = C_WHITE);
            /*! @brief Draw text.
             *  @details Draw text onto the **renderTexture**.
             *  @param text The text of the string.
             *  @param x The top-left X position of the text.
             *  @param y The top-left Y position of the text.
             *  @param size The size of the text.
             *  @param colour The colour of the text.
             */
            void DrawText(std::string text, int x, int y, int size = 20, Colour colour = C_WHITE);
            /// @}


            /*! @name Draw Textures
             *  @details Use these functions to draw textures.
             *  @note All coordinates are given in pixel-space relative to the
             *  top-left corner (not normalised floating-point coordinates).
             */
            /// @{
            /*! @brief Draw a texture (with scale and origin rotation).
             *  @details Draws a texture onto the **renderTexture** with scale
             *  and a rotation around a given origin.
             *  @param texture The texture to draw.
             *  @param x The top-left X position of the texture (before rotation).
             *  @param y The top-left Y position of the texture (before rotation).
             *  @param scaleX The horizontal scale of the texture.
             *  @param scaleY The vertical scale of the texture.
             *  @param rotation The rotation of the texture (in degrees).
             *  @param origin The origin of the rotation.
             *  @param blendColour The blend colour of the texture.
             */
            void DrawTexture(
                Texture texture,
                int x, int y,
                float scaleX, float scaleY,
                float rotation,
                Vector2 origin,
                Colour blendColour = C_WHITE
            );
            /*! @brief Draw a texture (with scale and simple rotation).
             *  @details Draws a texture onto the **renderTexture** with scale
             *  and rotation around the top-left corner.
             *  @param texture The texture to draw.
             *  @param x The top-left X position of the texture.
             *  @param y The top-left Y position of the texture.
             *  @param scaleX The horizontal scale of the texture.
             *  @param scaleY The vertical scale of the texture.
             *  @param rotation The rotation of the texture (in degrees).
             *  @param blendColour The blend colour of the texture.
             */
            void DrawTexture(
                Texture texture,
                int x, int y,
                float scaleX = 1.0f, float scaleY = 1.0f,
                float rotation = 0.0f,
                Colour blendColour = C_WHITE
            );
            /*! @brief Draw a portion of a texture.
             *  @details Draws a portion of a texture onto the
             *  **renderTexture** with source and destination rectangles.
             *  @param texture The texture to draw.
             *  @param src The source rectangle.
             *  @param dest The destination rectangle.
             *  @param blendColour The blend colour of the texture.
             */
            void DrawTexture(
                Texture texture,
                Rectangle src,
                Rectangle dest,
                Colour blendColour = C_WHITE
            );
            /*! @brief Draw a scaled and rotated portion of a texture.
             *  @details Draws a portion of a texture onto the
             *  **renderTexture** with scale and a rotation around a given
             *  origin.
             *  @param texture The texture to draw.
             *  @param src The source rectangle.
             *  @param dest The destination rectangle.
             *  @param origin The origin of the rotation.
             *  @param scale The scale of the texture.
             *  @param rotation The rotation of the texture (in degrees).
             *  @param blendColour The blend colour of the texture.
             */
            void DrawTextureTiled(
                Texture texture,
                Rectangle src,
                Rectangle dest,
                Vector2 origin = {0.0f, 0.0f},
                float scale = 1.0f,
                float rotation = 0.0f,
                Colour blendColour = C_WHITE
            );
            /// @}

            /*! @name Drawing Sprites
             *  @details Use these functions to draw sprites.
             */
            /// @{
            /*! @brief Draw a sprite.
             *  @details Draws a sprite onto the **renderTexture**.
             *  @param sprite The sprite to draw.
             *  @param frame The frame of the sprite to draw.
             *  @param x The X position of the sprite (before rotation).
             *  @param y The Y position of the sprite (before rotation).
             *  @param scaleX The horizontal scale of the sprite.
             *  @param scaleY The vertical scale of the sprite.
             *  @param rotation The rotation of the sprite.
             *  @param blendColour The blend colour to draw the sprite with.
             */
            void DrawSprite(
                Sprite sprite, int frame,
                int x, int y,
                float scaleX = 1.0f, float scaleY = 1.0f,
                float rotation = 0.0f,
                Colour blendColour = C_WHITE
            );
            /// @}

            /*! @name Drawing 9-slices
             *  @details Use these functions to draw 9-slices.
             */
            /// @{
            /*! @brief Draw a 9-slice.
             *  @details Draws a 9-slice onto the **renderTexture**.
             *  @param nslice The 9-slice to draw.
             *  @param x The X position of the sprite (before rotation).
             *  @param y The Y position of the sprite (before rotation).
             *  @param width The horizontal scale of the sprite.
             *  @param height The vertical scale of the sprite.
             *  @param blendColour The blend colour to draw the sprite with.
             */
            void DrawNSlice(
                NSlice nslice,
                int x, int y,
                int width, int height,
                Colour blendColour = C_WHITE
            );
            /// @}

            /*! @name Misc. & Control
             *  @details Use these functions for miscellaneous control, and get
             *  properties of the surface.
             */
            /// @{
            void Resize(int width, int height); //!< Resize surface (render texture).
            void Clear(Colour colour);          //!< Clear surface with colour.
            void Clear();                       //!< Clear surface with default colour.
            Image GetImage();                   //!< Get image of surface.
            void Destroy();                     //!< Destroy surface and unload textures.
            /// @}

            /*! @brief Constructor
             *  @details Constructs a surface with width, height, and clear
             *  colour.
             *  @param width The width of the surface (renderTexture).
             *  @param height The height of the surface (renderTexture).
             *  @param colour The clear colour of the surface.
             */
            Surface(int width, int height, Colour colour = C_BLACK);
            Surface();
    };
}