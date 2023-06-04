#include <Demo_Window.hpp>

void Demo_Window::OnLoad() {
    // Create simple background.
    GalaEngine::BackgroundLayer *lay_bg = scene->AddBackgroundLayer(assets->GetTexture("bg_grid"), C_RED);
    lay_bg->scrollSpeed = {64.0f, 64.0f};

    // Allow resizing, set minimum size.
    window->SetResizable(true);
    window->SetMinSize(320, 240);

    // Set window icon
    auto tex_icon = assets->GetTexture("tex_colourX");
    Image img_icon = LoadImageFromTexture(tex_icon);
    window->SetIcon(img_icon);
    UnloadImage(img_icon);
}

void Demo_Window::OnDraw() {
    // Draw stats.
    const int winWidth      = window->GetWidth();
    const int winHeight     = window->GetHeight();
    const int sceneWidth    = scene->GetSize().x;
    const int sceneHeight   = scene->GetSize().y;

    const int fontSize = 20;

    const Vector2 mousePosition = window->GetMousePosition();

    window->surface.DrawCircle(mousePosition.x, mousePosition.y, 4.0f, C_GALARED);

    const std::string sizeText =
        "Size: " + std::to_string(winWidth) + " x " + std::to_string(winHeight) + "\n" +
        "Surface: " + std::to_string(window->surface.renderTexture.texture.width) + " x " + std::to_string(window->surface.renderTexture.texture.height) + "\n" +
        "Mouse: " + std::to_string((int)mousePosition.x) + ", " + std::to_string((int)mousePosition.y) + "\n" +
        "Monitor: " + std::to_string(window->GetMonitorWidth()) + " x " + std::to_string(window->GetMonitorHeight()) + "\n" +
        "Fullscreen: " + (window->IsFullscreen() ? "Yes" : "No") + "\n" +
        "Fill window: " + (fillWindow ? "Yes" : "No");

    Vector2 textSize = MeasureTextEx(GalaEngine::DefaultFont->GetAtSize(fontSize), sizeText.c_str(), fontSize, 0);
    window->surface.DrawText(sizeText, (sceneWidth - textSize.x) / 2, (sceneHeight - textSize.y) / 2, fontSize, C_DKGREY);
    
    window->surface.DrawText("F - Fullscreen  |  S - Toggle scaling\nC - Centre", 16, sceneHeight - 64, fontSize, C_GREY);

    // Shade window if not focused.
    if(!window->IsFocused()) {
        window->surface.DrawRectangle(0, 0, sceneWidth, sceneHeight, {0x00, 0x00, 0x00, 0x7f});
    }
}

void Demo_Window::OnUpdate() {
    // Controls
    if(IsKeyPressed(KEY_F)) window->ToggleFullscreen();
    if(IsKeyPressed(KEY_S)) fillWindow = !fillWindow;
    if(IsKeyPressed(KEY_C)) window->Centre();
    if(IsKeyPressed(KEY_I)) window->interpolateSurface = !window->interpolateSurface;

    if(IsKeyPressed(KEY_ONE))   window->scaleMode = GalaEngine::Window::ScaleMode::Centre;
    if(IsKeyPressed(KEY_TWO))   window->scaleMode = GalaEngine::Window::ScaleMode::Contain;
    if(IsKeyPressed(KEY_THREE)) window->scaleMode = GalaEngine::Window::ScaleMode::Stretch;
    if(IsKeyPressed(KEY_FOUR))  window->scaleMode = GalaEngine::Window::ScaleMode::IntegerScale;

    // Resize scene and camera if resized
    if(window->IsResized() && fillWindow) {
        scene->Resize(window->GetWidth(), window->GetHeight());
        scene->GetCamera(0)->SetSize((float)window->GetWidth(), (float)window->GetHeight());
        scene->GetCamera(0)->screenport = {0.0f, 0.0f, (float)window->GetWidth(), (float)window->GetHeight()};
    }

    // Update background (too make it look cool)
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
        600,
        400,
        GalaEngine::AssetPathLayout {
            "./resources/",
            "textures/",
            "sprites/",
            "tilesets/",
            "nslices/",
            "sounds/",
            "fonts/"
        }
    }
) {}