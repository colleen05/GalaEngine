#include <Demo_Assets.hpp>

// Game class overrides
void Demo_Assets::OnLoad() {
    
}

void Demo_Assets::OnDraw() {
    // Draw Background
    scene->targetSurface->Clear({0x18, 0x18, 0x18, 0xff});

    // Draw view
    switch(currentView) {
        case View::Loaded:      View_Loaded();      break;
        case View::Available:   View_Available();   break;
    }

    // Draw title bar
    GUI_TitleBar();

    // Cursor
    SetMouseCursor(mouseCursor);
    mouseCursor = MOUSE_CURSOR_DEFAULT;
}

void Demo_Assets::OnUpdate() {
    scroll -= GetMouseWheelMove() * 64.0f;
    scroll = Clamp(scroll, 0.0f, scrollLimit);
}

void Demo_Assets::OnUnload() {

}

// GUI Components
void Demo_Assets::GUI_TitleBar() {
    // Panel
    scene->targetSurface->DrawRectangle(0, 0, 1280, 64, {0x22, 0x22, 0x22, 0xff});

    // Title Text
    std::string titleBarText = "";
    const int loadedAssetCount =
        assets->textures.size() +
        assets->sprites.size() +
        assets->tilesets.size() +
        assets->sounds.size() +
        assets->fonts.size();

    switch(currentView) {
        case View::Loaded:    titleBarText = "Loaded Assets (" + std::to_string(loadedAssetCount) + ")";    break;
        case View::Available: titleBarText = "Available Assets (" + std::to_string(availableAssetsCount) + ")"; break;
    }

    scene->targetSurface->DrawText(titleBarText, (currentView == View::Loaded) ? 32 : 64, 24, 20);

    // Back button
    if(currentView == View::Loaded) return;

    bool hovered = CheckCollisionPointCircle(GetMousePosition(), {32.0f, 32.0f}, 24.0f);

    if(hovered) mouseCursor = MOUSE_CURSOR_POINTING_HAND;

    scene->targetSurface->DrawCircle(
        32, 32, 24,
        hovered ?
            GalaEngine::Colour {0xff, 0xff, 0xff, 0x22} :
            GalaEngine::Colour {0xff, 0xff, 0xff, 0x00}
    );

    scene->targetSurface->DrawTriangle(
        32 - 14, 32,
        32 + 10, 32 + 12,
        32 + 10, 32 - 12,
        GalaEngine::Colour {0xbb, 0xbb, 0xbb, 0xff}
    );

    // Back
    if(hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        currentView = View::Loaded;
    }
}

