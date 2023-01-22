#include <GalaEngine/AssetManager.hpp>

// Getters
Texture GalaEngine::AssetManager::GetTexture(std::string name) {
    if(textures.count(name)) return textures[name];
    return Texture {0};
}

GalaEngine::Sprite *GalaEngine::AssetManager::GetSprite(std::string name) {
    if(sprites.count(name)) return sprites[name];
    return LoadSprite(name);
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
Texture GalaEngine::AssetManager::LoadTexture(std::string name) {
    Texture tex = Gres::LoadTexture(pathLayout.base + "/" + pathLayout.textures + "/" + name + ".gres");

    if(tex.id == 0) {
        ::UnloadTexture(tex);
        tex = LoadTextureFromImage(Data::MissingTextureImg);
    }

    if(textures.count(name)) ::UnloadTexture(textures[name]);
    textures.insert_or_assign(name, tex);

    return tex;
}

GalaEngine::Sprite *GalaEngine::AssetManager::LoadSprite(std::string name) {
    Sprite *sprite = new Sprite(Gres::LoadSprite(pathLayout.base + "/" + pathLayout.sprites + "/" + name + ".gres"));

    if(sprites.count(name)) UnloadSprite(name);
    sprites.insert_or_assign(name, sprite);

    return sprite;
}

Sound GalaEngine::AssetManager::LoadSound(std::string name) {
    Sound snd = Gres::LoadSound(pathLayout.base + "/" + pathLayout.sounds + "/" + name + ".gres");

    if(sounds.count(name)) ::UnloadSound(sounds[name]);
    sounds.insert_or_assign(name, snd);

    return snd;
}

Font GalaEngine::AssetManager::LoadFont(std::string name) {
    Font fnt = Gres::LoadFont(pathLayout.base + "/" + pathLayout.fonts + "/" + name + ".gres");

    if(fonts.count(name)) ::UnloadFont(fonts[name]);
    fonts.insert_or_assign(name, fnt);

    return fnt;
}

// Unloading
void GalaEngine::AssetManager::UnloadTexture(std::string name) {
    if(!textures.count(name)) return;

    ::UnloadTexture(textures[name]);
    textures.erase(name);
}

void GalaEngine::AssetManager::UnloadSprite(std::string name, bool unloadTexture) {
    if(!sprites.count(name)) return;

    if(unloadTexture) UnloadTexture("$res:sprites/" + name);
    delete sprites[name];
    sprites.erase(name);
}

void GalaEngine::AssetManager::UnloadSound(std::string name) {
    if(!sounds.count(name)) return;

    ::UnloadSound(sounds[name]);
    sounds.erase(name);
}

void GalaEngine::AssetManager::UnloadFont(std::string name) {
    if(!fonts.count(name)) return;

    ::UnloadFont(fonts[name]);
    fonts.erase(name);
}

void GalaEngine::AssetManager::UnloadAllTextures() {
    for(auto &t : textures) UnloadTexture(t.first);
}

void GalaEngine::AssetManager::UnloadAllSprites(bool unloadTextures) {
    for(auto &s : sprites) UnloadSprite(s.first, unloadTextures);
}

void GalaEngine::AssetManager::UnloadAllSounds() {
    for(auto &s : sounds) UnloadSound(s.first);
}

void GalaEngine::AssetManager::UnloadAllFonts() {
    for(auto &f : fonts) UnloadFont(f.first);
}

void GalaEngine::AssetManager::UnloadAll(bool unloadSpriteTextures) {
    UnloadAllTextures();
    UnloadAllSprites(unloadSpriteTextures);
    UnloadAllSounds();
    UnloadAllFonts();
}

// Constructor
GalaEngine::AssetManager::AssetManager(AssetPathLayout pathLayout) {
    this->pathLayout = pathLayout;
}