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
#include <GalaEngine/NSlice.hpp>
#include <GalaEngine/Font.hpp>

namespace GalaEngine {
    /*! @brief Resource loading functions
     *  @details These functions are for loading asset classes from resource
     *  filepaths or data.
     */
    namespace Gres {
        /*! @name Loading textures
         *  @param data Resource file bytes.
         *  @param filePath Resource file path.
         */
        /// @{
        Texture LoadTextureData(const std::vector<uint8_t> &data);  //!< Load Texture from byte array.
        Texture LoadTexture(const std::string &filePath);           //!< Load Texture from resource file (by path).
        /// @}

        /*! @name Loading sprites
         *  @param data Resource file bytes.
         *  @param filePath Resource file path.
         */
        /// @{
        Sprite LoadSpriteData(const std::vector<uint8_t> &data);    //!< Load Sprite from resource file data.
        Sprite LoadSprite(const std::string &filePath);             //!< Load Sprite from resource file (by path).
        /// @}

        /*! @name Loading tilesets
         *  @param data Resource file bytes.
         *  @param filePath Resource file path.
         */
        /// @{
        Tileset LoadTilesetData(const std::vector<uint8_t> &data);  //!< Load Tileset from resource file data.
        Tileset LoadTileset(const std::string &filePath);           //!< Load Tileset from resource file (by path).
        /// @}

        /*! @name Loading 9-slices
         *  @param data Resource file bytes.
         *  @param filePath Resource file path.
         */
        /// @{
        NSlice LoadNSliceData(const std::vector<uint8_t> &data);    //!< Load NSlice from resource file data.
        NSlice LoadNSlice(const std::string &filePath);             //!< Load NSlice from resource file (by path).
        /// @}

        /*! @name Loading sounds
         *  @param data Resource file bytes.
         *  @param filePath Resource file path.
         */
        /// @{
        Sound LoadSoundData(const std::vector<uint8_t> &data);  //!< Load Sound from resource file data.
        Sound LoadSound(const std::string &filePath);           //!< Load Sound from resource file (by path).
        /// @}

        /*! @name Loading fonts
         *  @param data Resource file bytes.
         *  @param filePath Resource file path.
         */
        /// @{
        GalaEngine::Font LoadFontData(const std::vector<uint8_t> &data);    //!< Load Font from resource file data.
        GalaEngine::Font LoadFont(const std::string &filePath);             //!< Load Font from resource file (by path).
        /// @}
    }
}