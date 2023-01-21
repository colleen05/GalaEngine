#include <GalaEngine/Tileset.hpp>

Rectangle GalaEngine::Tileset::GetTileRect(int tileX, int tileY) {
    return Rectangle {
        (float)(tileX * tileSize),
        (float)(tileY * tileSize),
        (float)(tileSize),
        (float)(tileSize)
    };
}

Rectangle GalaEngine::Tileset::GetTileRect(int tileID) {
    int tilesX = texture.width / tileSize;
    tilesX = (tilesX > 0) ? tilesX : 1;

    return GetTileRect(tileID % tilesX, tileID / tilesX);
}

uint16_t GalaEngine::Tileset::GetTileFlags(int tileX, int tileY) {
    int tilesX = texture.width / tileSize;
    tilesX = (tilesX > 0) ? tilesX : 1;

    return GetTileFlags((tileY * tilesX) + tileX);
}

uint16_t GalaEngine::Tileset::GetTileFlags(int tileID) {
    if(tileID < 0) return 0x0000;

    return (tileID < flags.size()) ? (flags[tileID]) : (0x0000);
}

GalaEngine::Tileset::Tileset(Texture texture, int tileSize, std::vector<uint16_t> flags) {
    if(!texture.id) return;

    this->texture = texture;
    this->tileSize = (tileSize >= 1 ? tileSize : 1);

    flags.resize((texture.width / tileSize) * (texture.height / tileSize), 0);
    this->flags = flags;
}

GalaEngine::Tileset::Tileset() : Tileset({}, 16) { }