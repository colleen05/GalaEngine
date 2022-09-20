#include <GalaEngine/Window.hpp>

// Initialisation & deconstruction
void GalaEngine::Window::Init() {
    InitWindow(_width, _height, _title.c_str());
    SetTargetFPS(_targetFPS);

    surface = Surface(_width, _height, C_BLACK);

    InitAudioDevice();
}

// bool GalaEngine::Window::GetKeyDown(KeyboardKey key) {
//     return IsKeyDown(key);
// }

// bool GalaEngine::Window::GetKeyPressed(KeyboardKey key) {
//     return (!_keyStates[key]) && IsKeyDown(key);
// }

// bool GalaEngine::Window::GetKeyReleased(KeyboardKey key) {
//     return _keyStates[key] && (!IsKeyDown(key));
// }

// void GalaEngine::Window::UpdateInput() {
//     for(int i = 0; i < _keyStates.size(); i++) {
//         _keyStates[i] = IsKeyDown((KeyboardKey)i);
//     }
// }

void GalaEngine::Window::Render() {
    DrawTexturePro(
        surface.texture.texture,
        Rectangle {
            0.0f,
            (float)surface.texture.texture.height,
            (float)surface.texture.texture.width,
            -(float)surface.texture.texture.height
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

void GalaEngine::Window::Exit() {
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