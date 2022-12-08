#include <GalaEngine/TileLayer.hpp>

int GalaEngine::TileLayer::GetTileIndex(int x, int y) {
    int tx = (x / tileset.tileSize) % width;
    int ty = (y / tileset.tileSize) % height;

    return (ty * width) + tx;
}

uint16_t GalaEngine::TileLayer::GetTile(int x, int y) {
    return tiles[GetTileIndex(x, y)];
}

uint16_t GalaEngine::TileLayer::GetTileFlags(int x, int y) {
    return tileset.GetTileFlags(GetTileIndex(x, y));
}

void GalaEngine::TileLayer::Render() {
    // Initialise image for map render
    Image img = GenImageColor(
        width * tileset.tileSize,
        height * tileset.tileSize,
        surface->clearColour
    );

    Image img_tiles = LoadImageFromTexture(tileset.texture);

    // Generate texture
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            ImageDraw(
                &img, img_tiles,
                tileset.GetTileRect(tiles[(y * width) + x]),
                Rectangle {
                    (float)(x * tileset.tileSize),
                    (float)(y * tileset.tileSize),
                    (float)tileset.tileSize,
                    (float)tileset.tileSize
                },
                C_WHITE
            );
        }
    }

    // Assign texture and unload image
    texture = LoadTextureFromImage(img);
    UnloadImage(img);
    UnloadImage(img_tiles);
}

void GalaEngine::TileLayer::OnStart() {
    Render();
}

void GalaEngine::TileLayer::OnUpdate() {
    
}

void GalaEngine::TileLayer::OnDraw(GalaEngine::Camera camera) {
    surface->DrawTexture(texture, 0, 0);
}

void GalaEngine::TileLayer::OnDestroy() {
    
}

GalaEngine::TileLayer::TileLayer(
    Tileset tileset, std::vector<uint16_t> tiles,
    int tilesX, int tilesY,
    Colour clearColour
): Layer(tileset.tileSize * tilesX, tileset.tileSize * tilesY, clearColour) {
    this->tileset = tileset;
    this->tiles = tiles;
    this->width = tilesX;
    this->height = tilesY;
}

GalaEngine::TileLayer::TileLayer() {

}
