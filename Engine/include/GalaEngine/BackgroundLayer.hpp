// Project: GalaEngine
// File: BackgroundLayer.hpp
// Description: Inherited class from Layer which supports background rendering
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <GalaEngine/Layer.hpp>

namespace GalaEngine {
    /*! @brief Background layer
     *  @details Draws a background (from supplied texture) with a few
     *  parameters, to its Surface.
     */
    class BackgroundLayer : public Layer {
        public:
            /*! @name Background Properties
             *  @details These variables control how the background is drawn to
             *  the Surface.
             */
            /// @{
            Texture background  = {};           //!< The texture of the background itself.
            Vector2 offset      = {0.0f, 0.0f}; //!< The position of the background.
            Vector2 scrollSpeed = {0.0f, 0.0f}; //!< How many pixels the background should move per frame.
            Vector2 scale       = {1.0f, 1.0f}; //!< The scale of the background.
            /// @}

            /*! @name Inherited Methods
             *  @details These functions are overridden from the Layer class,
             *  and define behaviour relevant to tile rendering.
             */
            /// @{
            void OnStart();                                 //!< No special behaviour.
            void OnUpdate();                                //!< Updates background offset.
            void OnDraw(const GalaEngine::Camera &camera);  //!< Draws background to Surface.
            void OnDestroy();                               //!< No special behaviour.
            /// @}

            /*! @brief Constructor
             *  @details Construct and create Surface (width x height), with
             *  specified background and clear colour.
             *  @param width Width of background layer.
             *  @param height Height of background layer.
             *  @param background Texture to use for background.
             *  @param clearColour What colour the Surface should be cleared with.
             */
            BackgroundLayer(const int width, const int height, const Texture background, const Colour clearColour = C_BLACK);
            BackgroundLayer();
            ~BackgroundLayer();
    };
}