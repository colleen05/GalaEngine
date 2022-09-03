// Project: GalaEngine
// File: Scene.hpp
// Description: Scene class for managing entities and layers
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <GalaEngine/Entity.hpp>
#include <GalaEngine/Layer.hpp>
#include <GalaEngine/Camera.hpp>
#include <iostream>
#include <map>
#include <stdint.h>

namespace GalaEngine {
    class Scene {
        protected:
            std::map<uint8_t, Layer*> _layers;
            std::map<uint32_t, Entity*> _entities;

            std::map<std::string, uint8_t> _layerNames;
            std::map<std::string, uint32_t> _entityNames;

        public:
            Surface *targetSurface = nullptr;
            GalaEngine::Camera mainCamera;

            void PushLayer(Layer *layer);

            void Update();
            void RenderLayers();

            // Constructor
            Scene(Surface *targetSurface);
            Scene();
    };
}