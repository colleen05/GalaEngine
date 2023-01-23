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
    struct AssetPathLayout {
        std::string base     = "./resources/",
                    textures = "textures/",
                    sprites  = "sprites/",
                    tilesets = "tilesets/",
                    sounds   = "sounds/",
                    fonts    = "fonts/";
    };

    class AssetManager {
        public:
            // Layout
            AssetPathLayout pathLayout;

            // Containers
            std::map<std::string, Texture>  textures;
            std::map<std::string, Sprite*>  sprites;
            std::map<std::string, Tileset>  tilesets;
            std::map<std::string, Sound>    sounds;
            std::map<std::string, Font>     fonts;

            // Getters
            Texture GetTexture  (const std::string &name);
            Sprite  *GetSprite  (const std::string &name);
            Tileset GetTileset  (const std::string &name);
            Sound   GetSound    (const std::string &name);
            Font    GetFont     (const std::string &name);

            // Loading
            Texture LoadTexture (const std::string &name);
            Sprite  *LoadSprite (const std::string &name);
            Tileset LoadTileset (const std::string &name);
            Sound   LoadSound   (const std::string &name);
            Font    LoadFont    (const std::string &name);

            // Unloading
            void UnloadTexture  (const std::string &name, const bool erase = true);
            void UnloadSprite   (const std::string &name, const bool unloadTexture = true, const bool erase = true);
            void UnloadTileset  (const std::string &name, const bool unloadTexture = true, const bool erase = true);
            void UnloadSound    (const std::string &name, const bool erase = true);
            void UnloadFont     (const std::string &name, const bool erase = true);

            void UnloadAllTextures  ();
            void UnloadAllSprites   (const bool unloadTextures = true);
            void UnloadAllTilesets  (const bool unloadTextures = true);
            void UnloadAllSounds    ();
            void UnloadAllFonts     ();
            
            void UnloadAll(const bool unloadAllTextures = true);

            // Constructor
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