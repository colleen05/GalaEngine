#include <Demo_NPatches.hpp>

void Demo_NPatches::OnLoad() {
    
}

void Demo_NPatches::OnDraw() {

}

void Demo_NPatches::OnUpdate() {

}

void Demo_NPatches::OnUnload() {
    scene->assets->UnloadAll();
}

Demo_NPatches::Demo_NPatches() : Game(
    GalaEngine::GameInfo {
        "GalaEngine 9-Patch Demo (GalaEngine v" GALAENGINE_VERSION_STRING ")",
        "GalaEngine example project.",
        "Colleen (colleen05)",
        1280,
        720,
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