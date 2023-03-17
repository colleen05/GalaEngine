// Project: GalaEngine
// File: NSlice.hpp
// Description: 9-Slice definition.
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <raylib.h>
#include <array>

namespace GalaEngine {
    /*! @brief 9-Slice class
     *  @details Data for 9-slice graphics.
     */
    struct NSlice {
        public:
            Texture     texture;                //!< Texture atlas.
            Rectangle   centreSlice;            //!< The centre slice.
            bool        stretchSlices[5] = { }; //!< Each stretched slice in TOP, RIGHT, BOTTOM, LEFT, CENTRE order.
    };
}