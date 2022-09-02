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

GalaEngine::Tileset::Tileset(Texture texture, int tileSize) {
    if(!texture.id) return;

    this->texture = texture;
    this->tileSize = tileSize;
}

GalaEngine::Tileset::Tileset() : Tileset({}, 16) { }