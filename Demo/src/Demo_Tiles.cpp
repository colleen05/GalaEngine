#include <Demo_Tiles.hpp>

// Game class overrides
void Demo_Tiles::OnLoad() {
    // Add background layer
    auto bgLayer = scene->AddBackgroundLayer(assets->GetTexture("bg_water"));
    bgLayer->scrollSpeed = {16.0f, 16.0f};

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

    // Add flags view layer
    lay_flagView = new GalaEngine::Layer(1024, 576, C_CLEAR);
    lay_flagView->blendColour = C_WHITE;
    scene->PushLayer(lay_flagView);
}

void Demo_Tiles::OnDraw() {
    // Draw grid & flags
    DrawTileGrid();
    DrawTileFlags();

    // Draw sidebar
    window->surface.DrawRectangle(0, 0, sidebarWidth, 576, {0x00, 0x00, 0x00, 0xdd});

    // Handle edit mode.
    if(editMode == EditMode::PlaceTiles) {
        GUI_LayerToggle(16, 16);
        GUI_BrushPreview(16, 128);
        GUI_FlagsToggle(384, 464);
        GUI_GridToggle(384, 512);
        GUI_ViewSelector(16, 472);
    }else {
        GUI_Picker();
    }
}

void Demo_Tiles::OnUpdate() {
    // Controls.
    if(IsKeyPressed(KEY_GRAVE)) {
        viewFlags = !viewFlags;
    }else if(IsKeyPressed(KEY_TAB)) {
        targetLayer =
            (targetLayer == EditLayer::Background) ?
            EditLayer::Foreground :
            EditLayer::Background;
    }

    // Layer visibility.
    lay_bgTiles->blendColour = viewBackgroundTiles ? C_WHITE : C_CLEAR;
    lay_fgTiles->blendColour = viewForegroundTiles ? C_WHITE : C_CLEAR;

    // Camera
    scene->mainCamera.position = (editMode == EditMode::PlaceTiles) ?
        Vector2 {0.0f, 0.0f} :
        Vector2 {-128.0f, 0.0f};

    // Update brush
    brushTile += GetMouseWheelMove();
    brushTile = brushTile % 64;

    // Update selection
    const int prevSelectionX = selectionX;
    const int prevSelectionY = selectionY;

    const Vector2 mousePosition = GetMousePosition();
    selectionX = (mousePosition.x - sidebarWidth) / tileSize;
    selectionY = mousePosition.y / tileSize;

    const bool selectionChanged = (prevSelectionX != selectionX) || (prevSelectionY != selectionY);

    selectionInBounds =
        (mousePosition.x >= sidebarWidth) &&
        (selectionX == Clamp(selectionX, 0, tilemapWidth - 1)) &&
        (selectionY == Clamp(selectionY, 0, tilemapHeight - 1));

    // Handle edit mode.
    if(editMode == EditMode::PlaceTiles) {
        if(selectionInBounds) {
            GalaEngine::TileLayer *layer =
                (targetLayer == EditLayer::Background) ?
                lay_bgTiles : lay_fgTiles;

            const size_t brushIndexOffset = (sidebarWidth / tileSize) * (selectionY + 1);
            const size_t brushIndex       = (selectionY * tilemapWidth + selectionX) + brushIndexOffset;

            if( IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ||
                (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && selectionChanged)
            ) {
                layer->tiles[brushIndex] = brushTile;
                layer->Render();
            }else if(
                IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) ||
                (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && selectionChanged)
            ) {
                layer->tiles[brushIndex] = 0x00;
                layer->Render();
            }
        }
    }
}

void Demo_Tiles::OnUnload() {

}

