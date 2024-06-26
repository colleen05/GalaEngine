#include <GalaEngine/AssetManager.hpp>

// Getters
Texture GalaEngine::AssetManager::GetTexture(const std::string &name) {
    if(textures.find(name) != textures.end()) return textures[name];
    return LoadTexture(name);
}

GalaEngine::Sprite *GalaEngine::AssetManager::GetSprite(const std::string &name) {
    if(sprites.find(name) != sprites.end()) return sprites[name];
    return LoadSprite(name);
}

GalaEngine::Tileset GalaEngine::AssetManager::GetTileset(const std::string &name) {
    if(tilesets.find(name) != tilesets.end()) return tilesets[name];
    return LoadTileset(name);
}

GalaEngine::NSlice *GalaEngine::AssetManager::GetNSlice(const std::string &name) {
    if(nslices.find(name) != nslices.end()) return nslices[name];
    return LoadNSLice(name);
}

Sound GalaEngine::AssetManager::GetSound(const std::string &name) {
    if(sounds.find(name) != sounds.end()) return sounds[name];
    return LoadSound(name);
}

GalaEngine::Font *GalaEngine::AssetManager::GetFont(const std::string &name) {
    if(fonts.find(name) != fonts.end()) return fonts[name];
    return LoadFont(name);
}

// Loading
Texture GalaEngine::AssetManager::LoadTexture(const std::string &name) {
    Texture tex = Gres::LoadTexture(pathLayout.base + "/" + pathLayout.textures + "/" + name + ".gres");

    if(tex.id == 0) {
        ::UnloadTexture(tex);
        tex = LoadTextureFromImage(Data::MissingTextureImg);
    }

    if(textures.find(name) != textures.end()) ::UnloadTexture(textures[name]);
    textures.insert_or_assign(name, tex);

    return tex;
}

GalaEngine::Sprite *GalaEngine::AssetManager::LoadSprite(const std::string &name) {
    Sprite *sprite = new Sprite(Gres::LoadSprite(pathLayout.base + "/" + pathLayout.sprites + "/" + name + ".gres"));

    if(sprites.find(name) != sprites.end()) UnloadSprite(name);
    sprites.insert_or_assign(name, sprite);

    return sprite;
}

GalaEngine::Tileset GalaEngine::AssetManager::LoadTileset(const std::string &name) {
    Tileset ts = Gres::LoadTileset(pathLayout.base + "/" + pathLayout.tilesets + "/" + name + ".gres");

    if(tilesets.find(name) != tilesets.end()) UnloadTileset(name);
    tilesets.insert_or_assign(name, ts);

    return ts;
}

GalaEngine::NSlice *GalaEngine::AssetManager::LoadNSLice(const std::string &name) {
    NSlice *nslice = new NSlice(Gres::LoadNSlice(pathLayout.base + "/" + pathLayout.nslices + "/" + name + ".gres"));

    if(nslices.find(name) != nslices.end()) UnloadNSlice(name);
    nslices.insert_or_assign(name, nslice);

    return nslice;
}

Sound GalaEngine::AssetManager::LoadSound(const std::string &name) {
    Sound snd = Gres::LoadSound(pathLayout.base + "/" + pathLayout.sounds + "/" + name + ".gres");

    if(sounds.find(name) != sounds.end()) ::UnloadSound(sounds[name]);
    sounds.insert_or_assign(name, snd);

    return snd;
}

GalaEngine::Font *GalaEngine::AssetManager::LoadFont(const std::string &name) {
    Font *fnt = new Font(Gres::LoadFont(pathLayout.base + "/" + pathLayout.fonts + "/" + name + ".gres"));

    if(fonts.find(name) != fonts.end()) fonts[name]->ClearCache();
    fonts.insert_or_assign(name, fnt);

    return fnt;
}

// Unloading
void GalaEngine::AssetManager::UnloadTexture(const std::string &name, const bool erase) {
    if(textures.find(name) == textures.end()) return;

    ::UnloadTexture(textures[name]);
    if(erase) textures.erase(name);
}

void GalaEngine::AssetManager::UnloadSprite(const std::string &name, const bool unloadTexture, const bool erase) {
    if(sprites.find(name) == sprites.end()) return;

    if(unloadTexture) ::UnloadTexture(sprites[name]->texture);
    delete sprites[name];
    if(erase) sprites.erase(name);
}

void GalaEngine::AssetManager::UnloadTileset(const std::string &name, const bool unloadTexture, const bool erase) {
    if(tilesets.find(name) == tilesets.end()) return;

    if(unloadTexture) ::UnloadTexture(tilesets[name].texture);
    
    if(erase) tilesets.erase(name);
    else      tilesets[name] = Tileset();
}

void GalaEngine::AssetManager::UnloadNSlice(const std::string &name, const bool unloadTexture, const bool erase) {
    if(nslices.find(name) == nslices.end()) return;

    if(unloadTexture) ::UnloadTexture(nslices[name]->texture);
    delete nslices[name];
    if(erase) nslices.erase(name);
}

void GalaEngine::AssetManager::UnloadSound(const std::string &name, const bool erase) {
    if(sounds.find(name) == sounds.end()) return;

    ::UnloadSound(sounds[name]);
    if(erase) sounds.erase(name);
}

void GalaEngine::AssetManager::UnloadFont(const std::string &name, const bool erase) {
    if(fonts.find(name) == fonts.end()) return;

    fonts[name]->ClearCache();
    delete fonts[name];
    if(erase) fonts.erase(name);
}

void GalaEngine::AssetManager::UnloadAllTextures() {
    for(auto &t : textures) UnloadTexture(t.first, false);
    textures.clear();
}

void GalaEngine::AssetManager::UnloadAllSprites(const bool unloadTextures) {
    for(auto &s : sprites) UnloadSprite(s.first, unloadTextures, false);
    sprites.clear();
}

void GalaEngine::AssetManager::UnloadAllTilesets(const bool unloadTextures) {
    for(auto &t : tilesets) UnloadTileset(t.first, unloadTextures, false);
    tilesets.clear();
}

void GalaEngine::AssetManager::UnloadAllNSlices(const bool unloadTextures) {
    for(auto &s : nslices) UnloadNSlice(s.first, unloadTextures, false);
    nslices.clear();
}

void GalaEngine::AssetManager::UnloadAllSounds() {
    for(auto &s : sounds) UnloadSound(s.first, false);
    sounds.clear();
}

void GalaEngine::AssetManager::UnloadAllFonts() {
    for(auto &f : fonts) UnloadFont(f.first, false);
    fonts.clear();
}

void GalaEngine::AssetManager::UnloadAll(const bool unloadAllTextures) {
    UnloadAllTextures();
    UnloadAllSprites(unloadAllTextures);
    UnloadAllTilesets(unloadAllTextures);
    UnloadAllNSlices(unloadAllTextures);
    UnloadAllSounds();
    UnloadAllFonts();
}

// Constructor
GalaEngine::AssetManager::AssetManager(AssetPathLayout pathLayout) {
    this->pathLayout = pathLayout;
}