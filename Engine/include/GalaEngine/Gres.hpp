// Project: GalaEngine
// File: Gres.hpp
// Description: .gres loading.
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <raylib.h>

#include <libxdt.hpp>
#include <GalaEngine/Sprite.hpp>
#include <GalaEngine/Tileset.hpp>

namespace GalaEngine {
    namespace Gres {
        Texture LoadTextureData (const std::vector<uint8_t> &data);
        Texture LoadTexture     (const std::string &filePath);
        Sprite  LoadSpriteData  (const std::vector<uint8_t> &data);
        Sprite  LoadSprite      (const std::string &filePath);
        Tileset LoadTilesetData (const std::vector<uint8_t> &data);
        Tileset LoadTileset     (const std::string &filePath);
        Sound   LoadSoundData   (const std::vector<uint8_t> &data);
        Sound   LoadSound       (const std::string &filePath);
        Font    LoadFontData    (const std::vector<uint8_t> &data);
        Font    LoadFont        (const std::string &filePath);
    }
}