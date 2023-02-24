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
    /*! @brief Tiles layer
     *  @details Draws a Tileset with tiles from a supplied Tileset, to its
     *  Surface.
     */
    class TileLayer : public Layer {
        public:
            /*! @name Tilemap Properties
             *  @details These variables pertain to rendering tiles, as well as
             *  supplying information needed when converting pixel-space
             *  coordinates into a tile index.
             */
            /// @{
            int width;                      //!< Number of tiles horizontally.
            int height;                     //!< Number of tiles vertically.
            Tileset tileset;                //!< Which tiles to draw.
            std::vector<uint16_t> tiles;    //!< Tilemap.
            Texture texture;                //!< Destination texture for drawn tiles, to be drawn to the Surface.
            /// @}

            /*! @brief Get index of a tile at coordinates.
             *  @details Get an index into the **tiles** vector calculated
             *  from supplied coordinates (in pixel space).
             *  @param x X coordinate.
             *  @param y Y coordinate.
             *  @returns Index into **tiles**.
             */
            int GetTileIndex(const int x, const int y);

            /*! @brief Get tile ID at coordinates.
             *  @details Get the tile ID (in Tileset) of a tile, at the
             *  supplied coordinates (in pixel space).
             *  @param x X coordinate.
             *  @param y Y coordinate.
             *  @returns Tile ID (in Tileset)
             */
            uint16_t GetTile(const int x, const int y);

            /*! @brief Get tile flags at coordinates.
             *  @details Get the flags (per the Tileset) of a tile, at the
             *  supplied coordinates (in pixel space).
             *  @param x X coordinate.
             *  @param y Y coordinate.
             *  @returns Tile flags (per the Tileset)
             */
            uint16_t GetTileFlags(const int x, const int y);

            /*! @brief Render tilemap to texture.
             *  @brief Renders the tilemap to the **texture** Texture, using
             *  the Tileset as the source of tile graphics.
             */
            void Render();

            /*! @name Inherited Methods
             *  @details These functions are overridden from the Layer class,
             *  and define behaviour relevant to tile rendering.
             */
            /// @{
            void OnStart();                                 //!< Initial render of tiles
            void OnUpdate();                                //!< No special behaviour.
            void OnDraw(const GalaEngine::Camera &camera);  //!< Draws **texture** to the Surface.
            void OnDestroy();                               //!< No special behaviour.
            /// @}

            /*! @brief Constructor
             *  @details Construct and create Surface (width x height), with
             *  specified clearColour. Sets the **tileset** Tileset, and vector
             *  of tiles to be drawn, with horizontal and vertical tile counts.
             *  @param tileset Tileset to use when rendering tiles vector.
             *  @param tiles Vector of tiles to be drawn (tilemap).
             *  @param tilesX Number tiles horizontally (**width** member).
             *  @param tilesY Number tiles vertically (**height** member).
             *  @param clearColour What colour the Surface should be cleared width.
             */
            TileLayer(const Tileset &tileset, const std::vector<uint16_t> &tiles, const int tilesX, const int tilesY, const Colour clearColour = C_BLACK);
            TileLayer();
            ~TileLayer();
    };
}
