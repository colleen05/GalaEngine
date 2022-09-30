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
            AssetPathLayout pathLayout;

            std::map<std::string, Texture>  textures;
            std::map<std::string, Sound>    sounds;
            std::map<std::string, Font>     fonts;

            Texture GetTexture  (std::string name);
            Sound   GetSound    (std::string name);
            Font    GetFont     (std::string name);

            void LoadTexture (std::string name, std::string path);
            void LoadSound   (std::string name, std::string path);
            void LoadFont    (std::string name, std::string path);

            void UnloadTexture  (std::string name, std::string path);
            void UnloadSound    (std::string name, std::string path);
            void UnloadFont     (std::string name, std::string path);

            void UnloadAllTextures  ();
            void UnloadAllSounds    ();
            void UnloadAllFonts     ();
            
            void UnloadAll();

            AssetManager(AssetPathLayout pathLayout = {
                "./base/",
                "./textures/",
                "./sounds/",
                "./fonts/"
            });
    };
}