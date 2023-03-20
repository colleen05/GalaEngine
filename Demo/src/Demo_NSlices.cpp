#include <Demo_NSlices.hpp>

void Demo_NSlices::OnLoad() {
    
}

void Demo_NSlices::OnDraw() {

}

void Demo_NSlices::OnUpdate() {

}

void Demo_NSlices::OnUnload() {
    scene->assets->UnloadAll();
}

Demo_NSlices::Demo_NSlices() : Game(
    GalaEngine::GameInfo {
        "GalaEngine 9-Slice Demo (GalaEngine v" GALAENGINE_VERSION_STRING ")",
        "GalaEngine example project.",
        "Colleen (colleen05)",
        1280,
        720,
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