#include <GalaEngine/Game.hpp>

void GalaEngine::Game::OnLoad   () {};
void GalaEngine::Game::OnUpdate () {};
void GalaEngine::Game::OnDraw   () {};
void GalaEngine::Game::OnUnload () {};

void GalaEngine::Game::Start() {
    window->Init();

    // Create scene and bind assets, input manager, etc..
    scene = new GalaEngine::Scene(&window->surface, _info.defaultWidth, _info.defaultHeight);
    scene->window   = window;
    scene->assets   = assets;
    scene->input    = input;
    scene->sound    = sound;

    OnLoad();

    while(!(window->ShouldClose() || _shouldEnd)) {
        // Update
        scene->Update();
        OnUpdate();
        // window->UpdateInput();

        // Drawing
        BeginDrawing();
        window->surface.Clear(C_BLACK);
        OnDraw(); // Call draw code from child class
        window->Render();
        EndDrawing();

        if(IsKeyPressed(KEY_F9)) {
            Image img_screen = LoadImageFromTexture(window->surface.renderTexture.texture);
            ExportImage(img_screen, "window_surface.png");
            UnloadImage(img_screen);
        }
    }

    OnUnload();
    window->Close();
}

void GalaEngine::Game::End() {
    _shouldEnd = true;
}

GalaEngine::Game::Game(const GameInfo info) {
    _info = info;
    window  = new GalaEngine::Window(_info.title, _info.defaultWidth, _info.defaultHeight);
    assets  = new GalaEngine::AssetManager(info.assetPaths);
    input   = new GalaEngine::InputManager();
    sound   = new GalaEngine::SoundManager();
}

GalaEngine::Game::Game() : Game(
    GameInfo {
        "GalaEngine Game",
        "Made with GalaEngine.",
        "",
        640,
        480,
        AssetPathLayout {
            "./resources/",
            "textures/",
            "sprites",
            "tilesets/",
            "sounds/",
            "fonts/"
        }
    }
) { }