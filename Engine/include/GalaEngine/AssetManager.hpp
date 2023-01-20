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
            Texture GetTexture  (std::string name);
            Sprite  *GetSprite  (std::string name);
            Sound   GetSound    (std::string name);
            Font    GetFont     (std::string name);

            // Loading
            Texture LoadTexture (std::string name, std::string path);
            Sprite  *LoadSprite (std::string name, std::string path);
            Sound   LoadSound   (std::string name, std::string path);
            Font    LoadFont    (std::string name, std::string path);

            // Unloading
            void UnloadTexture  (std::string name);
            void UnloadSprite   (std::string name, bool unloadTexture = true);
            void UnloadSound    (std::string name);
            void UnloadFont     (std::string name);

            void UnloadAllTextures  ();
            void UnloadAllSprites   (bool unloadTextures = true);
            void UnloadAllSounds    ();
            void UnloadAllFonts     ();
            
            void UnloadAll(bool unloadSpriteTextures = true);

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