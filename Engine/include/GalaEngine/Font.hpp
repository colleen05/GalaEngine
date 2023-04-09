// Project: GalaEngine
// File: Font.hpp
// Description: Font class.
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <raylib.h>
#include <raymath.h>

#include <cstdint>
#include <list>
#include <vector>
#include <string>
#include <algorithm>

#include <GalaEngine/Data.hpp>
#include <GalaEngine/Config.hpp>

using BitmapFont = ::Font;

namespace GalaEngine {
    /*! @brief Container for fonts.
     *  @details This class contains font data, with interfaces for retrieving
     *  the font at different resolutions for drawing.
     */
    class Font {
        private:
            std::vector<uint8_t> _fontData;  //!< Font file data.
            std::vector<int>     _fontChars; //!< Character set to render from font data.

        public:
            struct FontCacheItem {
                int size;           //!< Font size in bitmap.
                BitmapFont font;    //!< Internal bitmap font.
            };

            std::list<FontCacheItem> fontCacheList; //!< Internal cache queue for rendered bitmaps.

            void ClearCache(); //!< Clear cached bitmap fonts.

            bool LoadFontData(const std::vector<uint8_t> &data, const std::vector<int> &chars = {}); //!< Load font data.
            std::vector<uint8_t> GetFontData(); //!< Get the loaded font file data.

            BitmapFont GenerateBitmapFont(const int size); //!< Generate bitmap font at specified size without caching.
            BitmapFont GetAtSize(const int size); //!< Get bitmap font at specified size.

            Font(); //!< Default constructor
    };
}