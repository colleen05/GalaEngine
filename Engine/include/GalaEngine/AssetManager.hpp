// Project: GalaEngine
// File: AssetManager.hpp
// Description: Asset managing class for auto loading and unloading
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <raylib.h>
#include <string>
#include <map>

namespace GalaEngine {
    struct AssetPathLayout {
        std::string base,
                    textures,
                    sounds,
                    fonts;
    };

    class AssetManager {
        public:
            // Layout
            AssetPathLayout pathLayout;

            // Containers
            std::map<std::string, Texture>  textures;
            std::map<std::string, Sound>    sounds;
            std::map<std::string, Font>     fonts;

            // Getters
            Texture GetTexture  (std::string name);
            Sound   GetSound    (std::string name);
            Font    GetFont     (std::string name);

            // Loading
            Texture LoadTexture (std::string name, std::string path);
            Sound   LoadSound   (std::string name, std::string path);
            Font    LoadFont    (std::string name, std::string path);

            // Unloading
            void UnloadTexture  (std::string name);
            void UnloadSound    (std::string name);
            void UnloadFont     (std::string name);

            void UnloadAllTextures  ();
            void UnloadAllSounds    ();
            void UnloadAllFonts     ();
            
            void UnloadAll();

            // Constructor
            AssetManager(AssetPathLayout pathLayout = {
                "./base/",
                "./textures/",
                "./sounds/",
                "./fonts/"
            });
    };
}