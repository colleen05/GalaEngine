// Project: GalaEngine
// File: Font.hpp
// Description: Font class.
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <raylib.h>
#include <raymath.h>

#include <list>
#include <algorithm>

#include <GalaEngine/Config.hpp>

using BitmapFont = ::Font;

namespace GalaEngine {
    /*! @brief Container for fonts.
     *  @details This class contains font data, with interfaces for retrieving
     *  the font at different resolutions for drawing.
     */
    class Font {
        private:
            struct _FontCacheItem {
                int size;
                BitmapFont font;
            };

            std::list<_FontCacheItem> _fontCacheList;

        public:
            BitmapFont GetAtSize(const int size); //!< Get bitmap font at specified size.

            Font(); //!< Default constructor
    };
}