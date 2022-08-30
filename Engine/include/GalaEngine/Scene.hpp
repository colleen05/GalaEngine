// Project: GalaEngine
// File: Scene.hpp
// Description: Scene class for managing entities and layers
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#include <GalaEngine/Entity.hpp>
#include <GalaEngine/Layer.hpp>
#include <map>

namespace GalaEngine {
    class Scene {
        public:
            std::map<std::string, Layer*> layers;

            void Update();

            // Constructor
            Scene();
    };
}