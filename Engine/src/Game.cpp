#include <GalaEngine/Game.hpp>

void GalaEngine::Game::OnLoad   () {};
void GalaEngine::Game::OnUpdate () {};
void GalaEngine::Game::OnDraw   () {};
void GalaEngine::Game::OnUnload () {};

void GalaEngine::Game::Start() {
    window->Init();

    // Create scene and bind assets, input manager, etc..
    scene = new GalaEngine::Scene(&window->surface, info.defaultWidth, info.defaultHeight);
    scene->window   = window;
    scene->assets   = assets;
    scene->input    = input;
    scene->sound    = sound;
    
    scene->mainCamera.position = {0.0f, 0.0f};

    scene->mainCamera.size = Vector2 {
        (float) info.defaultWidth,
        (float) info.defaultHeight
    };

    OnLoad();

    while(!(window->ShouldClose() || _shouldEnd)) {
        // Update
        scene->Update();
        OnUpdate();
        
        if(IsKeyPressed(KEY_F11))
            window->ToggleFullscreen();

        // Drawing
        BeginDrawing();
        ClearBackground(window->surface.clearColour);
        window->surface.Clear();

        BeginBlendMode(BLEND_ALPHA);
        scene->RenderLayers();
        OnDraw(); // Call draw code from child class
        EndBlendMode();

        window->Render();
        EndDrawing();
    }

    OnUnload();
    window->Close();
}

void GalaEngine::Game::End() {
    _shouldEnd = true;
}

GalaEngine::Game::Game(const GameInfo &info) {
    this->info = info;
    window  = new GalaEngine::Window(info.title, info.defaultWidth, info.defaultHeight);
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