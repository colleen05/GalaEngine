// Project: GalaEngine
// File: Tileset.hpp
// Description: Tileset class for holding tileset texture & information
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <raylib.h>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>

namespace GalaEngine {
    class Tileset {
        public:
            Texture texture;
            int tileSize;
            
            std::vector<uint16_t> flags;

            Rectangle GetTileRect(const int tileX, const int tileY);
            Rectangle GetTileRect(const int tileID);

            uint16_t GetTileFlags(const int tileX, const int tileY);
            uint16_t GetTileFlags(const int tileID);

            Tileset(const Texture texture, const int tileSize, const std::vector<uint16_t> &flags = {});
            Tileset();
    };
}