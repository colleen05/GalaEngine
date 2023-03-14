#include <Demo_TestGfx.hpp>

void Demo_TestGfx::OnLoad() {

}

void Demo_TestGfx::OnDraw() {
    window->surface.DrawTexture(assets->GetTexture("alpha_test"), 16, 16);
    window->surface.DrawTexture(assets->GetTexture("filter_test"), 16, 16 + 16 + 256, 4.0f, 3.0f);

    SetTextureFilter(assets->GetTexture("filter_test"), TEXTURE_FILTER_BILINEAR);
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