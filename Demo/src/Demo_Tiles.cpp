#include <Demo_Tiles.hpp>

void Demo_Tiles::OnLoad() {
}

void Demo_Tiles::OnDraw() {
    float thickness = IsKeyDown(KEY_SPACE) ? 10.0f : 2.0f;
    window->surface.DrawRectangle(320, 240, 320, 240, C_GALARED, true, thickness);
}

void Demo_Tiles::OnUpdate() {
}

void Demo_Tiles::OnUnload() {

}

Demo_Tiles::Demo_Tiles() : Game(
    GalaEngine::GameInfo {
        "GalaEngine Tiles Demo (GalaEngine v" GALAENGINE_VERSION_STRING ")",
        "GalaEngine example project.",
        "Colleen (colleen05)",

        1280, 720,

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