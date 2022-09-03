#include <GalaEngine/TileLayer.hpp>

void GalaEngine::TileLayer::OnStart() {
    // Initialise image for map render
    Image img = GenImageColor(
        width * tileset.tileSize,
        height * tileset.tileSize,
        C_CLEAR
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

void GalaEngine::TileLayer::OnUpdate() {
    
}

void GalaEngine::TileLayer::OnDraw(GalaEngine::Camera camera) {
    surface->DrawTexture(
        texture, 0, 0
    );
}

void GalaEngine::TileLayer::OnDestroy() {
    
}

GalaEngine::TileLayer::TileLayer(
    Tileset tileset, std::vector<uint16_t> tiles,
    int tilesX, int tilesY,
    int surfaceWidth, int surfaceHeight
): Layer(surfaceWidth, surfaceHeight, C_CLEAR) {
    this->tileset = tileset;
    this->tiles = tiles;
    this->width = tilesX;
    this->height = tilesY;
}

GalaEngine::TileLayer::TileLayer() {

}