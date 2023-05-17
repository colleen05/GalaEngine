// Project: GalaEngine
// File: Camera.hpp
// Description: Camera class
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <raylib.h>

namespace GalaEngine {
    /*! @brief Camera
     *  @details Camera class used by classes like the Layer class for context
     *  as to what to draw (a viewport).
     */
    class Camera {
        public:
            Vector2 position = {0.0f, 0.0f}; //!< Position of the camera viewport.
            Vector2 size = {640.0f, 480.0f}; //!< Dimensions of the camera viewport.
            RenderTexture texture = {0}; //!< Where stuff visible by the camera gets drawn.

            /*! @brief Constructor
             *  @details Constructs with coordinates and viewport dimensions.
             *  @param x X position.
             *  @param y Y position.
             *  @param width Width of the viewport.
             *  @param height Height of the viewport.
             */
            Camera(const int x, const int y, const int width, const int height);
            Camera();
    };
}