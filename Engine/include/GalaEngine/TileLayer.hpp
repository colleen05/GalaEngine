// Project: GalaEngine
// File: TileLayer.hpp
// Description: Inherited class from Layer which supports tileset rendering
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <GalaEngine/Layer.hpp>
#include <GalaEngine/Tileset.hpp>

namespace GalaEngine {
    class TileLayer : public Layer {
        public:
            int width, height;
            Tileset tileset;
            std::vector<uint16_t> tiles;
            Texture texture;

            void OnStart();
            void OnUpdate();
            void OnDraw(GalaEngine::Camera camera);
            void OnDestroy();

            TileLayer(Tileset tileset, std::vector<uint16_t> tiles, int tilesX, int tilesY, int surfaceWidth, int surfaceHeight);
            TileLayer();
    };
}