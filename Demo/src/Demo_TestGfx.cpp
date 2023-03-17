#include <Demo_TestGfx.hpp>

void Demo_TestGfx::OnLoad() {
    assets->LoadTexture("filter_test");
    SetTextureFilter(assets->GetTexture("filter_test"), TEXTURE_FILTER_BILINEAR);
}

void Demo_TestGfx::OnDraw() {
    GalaEngine::Colour winClear = {0x00, 0x00, 0x00, 0xff};
    
    if(input->IsKeyDown(KEY_ONE)) {
        winClear.r = 0xff;
    }

    if(input->IsKeyDown(KEY_TWO)) {
        winClear.g = 0xff;
    }

    if(input->IsKeyDown(KEY_THREE)) {
        winClear.b = 0xff;
    }

    window->surface.Clear(winClear);

    // Separate textures
    window->surface.DrawTexture(assets->GetTexture("alpha_test"), 16, 16);
    window->surface.DrawTexture(assets->GetTexture("filter_test"), 16, 16 + 16 + 256, 4.0f, 4.0f);

    // Drawn overlayed
    window->surface.DrawTexture(assets->GetTexture("alpha_test"),  16 + 16 + 256, 16);
    window->surface.DrawTexture(assets->GetTexture("filter_test"), 16 + 16 + 256, 16, 4.0f, 4.0f);
}

void Demo_TestGfx::OnUpdate() {

}

void Demo_TestGfx::OnUnload() {
    scene->assets->UnloadAll();
}

Demo_TestGfx::Demo_TestGfx() : Game(
    GalaEngine::GameInfo {
        "GalaEngine Test Graphics Demo (GalaEngine v" GALAENGINE_VERSION_STRING ")",
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