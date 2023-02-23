#include <GalaEngine/Window.hpp>

// Initialisation & deconstruction
void GalaEngine::Window::Init() {
    InitWindow(_width, _height, _title.c_str());
    SetTargetFPS(_targetFPS);
    SetExitKey(KEY_NULL);

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
    return ::WindowShouldClose();
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
    return ::GetScreenWidth();
}

int GalaEngine::Window::GetHeight() {
    return ::GetScreenHeight();
}

Vector2 GalaEngine::Window::GetSize() {
    return (Vector2) {
        (float) GetWidth(),
        (float) GetHeight()
    };
}

Vector2 GalaEngine::Window::GetPosition() {
    return ::GetWindowPosition();
}

int GalaEngine::Window::GetMonitorCount() {
    return ::GetMonitorCount();
}

int GalaEngine::Window::GetCurrentMonitor() {
    return ::GetCurrentMonitor();
}

int GalaEngine::Window::GetMonitorWidth(const int monitor) {
    const int m = monitor >= 0 ? monitor : GetCurrentMonitor();

    return ::GetMonitorWidth(m);
}

int GalaEngine::Window::GetMonitorHeight(const int monitor) {
    const int m = monitor >= 0 ? monitor : GetCurrentMonitor();

    return ::GetMonitorHeight(m);
}

Vector2 GalaEngine::Window::GetMonitorSize(const int monitor) {
    const int m = monitor >= 0 ? monitor : GetCurrentMonitor();

    return (Vector2) {
        (float) ::GetMonitorWidth(m),
        (float) ::GetMonitorHeight(m)
    };
}

float GalaEngine::Window::GetMonitorPhysicalWidth(const int monitor) {
    const int m = monitor >= 0 ? monitor : GetCurrentMonitor();

    return (float) ::GetMonitorPhysicalWidth(m);
}

float GalaEngine::Window::GetMonitorPhysicalHeight(const int monitor) {
    const int m = monitor >= 0 ? monitor : GetCurrentMonitor();

    return (float) ::GetMonitorPhysicalHeight(m);
}

Vector2 GalaEngine::Window::GetMonitorPhysicalSize(const int monitor) {
    const int m = monitor >= 0 ? monitor : GetCurrentMonitor();

    return (Vector2) {
        (float) ::GetMonitorPhysicalWidth(m),
        (float) ::GetMonitorPhysicalHeight(m)
    };
}

float GalaEngine::Window::GetMonitorRefreshRate(const int monitor) {
    const int m = monitor >= 0 ? monitor : GetCurrentMonitor();

    return (float) ::GetMonitorRefreshRate(m);
}

std::string GalaEngine::Window::GetMonitorName(const int monitor) {
    const int m = monitor >= 0 ? monitor : GetCurrentMonitor();

    return std::string(::GetMonitorName(m));
}

// Setters
void GalaEngine::Window::SetTitle(const std::string &title) {
    SetWindowTitle(title.c_str());
}

void GalaEngine::Window::ToggleFullscreen() {
    ::ToggleFullscreen();
}

void GalaEngine::Window::SetMinimised() {
    ::MinimizeWindow();
}

void GalaEngine::Window::SetMaximised() {
    ::MaximizeWindow();
}

void GalaEngine::Window::SetWidth(const int width) {
    SetSize(width, GetHeight());
}

void GalaEngine::Window::SetHeight(const int height) {
    SetSize(GetWidth(), height);
}

void GalaEngine::Window::SetSize(const int width, const int height) {
    _width = width;
    _height = height;
    ::SetWindowSize(width, height);
    surface.Resize(width, height);
}

void GalaEngine::Window::SetPosition(const int x, const int y) {
    ::SetWindowPosition(x, y);
}

void GalaEngine::Window::SetTargetFPS(const float fps) {
    ::SetTargetFPS((int)(fps < 0 ? 60 : fps));
}

// Constructors
GalaEngine::Window::Window(const std::string &title, const int width, const int height, const int targetFPS) {
    _title = title;
    _width = width;
    _height = height;
    _targetFPS = (targetFPS < 0 ? 60 : targetFPS);
}

GalaEngine::Window::Window() : Window("Window", 640, 480) { }