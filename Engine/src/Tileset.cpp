#include <GalaEngine/Tileset.hpp>

Rectangle GalaEngine::Tileset::GetTileRect(int x, int y) {
    return Rectangle {
        (float)(x * tileSize),
        (float)(y * tileSize),
        (float)(tileSize),
        (float)(tileSize)
    };
}

Rectangle GalaEngine::Tileset::GetTileRect(int tileID) {
    int tilesX = texture.width / tileSize;

    return GetTileRect(tileID % tilesX, tileID / tilesX);
}

GalaEngine::Tileset::Tileset(Texture texture, int tileSize, std::vector<uint8_t> flags) {
    if(!texture.id) return;

    this->texture = texture;
    this->tileSize = tileSize;

    if(flags.size() == 0) flags = std::vector<uint8_t>((texture.width / tileSize) * (texture.height / tileSize));
    this->flags = flags;
}

GalaEngine::Tileset::Tileset() : Tileset({}, 16) { }