// Editor
bool Demo_Tiles::GUI_Button(const std::string &text, const int x, const int y, const int w, const int h, const bool highlighted) {
    const bool hovered = CheckCollisionPointRec(
        GetMousePosition(),
        (Rectangle) {
            (float)x, (float)y,
            (float)w, (float)h
        }
    );

    window->surface.DrawRectangleRounded(
        x, y, w, h, 4.0f,
        highlighted ? C_GREY :
            (hovered ? C_GREY : C_DKGREY)
    );

    window->surface.DrawText(text, x + 8, y + 6, 20, C_WHITE);

    return hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void Demo_Tiles::GUI_Picker() {
    // Draw background
    window->surface.DrawRectangle(0, 0, 1024, 576, {0x00, 0x00, 0x00, 0x7f});
    window->surface.DrawRectangleRounded(0, 0, 576, 576, 8.0f, C_BLACK);
    
    // Header
    if(GUI_Button("<", 32, 12, 28, 28) || IsKeyPressed(KEY_ESCAPE)) {
        editMode = EditMode::PlaceTiles;
    }

    window->surface.DrawText("Tiles", 68, 16, 20, C_WHITE);

    // Tileset
    auto ts = assets->GetTileset("environment");
    
    window->surface.DrawRectangle(32, 48, 512, 512, {0x11, 0x11, 0x11, 0xff});
    window->surface.DrawTexture(ts.texture, 32, 48);
    window->surface.DrawRectangle(32, 48, 512, 512, C_WHITE, true, -1.0f);

    // Grid
    if(viewGrid) {
        // Draw vertical lines.
        for(int i = 0; i < 8; i++) {
            window->surface.DrawLine(
                32 + (tileSize * i), 48,
                32 + (tileSize * i), 48 + 512,
                {0xff, 0xff, 0xff, 0x33}
            );
        }

        // Draw horizontal lines.
        for(int i = 0; i < 8; i++) {
            window->surface.DrawLine(
                32, 48 + (tileSize * i),
                32 + 512, 48 + (tileSize * i),
                {0xff, 0xff, 0xff, 0x33}
            );
        }
    }

    // Selection
    const Vector2 mousePos = GetMousePosition();

    const int setSelectionX = Clamp((mousePos.x - 32) / 64, 0, 7);
    const int setSelectionY = Clamp((mousePos.y - 48) / 64, 0, 7);
    const int hoveredTile   = setSelectionY * 8 + setSelectionX;

    if( CheckCollisionPointRec(mousePos, (Rectangle) {32.0f, 48.0f, 512.0f, 512.0f}) &&
        IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
    ) {
        brushTile = hoveredTile;
    }

    // Draw highlights
    const int brushX = brushTile % 8;
    const int brushY = brushTile / 8;
    window->surface.DrawRectangle(
        32 + brushX * 64,
        48 + brushY * 64,
        64, 64,
        {0xff, 0x00, 0x00, 0x88}
    );

    window->surface.DrawRectangle(
        32 + setSelectionX * 64,
        48 + setSelectionY * 64,
        64, 64,
        {0xff, 0x00, 0x00, 0x33}
    );
}

void Demo_Tiles::GUI_BrushPreview(const int x, const int y) {
    const bool hovered = CheckCollisionPointRec(
        GetMousePosition(),
        (Rectangle) {
            (float)x, (float)y + 32.0f,
            (float)tileSize, (float)tileSize
        }
    );

    // Draw text
    window->surface.DrawText("Tile Brush", x, y, 20, C_WHITE);

    // Draw brush tile
    auto ts = assets->GetTileset("environment");
    window->surface.DrawTexture(
        ts.texture,
        ts.GetTileRect(brushTile),
        (Rectangle) {
            (float)x, (float)y + 32.0f,
            (float)tileSize, (float)tileSize
        }
    );

    // Outline
    if(hovered)
        window->surface.DrawRectangle(x, y + 32.0f, tileSize, tileSize, {0xff, 0xff, 0xff, 0x55});

    window->surface.DrawRectangle(x, y + 32.0f, tileSize, tileSize, C_WHITE, true, 1.0f);

    // Draw info
    window->surface.DrawText("Tile: " + std::to_string(brushTile), x + 72, y + 32.0f, 20, C_WHITE);

    // Open picker if tile clicked
    if(hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        editMode = EditMode::PickTiles;
}

void Demo_Tiles::GUI_LayerToggle(const int x, const int y) {
    // Draw label
    window->surface.DrawText("Target Layer", x, y, 20, C_WHITE);

    // Do buttons
    if(GUI_Button("Background", x,  y + 32, 200, 32, targetLayer == EditLayer::Background))
        targetLayer = EditLayer::Background;

    if(GUI_Button("Foreground", x + 216, y + 32, 200, 32, targetLayer == EditLayer::Foreground))
        targetLayer = EditLayer::Foreground;
}

void Demo_Tiles::GUI_FlagsToggle(const int x, const int y) {
    const bool hovered = CheckCollisionPointRec(
        GetMousePosition(),
        (Rectangle) {
            (float)x, (float)y,
            40.0f, 40.0f
        }
    );
    
    if(hovered) {
        window->surface.DrawRectangleRounded(x, y, 40, 40, 4.0f, C_DKGREY);

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            viewFlags = !viewFlags;
        }
    }

    window->surface.DrawSprite(*assets->GetSprite("ui_tiles_flags"), viewFlags ? 1 : 0, x + 4, y + 4);
}

void Demo_Tiles::GUI_GridToggle(const int x, const int y) {
    const bool hovered = CheckCollisionPointRec(
        GetMousePosition(),
        (Rectangle) {
            (float)x, (float)y,
            40.0f, 40.0f
        }
    );
    
    if(hovered) {
        window->surface.DrawRectangleRounded(x, y, 40, 40, 4.0f, C_DKGREY);

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            viewGrid = !viewGrid;
        }
    }

    window->surface.DrawSprite(*assets->GetSprite("ui_tiles_grid"), viewGrid ? 1 : 0, x + 4, y + 4);
}

