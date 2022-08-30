// Project: GalaEngine
// File: Layer.hpp
// Description: Layer class
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#include <GalaEngine/Surface.hpp>

namespace GalaEngine {
    class Layer {
        public:
            Surface surface;

            virtual void OnStart();
            virtual void OnUpdate();
            virtual void OnDraw();

            Layer();
    };
}