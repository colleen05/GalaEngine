#include <Demo_Window.hpp>

void Demo_Window::OnLoad() {
    GalaEngine::BackgroundLayer *lay_bg = scene->AddBackgroundLayer(assets->GetTexture("bg_grid"), C_RED);
    lay_bg->scrollSpeed = {64.0f, 64.0f};

    SetWindowState(FLAG_WINDOW_RESIZABLE);
}

void Demo_Window::OnDraw() {
    const int winWidth = window->GetWidth();
    const int winHeight = window->GetHeight();

    const std::string sizeText =
        "Size: " + std::to_string(winWidth) + " x " + std::to_string(winHeight) + "\n" +
        "Surface: " + std::to_string(window->surface.renderTexture.texture.width) + " x " + std::to_string(window->surface.renderTexture.texture.height) + "\n" +
        "Fullscreen: " + (window->IsFullscreen() ? "Yes" : "No");

    Vector2 textSize = MeasureTextEx(GetFontDefault(), sizeText.c_str(), 20, 0);
    window->surface.DrawText(sizeText, (winWidth - textSize.x) / 2, (winHeight - textSize.y) / 2, 20, C_DKGREY);
    
    window->surface.DrawText("F - Fullscreen", 16, winHeight - 32, 20, C_GREY);

    if(!window->IsFocused()) {
        window->surface.DrawRectangle(0, 0, winWidth, winHeight, {0x00, 0x00, 0x00, 0x7f});
    }
}

void Demo_Window::OnUpdate() {
    const bool preIsFullscreen = window->IsFullscreen();

    if(IsKeyPressed(KEY_F)) window->ToggleFullscreen();

    if(preIsFullscreen != window->IsFullscreen()) {
        if(window->IsFullscreen())
            window->SetSize(window->GetMonitorWidth(), window->GetMonitorHeight());
        else
            window->SetSize(800, 600);
    }

    if(window->IsResized()) {
        std::cout << "RESIZING..." << std::endl;
        std::cout << "\tWindow..." << std::endl;
        window->surface.Resize(window->GetWidth(), window->GetHeight());
        std::cout << "\tScene..." << std::endl;
        scene->Resize(window->GetWidth(), window->GetHeight());
        std::cout << "DONE.\n" << std::endl;
        scene->mainCamera.size = {(float)window->GetWidth(), (float)window->GetHeight()};
    }

    Color bgcol = ColorFromHSV(GetTime() * 90.0f, 0.125f, 1.0f);
    scene->GetLayer(0)->blendColour = {bgcol.r, bgcol.g, bgcol.b, bgcol.a};
}

void Demo_Window::OnUnload() {
    scene->assets->UnloadAll();
}

Demo_Window::Demo_Window() : Game(
    GalaEngine::GameInfo {
        "GalaEngine Window Demo (GalaEngine v" GALAENGINE_VERSION_STRING ")",
        "GalaEngine example project.",
        "Colleen (colleen05)",
        800,
        600,
        GalaEngine::AssetPathLayout {
            "./resources/",
            "textures/",
            "sprites/",
            "tilesets/",
            "sounds/",
            "fonts/"
        }
    }
) {}