void Demo_Tiles::GUI_ViewSelector(const int x, const int y) {
    // Label
    window->surface.DrawText("Layer Visibility", x, y, 20, C_WHITE);

    // Icons
    for(int i = 0; i < 4; i++) {
        bool iconLit = false;

        if(CheckCollisionPointRec(
            GetMousePosition(),
            (Rectangle) {
                x + (64.0f * i), y + 24.0f,
                64.0f, 64.0f
            }
        )) {
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                switch(i) {
                    case 0:
                        viewBackgroundTiles = false;
                        viewForegroundTiles = false;
                        break;
                    case 1:
                        viewBackgroundTiles = true;
                        viewForegroundTiles = false;
                        break;
                    case 2:
                        viewBackgroundTiles = false;
                        viewForegroundTiles = true;
                        break;
                    case 3:
                        viewBackgroundTiles = true;
                        viewForegroundTiles = true;
                        break;
                }
            }

            iconLit = true;
        }else {
            switch(i) {
                case 0: iconLit = (!viewBackgroundTiles) && (!viewForegroundTiles); break;
                case 1: iconLit = (viewBackgroundTiles)  && (!viewForegroundTiles); break;
                case 2: iconLit = (!viewBackgroundTiles) && (viewForegroundTiles);  break;
                case 3: iconLit = (viewBackgroundTiles)  && (viewForegroundTiles);  break;
            }
        }

        window->surface.DrawSprite(
            *(assets->GetSprite("ui_tiles_views")), i,
            x + (64 * i), y + 24, 1.0f, 1.0f,
            0.0f,
            iconLit ?
                (GalaEngine::Colour) {0xff, 0xff, 0xff, 0xff} :
                (GalaEngine::Colour) {0xff, 0xff, 0xff, 0x7f}
        );
    }
}

void Demo_Tiles::DrawTileGrid() {
    if(viewGrid) {
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
    }

    // Draw brush
    if( (editMode == EditMode::PickTiles) ||
        (!selectionInBounds)
    ) return;

    auto ts = assets->GetTileset("environment");
    window->surface.DrawTexture(
        ts.texture,
        ts.GetTileRect(brushTile),
        (Rectangle) {
            (float)(sidebarWidth + (tileSize * selectionX)),
            (float)(tileSize * selectionY),
            (float)tileSize, (float)tileSize,
        },
        {0xff, 0xff, 0xff, 0x55}
    );
}

void Demo_Tiles::DrawTileFlags() {
    lay_flagView->surface->Clear();
    if(!viewFlags) return;
    
    for(int i = 0; i < 1024; i += tileSize) {
        for(int j = 0; j < 576; j += tileSize) {
            const bool bgTileSolid = (lay_bgTiles->GetTileFlags(i, j) > 0);
            const bool fgTileSolid = (lay_fgTiles->GetTileFlags(i, j) > 0);

            if(bgTileSolid && viewBackgroundTiles)
                lay_flagView->surface->DrawRectangle(i, j, 64, 64, {0xff, 0x00, 0x00, 0x88});

            if(fgTileSolid && viewForegroundTiles)
                lay_flagView->surface->DrawRectangle(i, j, 64, 64, {0xff, 0x00, 0x00, 0x88});
        }
    }
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
            "nslices/",
            "sounds/",
            "fonts/"
        }
    }
) {}