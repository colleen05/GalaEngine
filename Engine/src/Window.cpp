#include <GalaEngine/Window.hpp>

// Initialisation & deconstruction
void GalaEngine::Window::Init() {
    InitWindow(_width, _height, _title.c_str());
    SetTargetFPS(_targetFPS);

    surface = Surface(_width, _height);

    InitAudioDevice();
}

void GalaEngine::Window::Render() {
    BeginDrawing();

    DrawTexturePro(
        surface.texture.texture,
        Rectangle {
            0.0f, (float)surface.texture.texture.height,
            (float)surface.texture.texture.width,
            -(float)surface.texture.texture.height
        },
        Rectangle {
            0.0f, 0.0f,
            (float)GetWidth(),
            (float)GetHeight()
        },
        {0.0f, 0.0f},
        0.0f,
        C_WHITE
    );

    EndDrawing();
}

void GalaEngine::Window::Exit() {
    CloseWindow();
    CloseAudioDevice();
}

// Status getters
bool GalaEngine::Window::ShouldClose() {
    return WindowShouldClose();
}

int GalaEngine::Window::GetWidth() {
    return GetScreenWidth();
}

int GalaEngine::Window::GetHeight() {
    return GetScreenHeight();
}

// Constructors
GalaEngine::Window::Window(std::string title, int width, int height, int targeFPS) {
    _title = title;
    _width = width;
    _height = height;
    _targetFPS = targeFPS;
}

GalaEngine::Window::Window() : Window("Window", 640, 480) { }