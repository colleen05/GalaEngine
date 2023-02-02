// Project: GalaEngine
// File: AssetManager.hpp
// Description: Asset managing class for auto loading and unloading
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <GalaEngine/Sprite.hpp>
#include <GalaEngine/Tileset.hpp>
#include <GalaEngine/Colour.hpp>
#include <GalaEngine/Data.hpp>
#include <GalaEngine/Gres.hpp>

#include <raylib.h>
#include <string>
#include <map>
#include <iostream>

namespace GalaEngine {
    /*! @brief Path layout for resource file loading.
     *  @details Contains path names for each resource type (textures, sprites,
     *  tilesets, sounds, and fonts), as well as the base directory for such
     *  assets.
     *  @attention **Base path** must **start** with `./`. **All paths** must
     *  **end** with `/`.
     *  @note **If using GalaMake,** you should configure the output directory
     *  to be the same as the **base** path.
     */
    struct AssetPathLayout {
        std::string base     = "./resources/";  //!< Root of all game assets.
        std::string textures = "textures/";     //!< Where an AssetManager may look for textures.
        std::string sprites  = "sprites/";      //!< Where an AssetManager may look for sprites.
        std::string tilesets = "tilesets/";     //!< Where an AssetManager may look for tilesets.
        std::string sounds   = "sounds/";       //!< Where an AssetManager may look for sounds.
        std::string fonts    = "fonts/";        //!< Where an AssetManager may look for fonts.
    };

    /*! @brief Management class for game assets.
     *  @details Used by many classes as an interface for loading, retrieving,
     *  and general management of assets, loaded from resource files (.gres).
     *  The Game class holds onto a single AssetManager, which is then passed
     *  on to children. A Scene may have an AssetManager that it passes onto
     *  Entity objects upon creation. Those entities may then use the
     *  AssetManager to do various things, such as setting its sprite, playing
     *  a sound, drawing textures and fonts, etc..
     *  @note It is recommended to use the **Get** functions directly, rather
     *  than explicitly loading assets first. Such functions will
     *  **automatically load** assets if not-yet loaded.
     *  @attention Loading assets from files such as .png, .wav, .ogg, .otf,
     *  etc., **will not work**. GalaEngine uses a custom resource
     *  format (.gres). You will *need* to use **GalaMake** to compile such assets.
     */
    class AssetManager {
        public:
            AssetPathLayout pathLayout; //!< Where game resource files are looked for.

            /** @name Asset containers
             *  @details These are the containers which map asset names to
             *  the assets themselves.
             */
            /// @{
            std::map<std::string, Texture>  textures;   //!< Map of names to textures.
            std::map<std::string, Sprite*>  sprites;    //!< Map of names to sprites.
            std::map<std::string, Tileset>  tilesets;   //!< Map of names to tilesets.
            std::map<std::string, Sound>    sounds;     //!< Map of names to sounds.
            std::map<std::string, Font>     fonts;      //!< Map of names to fonts.
            /// @}


            /** @name Getting Assets
             *  @details Use these functions to retrieve assets. The
             *  AssetManager will automatically look for and load
             *  requested assets from resource (.gres) files if they have not
             *  yet been loaded.
             */
            /// @{
            /*! @brief Get texture by name.
             *  @details Looks for texture by name in the textures container.
             *  If the texture is not found, it will attempt to load it from
             *  a resource file.
             *  @param name The **name** of the texture asset (**not** the resource file path).
             *  @returns Loaded, or existing texture.
             */
            Texture GetTexture(const std::string &name);
            /*! @brief Get sprite by name.
             *  @details Looks for sprite by name in the sprites container.
             *  If the sprite is not found, it will attempt to load it from
             *  a resource file.
             *  @param name The **name** of the sprite asset (**not** the resource file path).
             *  @returns Pointer to loaded, or existing sprite.
             */
            Sprite *GetSprite(const std::string &name);
            /*! @brief Get tileset by name.
             *  @details Looks for tileset by name in the tilesets container.
             *  If the tileset is not found, it will attempt to load it from
             *  a resource file.
             *  @param name The **name** of the tileset asset (**not** the resource file path).
             *  @returns Loaded, or existing tileset.
             */
            Tileset GetTileset(const std::string &name);
            /*! @brief Get sound by name.
             *  @details Looks for sound by name in the sounds container.
             *  If the sound is not found, it will attempt to load it from
             *  a resource file.
             *  @param name The **name** of the sound asset (**not** the resource file path).
             *  @returns Loaded, or existing sound.
             */
            Sound GetSound(const std::string &name);
            /*! @brief Get font by name.
             *  @details Looks for font by name in the fonts container.
             *  If the font is not found, it will attempt to load it from
             *  a resource file.
             *  @param name The **name** of the font asset (**not** the resource file path).
             *  @returns Loaded, or existing font.
             */
            Font GetFont(const std::string &name);
            /// @}


