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
    // Scaling
    const float surfaceWidth  = surface.renderTexture.texture.width;
    const float surfaceHeight = surface.renderTexture.texture.height;

    _surfaceRect = {0.0f, 0.0f};
    
    switch(scaleMode) {
        case ScaleMode::Centre:
            _surfaceRect = (Rectangle) {
                (GetWidth()  - surfaceWidth)  / 2.0f,
                (GetHeight() - surfaceHeight) / 2.0f,
                surfaceWidth, surfaceHeight
            };
            break;
        case ScaleMode::Contain:
            _surfaceRect = Math::GetLetterboxedRectangle(
                (Vector2)   {surfaceWidth, surfaceHeight},
                (Rectangle) {0.0f, 0.0f, (float)GetWidth(), (float)GetHeight()}
            );
            break;
        case ScaleMode::Stretch:
            _surfaceRect = (Rectangle) {
                0.0f, 0.0f,
                (float)GetWidth(), (float)GetHeight()
            };
            break;
        case ScaleMode::IntegerScale:
            _surfaceRect = Math::GetIntegerScaledRectangle(
                (Vector2)   {surfaceWidth, surfaceHeight},
                (Rectangle) {0.0f, 0.0f, (float)GetWidth(), (float)GetHeight()}
            );
            break;
    }

    // Draw surface
    SetTextureFilter(
        surface.renderTexture.texture,
        interpolateSurface ?
            TEXTURE_FILTER_BILINEAR :
            TEXTURE_FILTER_POINT
    );

    DrawTexturePro(
        surface.renderTexture.texture,
        Rectangle {
            0.0f,
            surfaceHeight,
            surfaceWidth,
            -surfaceHeight
        },
        _surfaceRect,
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
bool GalaEngine::Window::ShouldClose    () { return ::WindowShouldClose();  }
bool GalaEngine::Window::IsReady        () { return ::IsWindowReady();      }

bool GalaEngine::Window::IsFullscreen   () { return ::IsWindowFullscreen(); }
bool GalaEngine::Window::IsMinimised    () { return ::IsWindowMinimized();  }
bool GalaEngine::Window::IsMaximised    () { return ::IsWindowMaximized();  }
bool GalaEngine::Window::IsFocused      () { return ::IsWindowFocused();    }

float GalaEngine::Window::GetFPS        () { return (float)::GetFPS();      }

bool GalaEngine::Window::IsResized      () { return ::IsWindowResized();    }

bool GalaEngine::Window::IsResizable() {
    return ::IsWindowState(FLAG_WINDOW_RESIZABLE);
}

bool GalaEngine::Window::IsUndecorated() {
    return ::IsWindowState(FLAG_WINDOW_UNDECORATED);
}

bool GalaEngine::Window::IsHidden() { return ::IsWindowHidden(); }

bool GalaEngine::Window::IsTopmost() {
    return ::IsWindowState(FLAG_WINDOW_TOPMOST);
}

int GalaEngine::Window::GetWidth() {
    return IsFullscreen() ? GetMonitorWidth() : (_width);
}

int GalaEngine::Window::GetHeight() {
    return IsFullscreen() ? GetMonitorHeight() : (_height);
}

Vector2 GalaEngine::Window::GetSize() {
    return (Vector2) {
        (float) GetWidth(),
        (float) GetHeight()
    };
}

Vector2 GalaEngine::Window::GetPosition     () { return ::GetWindowPosition();  }
int GalaEngine::Window::GetMonitorCount     () { return ::GetMonitorCount();    }
int GalaEngine::Window::GetCurrentMonitor   () { return ::GetCurrentMonitor();  }

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

Vector2 GalaEngine::Window::GetMousePosition() {
    const Vector2 mousePosition = ::GetMousePosition();
    const float   surfaceWidth  = surface.renderTexture.texture.width;
    const float   surfaceHeight = surface.renderTexture.texture.height;

    return Vector2 {
        Clamp((mousePosition.x - _surfaceRect.x) / _surfaceRect.width  * surfaceWidth , 0.0f, surfaceWidth),
        Clamp((mousePosition.y - _surfaceRect.y) / _surfaceRect.height * surfaceHeight, 0.0f, surfaceHeight)
    };
}


// Setters
void GalaEngine::Window::SetTitle(const std::string &title) {
    SetWindowTitle(title.c_str());
}

void GalaEngine::Window::SetIcon(const Image &image) {
    SetWindowIcon(image);
}

void GalaEngine::Window::Minimise   () { ::MinimizeWindow();    }
void GalaEngine::Window::Maximise   () { ::MaximizeWindow();    }
void GalaEngine::Window::Restore    () { ::RestoreWindow();     }

void GalaEngine::Window::Centre() {
    SetPosition(
        (GetMonitorWidth()  - GetWidth())  / 2,
        (GetMonitorHeight() - GetHeight()) / 2
    );
}

void GalaEngine::Window::ToggleFullscreen() { ::ToggleFullscreen(); }

void GalaEngine::Window::SetFullscreen(const bool fullscreen) {
    if(fullscreen != IsFullscreen()) ToggleFullscreen();
}

void GalaEngine::Window::SetResizable(const bool resizable) {
    if(resizable)   ::SetWindowState    (FLAG_WINDOW_RESIZABLE);
    else            ::ClearWindowState  (FLAG_WINDOW_RESIZABLE);
}

void GalaEngine::Window::SetUndecorated(const bool undecorated) {
    if(undecorated) ::SetWindowState    (FLAG_WINDOW_UNDECORATED);
    else            ::ClearWindowState  (FLAG_WINDOW_UNDECORATED);
}

void GalaEngine::Window::SetHidden(const bool hidden) {
    if(hidden)      ::SetWindowState    (FLAG_WINDOW_HIDDEN);
    else            ::ClearWindowState  (FLAG_WINDOW_HIDDEN);
}

void GalaEngine::Window::SetTopmost(const bool topmost) {
    if(topmost)     ::SetWindowState    (FLAG_WINDOW_TOPMOST);
    else            ::ClearWindowState  (FLAG_WINDOW_TOPMOST);
}

void GalaEngine::Window::SetWidth   (const int width)   { SetSize(width, GetHeight()); }
void GalaEngine::Window::SetHeight  (const int height)  { SetSize(GetWidth(), height); }

void GalaEngine::Window::SetSize(const int width, const int height, const bool resizeSurface) {
    _width = width;
    _height = height;
    ::SetWindowSize(width, height);
    
    if(resizeSurface)
        surface.Resize(width, height);
}

void GalaEngine::Window::SetMinSize(const int width, const int height) {
    ::SetWindowMinSize(width, height);
}

void GalaEngine::Window::SetPosition(const int x, const int y) { ::SetWindowPosition(x, y); }

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