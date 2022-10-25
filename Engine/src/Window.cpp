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
    return ::GetMonitorWidth(monitor >= 0 ? monitor : GetCurrentMonitor());
}

int GalaEngine::Window::GetMonitorHeight(int monitor) {
    return ::GetMonitorHeight(monitor >= 0 ? monitor : GetCurrentMonitor());
}

Vector2 GalaEngine::Window::GetMonitorSize(int monitor) {
    int m = monitor >= 0 ? monitor : GetCurrentMonitor();

    return (Vector2) {
        (float) ::GetMonitorWidth(m),
        (float) ::GetMonitorHeight(m)
    };
}

float GalaEngine::Window::GetMonitorPhysicalWidth(int monitor) {
    return (float) ::GetMonitorPhysicalWidth(monitor >= 0 ? monitor : GetCurrentMonitor());
}

float GalaEngine::Window::GetMonitorPhysicalHeight(int monitor) {
    return (float) ::GetMonitorPhysicalHeight(monitor >= 0 ? monitor : GetCurrentMonitor());
}

Vector2 GalaEngine::Window::GetMonitorPhysicalSize(int monitor) {
    int m = monitor >= 0 ? monitor : GetCurrentMonitor();

    return (Vector2) {
        (float) ::GetMonitorPhysicalWidth(m),
        (float) ::GetMonitorPhysicalHeight(m)
    };
}

float GalaEngine::Window::GetMonitorRefreshRate(int monitor) {
    return (float) ::GetMonitorRefreshRate(monitor >= 0 ? monitor : GetCurrentMonitor());
}

std::string GalaEngine::Window::GetMonitorName(int monitor) {
    return std::string(::GetMonitorName(monitor >= 0 ? monitor : GetCurrentMonitor()));
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
    ::SetTargetFPS((int) fps);
}

// Constructors
GalaEngine::Window::Window(std::string title, int width, int height, int targeFPS) {
    _title = title;
    _width = width;
    _height = height;
    _targetFPS = targeFPS;
}

GalaEngine::Window::Window() : Window("Window", 640, 480) { }