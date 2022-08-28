#include <GalaEngine/Game.hpp>

void GalaEngine::Game::OnLoad   () {};
void GalaEngine::Game::OnUpdate () {};
void GalaEngine::Game::OnDraw   () {};
void GalaEngine::Game::OnUnload () {};

void GalaEngine::Game::Start() {
    window->Init();

    while(!(window->ShouldClose() || _shouldEnd)) {
        // Update
        OnUpdate();

        // Drawing
        window->surface.Clear();

        BeginDrawing();
        OnDraw(); // Call draw code from child class
        EndDrawing();

        window->Render();
    }

    OnUnload();
    window->Exit();
}

void GalaEngine::Game::End() {
    _shouldEnd = true;
}

GalaEngine::Game::Game(GameInfo info) {
    _info = info;
    window = new GalaEngine::Window(_info.title, _info.defaultWidth, _info.defaultHeight);
}

GalaEngine::Game::Game() : Game(
    GameInfo {
        "GalaEngine Game",
        "GalaEngine Game",
        "",
        640, 480,
        "./res/"
    }
) { }