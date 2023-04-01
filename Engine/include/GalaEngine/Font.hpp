// Project: GalaEngine
// File: Font.hpp
// Description: Font class.
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <raylib.h>
#include <raymath.h>

#include <vector>
#include <array>

#include <GalaEngine/Config.hpp>

using BitmapFont = ::Font;

namespace GalaEngine {
    /*! @brief Container for fonts.
     *  @details This class contains font data, with interfaces for retrieving
     *  the font at different resolutions for drawing.
     */
    class Font {
        private:
            size_t _cachedFontCount = 0;
            std::array<int, GALAENGINE_FONT_CACHE_SIZE>                         _cachedFontGetCounts {}; //!< Count of gets for each cache slot. 
            std::array<std::pair<int, BitmapFont>, GALAENGINE_FONT_CACHE_SIZE>  _cachedFonts         {}; //!< Array of cached fonts at different sizes.

        public:
            BitmapFont GetAtSize (int size); //!< Get bitmap font at specified size.

            Font(); //!< Default constructor
    };
}