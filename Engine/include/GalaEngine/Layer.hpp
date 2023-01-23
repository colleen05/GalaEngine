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
    class Layer {
        public:
            Surface *surface = nullptr;
            Colour blendColour = C_WHITE;

            virtual void OnStart();
            virtual void OnUpdate();
            virtual void OnDraw(const GalaEngine::Camera &camera);
            virtual void OnDestroy();

            Layer(const Surface *surface);
            Layer(const int width, const int height, const Colour clearColour = C_BLACK);
            Layer();
            ~Layer();
    };
}