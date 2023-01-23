#include <GalaEngine/AssetManager.hpp>

// Getters
Texture GalaEngine::AssetManager::GetTexture(std::string name) {
    if(textures.count(name)) return textures[name];
    return LoadTexture(name);
}

GalaEngine::Sprite *GalaEngine::AssetManager::GetSprite(std::string name) {
    if(sprites.count(name)) return sprites[name];
    return LoadSprite(name);
}

GalaEngine::Tileset GalaEngine::AssetManager::GetTileset(std::string name) {
    if(tilesets.count(name)) return tilesets[name];
    return LoadTileset(name);
}

Sound GalaEngine::AssetManager::GetSound(std::string name) {
    if(sounds.count(name)) return sounds[name];
    return LoadSound(name);
}

Font GalaEngine::AssetManager::GetFont(std::string name) {
    if(fonts.count(name)) return fonts[name];
    return LoadFont(name);
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

GalaEngine::Tileset GalaEngine::AssetManager::LoadTileset(std::string name) {
    Tileset ts = Gres::LoadTileset(pathLayout.base + "/" + pathLayout.tilesets + "/" + name + ".gres");

    if(tilesets.count(name)) UnloadTileset(name);
    tilesets.insert_or_assign(name, ts);

    return ts;
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
void GalaEngine::AssetManager::UnloadTexture(std::string name, bool erase) {
    if(!textures.count(name)) return;

    ::UnloadTexture(textures[name]);
    if(erase) textures.erase(name);
}

void GalaEngine::AssetManager::UnloadSprite(std::string name, bool unloadTexture, bool erase) {
    if(!sprites.count(name)) return;

    if(unloadTexture) ::UnloadTexture(sprites[name]->texture);
    delete sprites[name];
    if(erase) sprites.erase(name);
}

void GalaEngine::AssetManager::UnloadTileset(std::string name, bool unloadTexture, bool erase) {
    if(!tilesets.count(name)) return;

    if(unloadTexture) ::UnloadTexture(tilesets[name].texture);
    if(erase) tilesets.erase(name);
}

void GalaEngine::AssetManager::UnloadSound(std::string name, bool erase) {
    if(!sounds.count(name)) return;

    ::UnloadSound(sounds[name]);
    if(erase) sounds.erase(name);
}

void GalaEngine::AssetManager::UnloadFont(std::string name, bool erase) {
    if(!fonts.count(name)) return;

    ::UnloadFont(fonts[name]);
    if(erase) fonts.erase(name);
}

void GalaEngine::AssetManager::UnloadAllTextures() {
    for(auto &t : textures) UnloadTexture(t.first, false);
    textures.clear();
}

void GalaEngine::AssetManager::UnloadAllSprites(bool unloadTextures) {
    for(auto &s : sprites) UnloadSprite(s.first, unloadTextures, false);
    sprites.clear();
}

void GalaEngine::AssetManager::UnloadAllTilesets(bool unloadTextures) {
    for(auto &t : tilesets) UnloadTileset(t.first, unloadTextures, false);
    tilesets.clear();
}

void GalaEngine::AssetManager::UnloadAllSounds() {
    for(auto &s : sounds) UnloadSound(s.first, false);
    tilesets.clear();
}

void GalaEngine::AssetManager::UnloadAllFonts() {
    for(auto &f : fonts) UnloadFont(f.first, false);
    fonts.clear();
}

void GalaEngine::AssetManager::UnloadAll(bool unloadAllTextures) {
    UnloadAllTextures();
    UnloadAllSprites(unloadAllTextures);
    UnloadAllTilesets(unloadAllTextures);
    UnloadAllSounds();
    UnloadAllFonts();
}

// Constructor
GalaEngine::AssetManager::AssetManager(AssetPathLayout pathLayout) {
    this->pathLayout = pathLayout;
}