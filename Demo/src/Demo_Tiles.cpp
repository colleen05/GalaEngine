#include <Demo_Tiles.hpp>

// Game class overrides
void Demo_Tiles::OnLoad() {
    // Add background layer
    auto bgLayer = scene->AddBackgroundLayer(assets->GetTexture("bg_water"));
    bgLayer->scrollSpeed = {16.0f, 16.0f};

    assets->LoadTileset("environment");

    // Add background tile layer
    lay_bgTiles = scene->AddTileLayer(
        assets->GetTileset("environment"),
        std::vector<uint16_t>(16 * tilemapHeight, 0x00),
        16, tilemapHeight
    );

    // Add foreground tile layer
    lay_fgTiles = scene->AddTileLayer(
        assets->GetTileset("environment"),
        std::vector<uint16_t>(16 * tilemapHeight, 0x00),
        16, tilemapHeight
    );

    for(int i = 0; i < lay_bgTiles->tiles.size(); i++) {
        lay_bgTiles->tiles[i] = GetRandomValue(0, 63);
    }

    lay_bgTiles->Render();
}

void Demo_Tiles::OnDraw() {
    // Draw sidebar.
    // window->surface.DrawRectangle(0, 0, sidebarWidth, 576, {0x33, 0x33, 0x33, 0xff});

    // Handle edit mode.
    switch(editMode) {
        case EditMode::PlaceTiles:
            break;
        case EditMode::PickTiles:
            break;
    }

    // Draw grid
    DrawTileGrid();
}

void Demo_Tiles::OnUpdate() {
    // Toggle viewing tile flags.
    if(IsKeyPressed(KEY_GRAVE)) {
        viewFlags = !viewFlags;
    }

    // Update brush
    brushTile += GetMouseWheelMove();
    if(brushTile > 64) brushTile = 0; 

    // Update selection
    const Vector2 mousePosition = GetMousePosition();
    selectionX = (mousePosition.x - sidebarWidth) / tileSize;
    selectionY = mousePosition.y / tileSize;

    // Handle edit mode.
    if(editMode == EditMode::PlaceTiles) {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            sound->Play(assets->GetSound("sfx_chime"));

            GalaEngine::TileLayer *layer =
                (targetLayer == EditLayer::Background) ?
                lay_bgTiles : lay_fgTiles;

            const size_t brushIndex = selectionY * tilemapWidth + selectionX;
            
            layer->tiles[brushIndex] = brushTile;
        }
    }
}

void Demo_Tiles::OnUnload() {

}

// Editor
void Demo_Tiles::DoPicker() {

}

void Demo_Tiles::DrawTileGrid() {
    // Draw vertical lines.
    for(int i = 0; i < tilemapWidth; i++) {
        window->surface.DrawLine(
            sidebarWidth + (tileSize * i), 0,
            sidebarWidth + (tileSize * i), 576,
            {0x00, 0x00, 0x00, 0x33}
        );
    }

    // Draw horizontal lines.
    for(int i = 0; i < tilemapHeight; i++) {
        window->surface.DrawLine(
            sidebarWidth, tileSize * i,
            1024, tileSize * i,
            {0x00, 0x00, 0x00, 0x33}
        );
    }

    // Draw brush tile
    if( (editMode == EditMode::PickTiles) ||
        (selectionX < 0)
    ) return;

    window->surface.DrawTexture(
        assets->GetTileset("environment").texture,
        (Rectangle) {
            (brushTile % 8) * 64.0f,
            (brushTile / 8) * 64.0f,
            64.0f, 64.0f
        },
        (Rectangle) {
            (float)(sidebarWidth + (tileSize * selectionX)),
            (float)(tileSize * selectionY),
            (float)tileSize, (float)tileSize,
        },
        {0xff, 0xff, 0xff, 0x55}
    );
}

// Constructor
Demo_Tiles::Demo_Tiles() : Game(
    GalaEngine::GameInfo {
        "GalaEngine Tiles Demo (GalaEngine v" GALAENGINE_VERSION_STRING ")",
        "GalaEngine example project.",
        "Colleen (colleen05)",

        1024, 576,

        GalaEngine::AssetPathLayout {
            "./resources/",
            "textures/",
            "sprites/",
            "tilesets/",
            "sounds/",
            "fonts/"
        }
    }
) {}