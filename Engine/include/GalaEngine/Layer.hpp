// Project: GalaEngine
// File: Layer.hpp
// Description: Layer class
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <GalaEngine/Surface.hpp>
#include <iostream>

namespace GalaEngine {
    class Layer {
        public:
            Surface *surface;
            Colour blendColour = C_WHITE;

            virtual void OnStart();
            virtual void OnUpdate();
            virtual void OnDraw();
            virtual void OnDestroy();

            Layer(Surface *surface);
            Layer(int width, int height, Colour clearColour = C_BLACK);
            Layer();
            ~Layer();
    };
}