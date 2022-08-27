#include <GalaEngine/Window.hpp>

// Initialisation & deconstruction
void GalaEngine::Window::Init() {
    InitWindow(_width, _height, _title.c_str());
    SetTargetFPS(_targetFPS);

    InitAudioDevice();
}

void GalaEngine::Window::Exit() {
    CloseWindow();
    CloseAudioDevice();
}

// Status getters
bool GalaEngine::Window::ShouldClose() {
    return WindowShouldClose();
}

// Constructors
GalaEngine::Window::Window(std::string title, int width, int height, int targeFPS) {
    _title = title;
    _width = width;
    _height = height;
    _targetFPS = targeFPS;
}

GalaEngine::Window::Window() : Window("Window", 640, 480) { }