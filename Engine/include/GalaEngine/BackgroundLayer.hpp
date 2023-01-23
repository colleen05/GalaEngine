// Project: GalaEngine
// File: BackgroundLayer.hpp
// Description: Inherited class from Layer which supports background rendering
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <GalaEngine/Layer.hpp>

namespace GalaEngine {
    class BackgroundLayer : public Layer {
        public:
            Texture background;
            Vector2 offset = {0.0f};
            Vector2 scrollSpeed = {0.0f};
            Vector2 scale = {1.0f, 1.0f};

            void OnStart();
            void OnUpdate();
            void OnDraw(const GalaEngine::Camera &camera);
            void OnDestroy();

            BackgroundLayer(const int width, const int height, const Texture background, const Colour clearColour = C_BLACK);
            BackgroundLayer();
    };
}