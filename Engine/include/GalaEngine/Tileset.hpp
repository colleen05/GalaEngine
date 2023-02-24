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
    /*! @brief Tileset class
     *  @details A container for a tileset texture and parameters, with
     *  interfacing functions.
     */
    class Tileset {
        public:
            Texture texture; //!< Texture of all tiles.
            int tileSize;    //!< Side length of the tiles.
            
            std::vector<uint16_t> flags;    //!< Flags for each tile

            /*! @name Tile Rectangles
             *  @details These functions get the rectangle region into the
             *  texture for a specified tile.
             *  @param tileX The tile's horizontal position.
             *  @param tileY The tile's vertical position.
             *  @param tileID The direct index of a tile.
             */
            /// @{
            Rectangle GetTileRect(const int tileX, const int tileY);    //!< Get a tile's rectangle by position.
            Rectangle GetTileRect(const int tileID);                    //!< Get a tile's rectangle by index.
            /// @}

            /*! @name Tile Flags
             *  @details These functions get the flags for a specified tile.
             *  @param tileX The tile's horizontal position.
             *  @param tileY The tile's vertical position.
             *  @param tileID The direct index of a tile.
             */
            /// @{
            uint16_t GetTileFlags(const int tileX, const int tileY);    //!< Get a tile's flags by position.
            uint16_t GetTileFlags(const int tileID);                    //!< Get a tile's rectangle by index.
            /// @}

            /*! @brief Constructor
             *  @details Construct a tileset from a texture, tile size, and
             *  flags.
             */
            Tileset(const Texture texture, const int tileSize, const std::vector<uint16_t> &flags = {});
            Tileset();
    };
}