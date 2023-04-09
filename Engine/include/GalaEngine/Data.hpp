// Project: GalaEngine
// File: Data.hpp
// Description: Raw data arrays for embedded resources.
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <stdint.h>
#include <raylib.h>

#include <vector>

#define ARRAY_LENGTH(x) sizeof(x) / sizeof(x[0])

namespace GalaEngine {
    namespace Data {
        inline Color MissingTexturePx[] = {
            {0xff, 0xff, 0xff, 0xff}
        };  

        inline const Image MissingTextureImg = {
            MissingTexturePx,
            1, 1,
            1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
        };
        
        inline const std::vector<uint8_t> DefaultFontTTF = {
            #include <GalaEngine/Data/DefaultFontTTF.inc>
        };
    }
}