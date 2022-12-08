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

            int GetTileIndex(int x, int y);

            uint16_t GetTile(int x, int y);
            uint16_t GetTileFlags(int x, int y);

            void Render();

            void OnStart();
            void OnUpdate();
            void OnDraw(GalaEngine::Camera camera);
            void OnDestroy();

            TileLayer(Tileset tileset, std::vector<uint16_t> tiles, int tilesX, int tilesY, Colour clearColour = C_BLACK);
            TileLayer();
    };
}
