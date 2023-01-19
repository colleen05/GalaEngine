#include <Demo_Tiles.hpp>

void Demo_Tiles::OnLoad() {
}

void Demo_Tiles::OnDraw() {
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