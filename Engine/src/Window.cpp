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

// Getters
bool GalaEngine::Window::ShouldClose() {
    return WindowShouldClose();
}

bool GalaEngine::Window::IsReady() {
    return ::IsWindowReady();
}

bool GalaEngine::Window::IsFullscreen() {
    return ::IsWindowFullscreen();
}

bool GalaEngine::Window::IsMinimised() {
    return ::IsWindowMinimized();
}

bool GalaEngine::Window::IsMaximised() {
    return ::IsWindowMaximized();
}

bool GalaEngine::Window::IsFocused() {
    return ::IsWindowFocused();
}

float GalaEngine::Window::GetFPS() {
    return (float)::GetFPS();
}

bool GalaEngine::Window::IsResized() {
    return ::IsWindowResized();
}

int GalaEngine::Window::GetWidth() {
    return GetScreenWidth();
}

int GalaEngine::Window::GetHeight() {
    return GetScreenHeight();
}

Vector2 GalaEngine::Window::GetSize() {
    return (Vector2) {
        (float) GetWidth(),
        (float) GetHeight()
    };
}

Vector2 GalaEngine::Window::GetPosition() {
    return GetWindowPosition();
}

int GalaEngine::Window::GetMonitorCount() {
    return ::GetMonitorCount();
}

int GalaEngine::Window::GetCurrentMonitor() {
    return ::GetCurrentMonitor();
}

int GalaEngine::Window::GetMonitorWidth(int monitor) {
    const int m = monitor >= 0 ? monitor : GetCurrentMonitor();

    return ::GetMonitorWidth(m);
}

int GalaEngine::Window::GetMonitorHeight(int monitor) {
    const int m = monitor >= 0 ? monitor : GetCurrentMonitor();

    return ::GetMonitorHeight(m);
}

Vector2 GalaEngine::Window::GetMonitorSize(int monitor) {
    const int m = monitor >= 0 ? monitor : GetCurrentMonitor();

    return (Vector2) {
        (float) ::GetMonitorWidth(m),
        (float) ::GetMonitorHeight(m)
    };
}

float GalaEngine::Window::GetMonitorPhysicalWidth(int monitor) {
    const int m = monitor >= 0 ? monitor : GetCurrentMonitor();

    return (float) ::GetMonitorPhysicalWidth(m);
}

float GalaEngine::Window::GetMonitorPhysicalHeight(int monitor) {
    const int m = monitor >= 0 ? monitor : GetCurrentMonitor();

    return (float) ::GetMonitorPhysicalHeight(m);
}

Vector2 GalaEngine::Window::GetMonitorPhysicalSize(int monitor) {
    const int m = monitor >= 0 ? monitor : GetCurrentMonitor();

    return (Vector2) {
        (float) ::GetMonitorPhysicalWidth(m),
        (float) ::GetMonitorPhysicalHeight(m)
    };
}

float GalaEngine::Window::GetMonitorRefreshRate(int monitor) {
    const int m = monitor >= 0 ? monitor : GetCurrentMonitor();

    return (float) ::GetMonitorRefreshRate(m);
}

std::string GalaEngine::Window::GetMonitorName(int monitor) {
    const int m = monitor >= 0 ? monitor : GetCurrentMonitor();

    return std::string(::GetMonitorName(m));
}

// Setters
void GalaEngine::Window::SetTitle(std::string title) {
    SetWindowTitle(title.c_str());
}

void GalaEngine::Window::ToggleFullscreen() {
    ::ToggleFullscreen();
}

void GalaEngine::Window::SetMinimised(bool minimised) {
    if(minimised) ::MinimizeWindow();
}

void GalaEngine::Window::SetMaximised(bool maximised) {
    if(maximised) ::MaximizeWindow();
}

void GalaEngine::Window::SetWidth(int width) {
    ::SetWindowSize(width, GetHeight());
}

void GalaEngine::Window::SetHeight(int height) {
    ::SetWindowSize(GetWidth(), height);
}

void GalaEngine::Window::SetSize(int width, int height) {
    ::SetWindowSize(width, height);
}

void GalaEngine::Window::SetPosition(int x, int y) {
    ::SetWindowPosition(x, y);
}

void GalaEngine::Window::SetTargetFPS(float fps) {
    if(fps < 0) fps = 60; // Guard against negative target FPS.
    ::SetTargetFPS((int) fps);
}

// Constructors
GalaEngine::Window::Window(std::string title, int width, int height, int targetFPS) {
    if(targetFPS < 0) targetFPS = 60; // Guard against negative target FPS.

    _title = title;
    _width = width;
    _height = height;
    _targetFPS = targetFPS;
}

GalaEngine::Window::Window() : Window("Window", 640, 480) { }