            /** @name Loading Assets
             *  @details Use these functions to load assets directly. It is
             *  recommended to use the __Get*__ functions instead, unless you
             *  explicitly want to pre-load assets. Resource (.gres) files are
             *  looked for based upon the concatonation of paths within the
             *  *pathLayout*. Upon loading an asset, it will be added to the
             *  corresponding container, **or** replace an existing asset with
             *  the same name.
             *  @param name The name of the asset you wish to load.
             */
            /// @{
            /*! @brief Load texture by name.
             *  @details Loads a texture asset from a resource file (the
             *  directory of which is determined by the *pathLayout*), and
             *  either inserts or replaces the asset in the textures container
             *  for future use.
             *  @param name The **name** of the texture asset (**not** the resource file path).
             *  @returns Loaded texture.
             */
            Texture LoadTexture(const std::string &name);
            /*! @brief Load sprite by name.
             *  @details Loads a sprite asset from a resource file (the
             *  directory of which is determined by the *pathLayout*), and
             *  either inserts or replaces the asset in the sprites container
             *  for future use.
             *  @param name The **name** of the sprite asset (**not** the resource file path).
             *  @returns Pointer to loaded sprite.
             */
            Sprite *LoadSprite(const std::string &name);
            /*! @brief Load tileset by name.
             *  @details Loads a tileset asset from a resource file (the
             *  directory of which is determined by the *pathLayout*), and
             *  either inserts or replaces the asset in the tilesets container
             *  for future use.
             *  @param name The **name** of the tileset asset (**not** the resource file path).
             *  @returns Loaded tileset.
             */
            Tileset LoadTileset(const std::string &name);
            /*! @brief Load sound by name.
             *  @details Loads a sound asset from a resource file (the
             *  directory of which is determined by the *pathLayout*), and
             *  either inserts or replaces the asset in the sounds container
             *  for future use.
             *  @param name The **name** of the sound asset (**not** the resource file path).
             *  @returns Loaded sound.
             */
            Sound LoadSound(const std::string &name);
            /*! @brief Load font by name.
             *  @details Loads a font asset from a resource file (the
             *  directory of which is determined by the *pathLayout*), and
             *  either inserts or replaces the asset in the fonts container
             *  for future use.
             *  @param name The **name** of the font asset (**not** the resource file path).
             *  @returns Loaded font.
             */
            Font LoadFont(const std::string &name);
            /// @}


            /** @name Unloading Individual Assets
             *  @details Use these functions to unload *individual* assets
             *  directly.
             *  @param name The name of the asset you wish to unload.
             *  @param erase Whether or not to remove from asset containers.
             *  @param unloadTexture Whether or not to unload the associated texture.
             */
            /// @{
            /*! @brief Unload texture by name.
             *  @details Unloads the GPU texture data of a texture asset, and
             *  (by default) erases it from the textures container.
             *  @param name The name of the texture asset.
             *  @param erase Whether or not to erase the asset from the textures container.
             */
            void UnloadTexture(const std::string &name, const bool erase = true);
            /*! @brief Unload sprite by name.
             *  @details Clears sprite data in memory and deletes the pointer.
             *  By default, will unload the associated texture, and erase the
             *  sprite from the sprites container.
             *  @param name The name of the tileset asset.
             *  @param unloadTexture Whether or not to erase the associated texture.
             *  @param erase Whether or not to erase the asset from the sprites container.
             */
            void UnloadSprite(const std::string &name, const bool unloadTexture = true, const bool erase = true);
            /*! @brief Unload tileset by name.
             *  @details Clears tileset data in memory. By default, will unload
             *  the associated texture, and erase the tileset from the tilesets
             *  container.
             *  @param name The name of the tileset asset.
             *  @param unloadTexture Whether or not to erase the associated texture.
             *  @param erase Whether or not to erase the tileset from the tilesets container.
             */
            void UnloadTileset(const std::string &name, const bool unloadTexture = true, const bool erase = true);
            /*! @brief Unload sound by name.
             *  @details Clears the audio data in memory. By default, will
             *  erase the sound from the sounds container.
             *  @param name The name of the sound asset.
             *  @param erase Whether or not to erase the sound from the sounds container.
             */
            void UnloadSound(const std::string &name, const bool erase = true);
            /*! @brief Unload font by name.
             *  @details Clears the font data in memory. By default, will
             *  erase the font from the fonts container.
             *  @param name The name of the font asset.
             *  @param erase Whether or not to erase the font from the fonts container.
             */
            void UnloadFont(const std::string &name, const bool erase = true);
            /// @}


            /** @name Unloading Multiple Assets
             *  @details Use these functions to unload *all* assets of each
             *  type directly.
             *  @attention Will always erase assets from containers.
             *  @param unloadTextures Whether or not to unload the associated texture.
             */
            /// @{
            /*! @brief Unload all textures.
             *  @details Unloads all texture data from GPU, and erases assets
             *  from textures container.
             */
            void UnloadAllTextures();
            /*! @brief Unload all sprites.
             *  @details Unloads all sprite data from memory, erases assets
             *  from sprites container, and (by default) unloads associated
             *  textures.
             *  @param unloadTextures Unloads associated textures from GPU.
             */
            void UnloadAllSprites(const bool unloadTextures = true);
            /*! @brief Unload all tilesets.
             *  @details Unloads all tilesets data from memory, erases assets
             *  from tilesets container, and (by default) unloads associated
             *  textures.
             *  @param unloadTextures Unloads associated textures from GPU.
             */
            void UnloadAllTilesets(const bool unloadTextures = true);
            /*! @brief Unload all sounds.
             *  @details Unloads all sound data from memory, and erases
             *  assets from sounds container.
             */
            void UnloadAllSounds();
            /*! @brief Unload all fonts.
             *  @details Unloads all font data from memory, and erases assets
             *  from fonts container.
             */
            void UnloadAllFonts();
            /*! @brief Unload all assets
             *  @param unloadAllTextures Whether or not to unload texutres
             *  associated with applicable assets.
             */
            void UnloadAll(const bool unloadAllTextures = true);
            /// @}


            /*! @brief Constructor
             *  @param pathLayout The path layout where resources are to be located.
             */
            AssetManager(AssetPathLayout pathLayout = {
                "./resources/",
                "textures/",
                "sprites/",
                "tilesets/"
                "sounds/",
                "fonts/"
            });
    };
}