// Project: GalaEngine
// File: Layer.hpp
// Description: Layer class
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <GalaEngine/Surface.hpp>
#include <GalaEngine/Camera.hpp>
#include <iostream>

namespace GalaEngine {
    /*! @brief Layer base class
     *  @details Primary element within a Scene, which can render onto its
     *  own surface, and define its own behaviour upon initialisation,
     *  updating, drawing, and destruction.
     * 
     *  Common layer types include:
     *  - BackgroundLayer: Draws a simple background with a few parameters.
     *  - TileLayer: Draws a tilemap and provides interfacing with Tileset.
     *  - EntityLayer: Updates and renders entities.
     */
    class Layer {
        public:
            Surface *surface = nullptr;     //!< Surface on which to draw during **OnDraw()**
            Colour blendColour = C_WHITE;   //!< Colour to clear the surface with.

            /*! @brief Behaviour upon starting.
             *  @details This function is called by the Scene class upon being
             *  attached to said Scene. Override this to define behaviour which
             *  should be executed upon scene-attachment.
             */
            virtual void OnStart();
            /*! @brief Behaviour upon updating.
             *  @details This function is called by the Scene class when it is
             *  updated. Override this to define behaviour which should be
             *  executed constantly.
             *  @note This function may be called multiple times per-frame.
             *  Do not rely on this function for time-sensitive operations.
             */
            virtual void OnUpdate();
            /*! @brief Drawing to surface.
             *  @details This function is called by the Scene class once
             *  per frame, before compositing each layer to its own Surface.
             *  Override this to define drawing behaviour, or behaviour which
             *  should be executed once per frame.
             *  @note The **camera** argument can be used for better-optimised
             *  rendering, such as culling out stuff not visible by a camera.
             *  @param camera The camera currently viewing the Layer.
             */
            virtual void OnDraw(const GalaEngine::Camera &camera);
            /*! @brief Behaviour upon destruction.
             *  @details This function is called by the Scene class when
             *  disposing of a Layer. Override this function to define
             *  behaviour which should be executed before destruction,
             *  such as unloading resources in memory.
             */
            virtual void OnDestroy();

            /*! @brief Construct with pre-existing surface.
             *  @details Use this constructor when initialising with a
             *  pre-exisitng Surface.
             *  @param surface Pointer to the pre-exisitng surface.
             */
            Layer(const Surface *surface);
            /*! @brief Construct and create new surface.
             *  @details Use this constructor to initialise and create a new
             *  surface.
             *  @param width The desired width of the Surface.
             *  @param height The desired height of the Surface.
             *  @param clearColour What colour the Surface should be cleared with.
             */
            Layer(const int width, const int height, const Colour clearColour = C_BLACK);
            Layer();
            virtual ~Layer();
    };
}