bool Demo_Assets::GUI_Button(const std::string &text, const int x, const int y, const int width, const int height, const GalaEngine::Colour colour) {
    bool hovered = CheckCollisionPointRec(
        GetMousePosition(),
        Rectangle {(float)x, (float)y, (float)width, (float)height}
    );

    if(hovered) mouseCursor = MOUSE_CURSOR_POINTING_HAND;

    // Draw background
    scene->targetSurface->DrawRectangleRounded(
        x, y, width, height, 8.0f,
        GalaEngine::Colour {colour.r, colour.g, colour.b, hovered ? (uint8_t)0x88 : (uint8_t)0x55}
    );

    // Draw text
    scene->targetSurface->DrawText(text, x + 8, y + 8, 20, {0xff, 0xff, 0xff, 0xff});

    return (hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
}

bool Demo_Assets::GUI_TextureCard(const int x, const int y, const std::string &resName) {
    bool hovered = CheckCollisionPointRec(
        GetMousePosition(),
        Rectangle {(float)x, (float)y, 160.0f, 192.0f}    
    );

    if(hovered) mouseCursor = MOUSE_CURSOR_POINTING_HAND;

    // Background
    scene->targetSurface->DrawRectangleRounded(
        x, y, 160, 192, 8.0f,
        GalaEngine::Colour {
            textureCardColour.r,
            textureCardColour.g,
            textureCardColour.b,
            hovered ? (uint8_t)0xdd : (uint8_t)0xaa
        }
    );

    // Draw texture
    scene->targetSurface->DrawRectangle(x + 16, y + 16, 128.0f, 128.0f, {0x00, 0x00, 0x00, 0xaa});

    const auto &resTexture = assets->GetTexture(resName);
    float smallLength = (resTexture.width > resTexture.height) ? resTexture.height : resTexture.width;
    scene->targetSurface->DrawTexture(
        resTexture,
        showWholeTexture ?
            ((Rectangle) {0.0f, 0.0f, (float)resTexture.width, (float)resTexture.height}) :
            ((Rectangle) {0.0f, 0.0f, smallLength, smallLength}),
        (Rectangle) {(float)x + 16.0f, (float)y + 16.0f, 128.0f, 128.0f}
    );

    // Draw name
    scene->targetSurface->DrawText("Texture\n" + resName, x + 16, y + 152, 10);

    return (hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
}

bool Demo_Assets::GUI_SpriteCard(const int x, const int y, const std::string &resName) {
    bool hovered = CheckCollisionPointRec(
        GetMousePosition(),
        Rectangle {(float)x, (float)y, 160.0f, 192.0f}    
    );

    if(hovered) mouseCursor = MOUSE_CURSOR_POINTING_HAND;

    // Background
    scene->targetSurface->DrawRectangleRounded(
        x, y, 160, 192, 8.0f,
        GalaEngine::Colour {
            spriteCardColour.r,
            spriteCardColour.g,
            spriteCardColour.b,
            hovered ? (uint8_t)0xdd : (uint8_t)0xaa
        }
    );

    // Draw texture
    scene->targetSurface->DrawRectangle(x + 16, y + 16, 128.0f, 128.0f, {0x00, 0x00, 0x00, 0xaa});

    const auto &resTexture = assets->GetSprite(resName)->texture;
    const auto &frameRecs  = assets->GetSprite(resName)->frameRects;
    scene->targetSurface->DrawTexture(
        resTexture,
        showWholeSprite ?
            ((Rectangle){0.0f, 0.0f, (float)resTexture.width, (float)resTexture.height}) :
            (frameRecs[(int)(GetTime() * 2.0f) % frameRecs.size()]),
        (Rectangle) {(float)x + 16.0f, (float)y + 16.0f, 128.0f, 128.0f}
    );

    // Draw name
    scene->targetSurface->DrawText("Sprite\n" + resName, x + 16, y + 152, 10);

    return (hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
}

bool Demo_Assets::GUI_TilesetCard(const int x, const int y, const std::string &resName) {
    bool hovered = CheckCollisionPointRec(
        GetMousePosition(),
        Rectangle {(float)x, (float)y, 160.0f, 192.0f}    
    );

    if(hovered) mouseCursor = MOUSE_CURSOR_POINTING_HAND;

    // Background
    scene->targetSurface->DrawRectangleRounded(
        x, y, 160, 192, 8.0f,
        GalaEngine::Colour {
            tilesetCardColour.r,
            tilesetCardColour.g,
            tilesetCardColour.b,
            hovered ? (uint8_t)0xdd : (uint8_t)0xaa
        }
    );

    // Draw texture
    scene->targetSurface->DrawRectangle(x + 16, y + 16, 128.0f, 128.0f, {0x00, 0x00, 0x00, 0xaa});

    const auto &resTexture = assets->GetTileset(resName).texture;
    scene->targetSurface->DrawTexture(
        resTexture,
        (Rectangle) {0.0f, 0.0f, (float)resTexture.width, (float)resTexture.height},
        (Rectangle) {(float)x + 16.0f, (float)y + 16.0f, 128.0f, 128.0f}
    );

    // Draw name
    scene->targetSurface->DrawText("Tileset\n" + resName, x + 16, y + 152, 10);

    return (hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
}

bool Demo_Assets::GUI_SoundCard(const int x, const int y, const std::string &resName) {
    bool hovered = CheckCollisionPointRec(
        GetMousePosition(),
        Rectangle {(float)x, (float)y, 160.0f, 192.0f}    
    );

    if(hovered) mouseCursor = MOUSE_CURSOR_POINTING_HAND;

    // Background
    scene->targetSurface->DrawRectangleRounded(
        x, y, 160, 192, 8.0f,
        GalaEngine::Colour {
            soundCardColour.r,
            soundCardColour.g,
            soundCardColour.b,
            hovered ? (uint8_t)0xdd : (uint8_t)0xaa
        }
    );

    // Draw preview
    scene->targetSurface->DrawText("sound", x + 20, y + 64, 40, {0x00, 0xaa, 0xdd, 0xff});

    // Draw name
    scene->targetSurface->DrawText("Sound\n" + resName, x + 16, y + 152, 10);

    return (hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
}

bool Demo_Assets::GUI_FontCard(const int x, const int y, const std::string &resName) {
    bool hovered = CheckCollisionPointRec(
        GetMousePosition(),
        Rectangle {(float)x, (float)y, 160.0f, 192.0f}    
    );

    if(hovered) mouseCursor = MOUSE_CURSOR_POINTING_HAND;

    // Background
    scene->targetSurface->DrawRectangleRounded(
        x, y, 160, 192, 8.0f,
        GalaEngine::Colour {
            fontCardColour.r,
            fontCardColour.g,
            fontCardColour.b,
            hovered ? (uint8_t)0xdd : (uint8_t)0xaa
        }
    );

    // Draw preview
    scene->targetSurface->DrawText(assets->GetFont(resName), "Abcde\n123.!?", x + 16, y + 16, 40, C_WHITE);

    // Draw name
    scene->targetSurface->DrawText("Font\n" + resName, x + 16, y + 152, 10);

    return (hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
}

// Views
void Demo_Assets::View_Loaded() {
    // Cards
    int card = 0;

    for(auto &t : assets->textures) {
        const int cardRow = card / 7;
        const int cardCol = card % 7;
        if(GUI_TextureCard(16 + (160 + 16) * cardCol, (132 + (192 + 16) * cardRow) - scroll, t.first)) {
            showWholeTexture = !showWholeTexture;
        }
        card++;
    }

    for(auto &s : assets->sprites) {
        const int cardRow = card / 7;
        const int cardCol = card % 7;
        if(GUI_SpriteCard(16 + (160 + 16) * cardCol, (132 + (192 + 16) * cardRow) - scroll, s.first)) {
            showWholeSprite = !showWholeSprite;
        }
        card++;
    }

    for(auto &t : assets->tilesets) {
        const int cardRow = card / 7;
        const int cardCol = card % 7;
        GUI_TilesetCard(16 + (160 + 16) * cardCol, (132 + (192 + 16) * cardRow) - scroll, t.first);
        card++;
    }

    for(auto &s : assets->sounds) {
        const int cardRow = card / 7;
        const int cardCol = card % 7;
        if(GUI_SoundCard(16 + (160 + 16) * cardCol, (132 + (192 + 16) * cardRow) - scroll, s.first)) {
            sound->Play(s.second, true);
        }
        card++;
    }

    for(auto &f : assets->fonts) {
        const int cardRow = card / 7;
        const int cardCol = card % 7;
        GUI_FontCard(16 + (160 + 16) * cardCol, (132 + (192 + 16) * cardRow) - scroll, f.first);
        card++;
    }

    scrollLimit = floor(card / 7) * (192.0f + 16.0f);

    // Buttons
    scene->targetSurface->DrawRectangle(0, 63, 1280, 68, {0x18, 0x18, 0x18, 0xff});

    const int btnWidth = (1280 - 32 - (8 * 2)) / 3; // (screen_width - borders - (spaces * space_width)) / num_buttons

    if(GUI_Button("See Available",  16 + (btnWidth + 8) * 0, 80, btnWidth, 36)) {
        scroll = 0.0f;
        currentView = View::Available;
    }

    if(GUI_Button("Load All",       16 + (btnWidth + 8) * 1, 80, btnWidth, 36)) {
        LoadAllResources();
    }

    if(GUI_Button("Unload All",     16 + (btnWidth + 8) * 2, 80, btnWidth, 36)) {
        sound->StopAll();
        assets->UnloadAll();
    }
}

void Demo_Assets::View_Available() {
    int entry = 0;

    // List textures
    const std::string texturesPath = assets->pathLayout.base + assets->pathLayout.textures;
    for(const auto &e : std::filesystem::directory_iterator(texturesPath)) {
        if(e.is_directory() || e.is_symlink()) continue;
        const std::string resName = e.path().stem();

        const bool isLoaded = (assets->textures.find(resName) != assets->textures.end());
        const std::string btnText = std::string(isLoaded ? "[L] " : "* ") + "[texture] " + resName;

        if(GUI_Button(btnText, 16, (80 + (36 + 8) * entry) - scroll, 1280 - 32, 36, textureCardColour)) {
            if(!isLoaded) {
                assets->LoadTexture(resName);
            }else {
                if(IsKeyDown(KEY_LEFT_SHIFT))
                    assets->UnloadTexture(resName, true);
            }
        }

        entry++;
    }

    // List sprites
    const std::string spritesPath = assets->pathLayout.base + assets->pathLayout.sprites;
    for(const auto &e : std::filesystem::directory_iterator(spritesPath)) {
        if(e.is_directory() || e.is_symlink()) continue;
        const std::string resName = e.path().stem();

        const bool isLoaded = (assets->sprites.find(resName) != assets->sprites.end());
        const std::string btnText = std::string(isLoaded ? "[L] " : "* ") + "[sprite] " + resName;

        if(GUI_Button(btnText, 16, (80 + (36 + 8) * entry) - scroll, 1280 - 32, 36, spriteCardColour)) {
            if(!isLoaded) {
                assets->LoadSprite(resName);
            }else {
                if(IsKeyDown(KEY_LEFT_SHIFT))
                    assets->UnloadSprite(resName, true);
            }
        }

        entry++;
    }

    // List tilesets
    const std::string tilesetsPath = assets->pathLayout.base + assets->pathLayout.tilesets;
    for(const auto &e : std::filesystem::directory_iterator(tilesetsPath)) {
        if(e.is_directory() || e.is_symlink()) continue;
        const std::string resName = e.path().stem();

        const bool isLoaded = (assets->tilesets.find(resName) != assets->tilesets.end());
        const std::string btnText = std::string(isLoaded ? "[L] " : "* ") + "[tileset] " + resName;

        if(GUI_Button(btnText, 16, (80 + (36 + 8) * entry) - scroll, 1280 - 32, 36, tilesetCardColour)) {
            if(!isLoaded) {
                assets->LoadTileset(resName);
            }else {
                if(IsKeyDown(KEY_LEFT_SHIFT))
                    assets->UnloadTileset(resName, true);
            }
        }

        entry++;
    }

    // List sounds
    const std::string soundsPath = assets->pathLayout.base + assets->pathLayout.sounds;
    for(const auto &e : std::filesystem::directory_iterator(soundsPath)) {
        if(e.is_directory() || e.is_symlink()) continue;
        const std::string resName = e.path().stem();

        const bool isLoaded = (assets->sounds.find(resName) != assets->sounds.end());
        const std::string btnText = std::string(isLoaded ? "[L] " : "* ") + "[sound] " + resName;

        if(GUI_Button(btnText, 16, (80 + (36 + 8) * entry) - scroll, 1280 - 32, 36, soundCardColour)) {
            if(!isLoaded) {
                assets->LoadSound(resName);
            }else {
                if(IsKeyDown(KEY_LEFT_SHIFT))
                    sound->StopAll();
                    assets->UnloadSound(resName, true);
            }
        }

        entry++;
    }

    // List fonts
    const std::string fontsPath = assets->pathLayout.base + assets->pathLayout.fonts;
    for(const auto &e : std::filesystem::directory_iterator(fontsPath)) {
        if(e.is_directory() || e.is_symlink()) continue;
        const std::string resName = e.path().stem();

        const bool isLoaded = (assets->fonts.find(resName) != assets->fonts.end());
        const std::string btnText = std::string(isLoaded ? "[L] " : "* ") + "[font] " + resName;

        if(GUI_Button(btnText, 16, (80 + (36 + 8) * entry) - scroll, 1280 - 32, 36, fontCardColour)) {
            if(!isLoaded) {
                assets->LoadFont(resName);
            }else {
                if(IsKeyDown(KEY_LEFT_SHIFT))
                    assets->UnloadFont(resName, true);
            }
        }

        entry++;
    }

    availableAssetsCount = entry;
    scrollLimit = (entry - 1) * (36 + 8) + 8;
}

// Misc.
void Demo_Assets::LoadAllResources() {
    assets->UnloadAll();

    // Load textures
    const std::string texturesPath = assets->pathLayout.base + assets->pathLayout.textures;
    for(const auto &e : std::filesystem::directory_iterator(texturesPath)) {
        if(e.is_directory() || e.is_symlink()) continue;
        const std::string resName = e.path().stem();
        assets->LoadTexture(resName);
    }

    // Load sprites
    const std::string spritesPath = assets->pathLayout.base + assets->pathLayout.sprites;
    for(const auto &e : std::filesystem::directory_iterator(spritesPath)) {
        if(e.is_directory() || e.is_symlink()) continue;
        const std::string resName = e.path().stem();
        assets->LoadSprite(resName);
    }

    // Load tilesets
    const std::string tilesetsPath = assets->pathLayout.base + assets->pathLayout.tilesets;
    for(const auto &e : std::filesystem::directory_iterator(tilesetsPath)) {
        if(e.is_directory() || e.is_symlink()) continue;
        const std::string resName = e.path().stem();
        assets->LoadTileset(resName);
    }

    // Load sounds
    const std::string soundsPath = assets->pathLayout.base + assets->pathLayout.sounds;
    for(const auto &e : std::filesystem::directory_iterator(soundsPath)) {
        if(e.is_directory() || e.is_symlink()) continue;
        const std::string resName = e.path().stem();
        assets->LoadSound(resName);
    }

    // Load fonts
    const std::string fontsPath = assets->pathLayout.base + assets->pathLayout.fonts;
    for(const auto &e : std::filesystem::directory_iterator(fontsPath)) {
        if(e.is_directory() || e.is_symlink()) continue;
        const std::string resName = e.path().stem();
        assets->LoadFont(resName);
    }
}

// Constructor
Demo_Assets::Demo_Assets() : Game(
    GalaEngine::GameInfo {
        "GalaEngine Asset Management Demo (GalaEngine v" GALAENGINE_VERSION_STRING ")",
        "GalaEngine example project.",
        "Colleen (colleen05)",

        1280, 720,

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