#include <GalaEngine/Window.hpp>

// Initialisation & deconstruction
void GalaEngine::Window::Init() {
    InitWindow(_width, _height, _title.c_str());
    SetTargetFPS(_targetFPS);

    surface = Surface(_width, _height, C_BLACK);

    InitAudioDevice();
}

void GalaEngine::Window::Render() {
    DrawTexturePro(
        surface.renderTexture.texture,
        Rectangle {
            0.0f,
            (float)surface.renderTexture.texture.height,
            (float)surface.renderTexture.texture.width,
            -(float)surface.renderTexture.texture.height
        },
        Rectangle {
            0.0f,
            0.0f,
            (float)GetWidth(),
            (float)GetHeight()
        },
        {0.0f, 0.0f},
        0.0f,
        C_WHITE
    );
}

void GalaEngine::Window::Close() {
    surface.Destroy();
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