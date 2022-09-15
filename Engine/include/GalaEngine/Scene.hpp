// Project: GalaEngine
// File: Scene.hpp
// Description: Scene class for managing entities and layers
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <GalaEngine/Entity.hpp>
#include <GalaEngine/Layer.hpp>
#include <GalaEngine/BackgroundLayer.hpp>
#include <GalaEngine/TileLayer.hpp>
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

            int _width, _height;

        public:
            Surface *targetSurface = nullptr;
            GalaEngine::Camera mainCamera;

            void PushLayer(Layer *layer, int position = -1);

            BackgroundLayer *AddBackgroundLayer(Texture texture, Colour clearColour = C_CLEAR, int position = -1);
            TileLayer       *AddTileLayer(Tileset tileset, std::vector<uint16_t> tiles, int width, int height, Colour clearColour = C_CLEAR, int position = -1);

            void    Resize(int width, int height);
            Vector2 GetSize();
            void    Update();
            void    RenderLayers();

            // Constructor
            Scene(Surface *targetSurface, int width = 640, int height = 480);
            Scene();
    };
}