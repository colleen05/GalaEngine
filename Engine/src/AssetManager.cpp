#include <GalaEngine/AssetManager.hpp>

// Getters
Texture GalaEngine::AssetManager::GetTexture(std::string name) {
    if(textures.count(name)) return textures[name];
    return Texture {0};
}

Sound GalaEngine::AssetManager::GetSound(std::string name) {
    if(sounds.count(name)) return sounds[name];
    return Sound {0};
}

Font GalaEngine::AssetManager::GetFont(std::string name) {
    if(fonts.count(name)) return fonts[name];
    return Font {0};
}

// Loading
Texture GalaEngine::AssetManager::LoadTexture(std::string name, std::string path) {
    Texture tex = ::LoadTexture(path.c_str());

    if(textures.count(name)) ::UnloadTexture(textures[name]);
    textures.insert_or_assign(name, tex);

    return tex;
}

Sound GalaEngine::AssetManager::LoadSound(std::string name, std::string path) {
    Sound snd = ::LoadSound(path.c_str());

    if(sounds.count(name)) ::UnloadSound(sounds[name]);
    sounds.insert_or_assign(name, snd);

    return snd;
}

Font GalaEngine::AssetManager::LoadFont(std::string name, std::string path) {
    Font fnt = ::LoadFont(path.c_str());

    if(fonts.count(name)) ::UnloadFont(fonts[name]);
    fonts.insert_or_assign(name, fnt);

    return fnt;
}

// Unloading
void GalaEngine::AssetManager::UnloadTexture(std::string name) {
    ::UnloadTexture(textures[name]);
    textures.erase(name);
}

void GalaEngine::AssetManager::UnloadSound(std::string name) {
    ::UnloadSound(sounds[name]);
    sounds.erase(name);
}

void GalaEngine::AssetManager::UnloadFont(std::string name) {
    ::UnloadFont(fonts[name]);
    fonts.erase(name);
}

void GalaEngine::AssetManager::UnloadAllTextures() {
    for(auto &t : textures) UnloadTexture(t.first);
}

void GalaEngine::AssetManager::UnloadAllSounds() {
    for(auto &s : sounds) UnloadSound(s.first);
}

void GalaEngine::AssetManager::UnloadAllFonts() {
    for(auto &f : fonts) UnloadFont(f.first);
}

void GalaEngine::AssetManager::UnloadAll() {
    UnloadAllTextures();
    UnloadAllSounds();
    UnloadAllFonts();
}

// Constructor
GalaEngine::AssetManager::AssetManager(AssetPathLayout pathLayout) {
    this->pathLayout = pathLayout;
}