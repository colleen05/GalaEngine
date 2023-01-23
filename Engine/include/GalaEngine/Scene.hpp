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
#include <GalaEngine/EntityLayer.hpp>
#include <GalaEngine/TileLayer.hpp>
#include <GalaEngine/Camera.hpp>
#include <GalaEngine/AssetManager.hpp>
#include <GalaEngine/InputManager.hpp>
#include <GalaEngine/SoundManager.hpp>
#include <GalaEngine/Window.hpp>
#include <iostream>
#include <map>
#include <stdint.h>

namespace GalaEngine {
    class Scene {
        protected:
            std::map<uint8_t, Layer*>   _layers;
            std::map<uint32_t, Entity*> _entities;

            std::map<std::string, uint8_t>  _layerNames;
            std::map<std::string, uint32_t> _entityNames;

            int _width  = 640;
            int _height = 480;

        public:
            // Surface, camera, and asset manager
            Surface *targetSurface = nullptr;
            GalaEngine::Camera mainCamera;

            GalaEngine::Window       *window = nullptr;
            GalaEngine::AssetManager *assets = nullptr;
            GalaEngine::InputManager *input  = nullptr;
            GalaEngine::SoundManager *sound  = nullptr;

            // Entity & layers
            uint32_t    PushEntity  (Entity *entity, const std::string &name = "");
            Entity      *GetEntity  (const std::string &name);
            void        PushLayer   (Layer *layer, const int position = -1);

            // Add default layer types
            BackgroundLayer *AddBackgroundLayer (const Texture texture, const Colour clearColour = C_CLEAR, const int position = -1);
            EntityLayer     *AddEntityLayer     (const Colour clearColour = C_CLEAR, const int position = -1);
            TileLayer       *AddTileLayer       (const Tileset &tileset, const std::vector<uint16_t> &tiles, const int width, const int height, const Colour clearColour = C_CLEAR, const int position = -1);

            // Utility
            void    Resize          (const int width, const int height);
            Vector2 GetSize         ();
            void    Update          ();
            void    RenderLayers    ();

            // Constructors
            Scene(Surface *targetSurface, const int width = 640, const int height = 480);
            Scene();
    };
}