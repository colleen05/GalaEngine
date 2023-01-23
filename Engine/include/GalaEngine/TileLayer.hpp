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

            int GetTileIndex(const int x, const int y);

            uint16_t GetTile(const int x, const int y);
            uint16_t GetTileFlags(const int x, const int y);

            void Render();

            void OnStart();
            void OnUpdate();
            void OnDraw(const GalaEngine::Camera &camera);
            void OnDestroy();

            TileLayer(const Tileset &tileset, const std::vector<uint16_t> &tiles, const int tilesX, const int tilesY, const Colour clearColour = C_BLACK);
            TileLayer();
    };
}
