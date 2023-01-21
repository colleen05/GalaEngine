#include <GalaEngine/Gres.hpp>

// Textures
Texture GalaEngine::Gres::LoadTextureData(const std::vector<uint8_t> &data) {
    // Load table
    xdt::Table gresTable;
    gresTable.Deserialise(data);

    // Checking
    if(gresTable.GetString("type") != "texture")                return {0};
    if(gresTable.GetItemType("texture") != xdt::ItemType::Raw)  return {0};

    // Decode texture
    const auto textureBytes = gresTable.GetBytes("texture");

    Image img = LoadImageFromMemory(".qoi", textureBytes.data(), textureBytes.size() * sizeof(textureBytes[0]));
    if( (img.data == NULL) ||
        (img.width == 0) ||
        (img.height == 0)
    ) return {0};

    Texture tex = LoadTextureFromImage(img);
    UnloadImage(img);
    
    return tex;
}

Texture GalaEngine::Gres::LoadTexture(const std::string &filePath) {
    std::ifstream f(filePath);

    if(!f.good()) return {0};

    return LoadTextureData(std::vector<uint8_t>(
        std::istreambuf_iterator<char>(f),
        std::istreambuf_iterator<char>()
    ));
}


// Sprites
GalaEngine::Sprite GalaEngine::Gres::LoadSpriteData(const std::vector<uint8_t> &data) {
    return {0};
}

GalaEngine::Sprite GalaEngine::Gres::LoadSprite(const std::string &filePath) {
    return {0};
}


// Tilesets
GalaEngine::Tileset GalaEngine::Gres::LoadTilesetData(const std::vector<uint8_t> &data) {
    return Tileset();
}

GalaEngine::Tileset GalaEngine::Gres::LoadTileset(const std::string &filePath) {
    return Tileset();
}


// Sounds
Sound GalaEngine::Gres::LoadSoundData(const std::vector<uint8_t> &data) {
    return {0};
}

Sound GalaEngine::Gres::LoadSound(const std::string &filePath) {
    return {0};
}


// Fonts
Font GalaEngine::Gres::LoadFontData(const std::vector<uint8_t> &data) {
    return {0};
}

Font GalaEngine::Gres::LoadFont(const std::string &filePath) {
    return {0};
}