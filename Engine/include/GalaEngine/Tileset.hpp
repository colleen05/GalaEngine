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

namespace GalaEngine {
    class Tileset {
        public:
            Texture texture;
            int tileSize;
            
            std::vector<uint8_t> flags;

            Rectangle GetTileRect(int tileX, int tileY);
            Rectangle GetTileRect(int tileID);

            Tileset(Texture texture, int tileSize, std::vector<uint8_t> flags = {});
            Tileset();
    };
}