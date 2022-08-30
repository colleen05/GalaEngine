#include <Demo_Scene.hpp>

void Demo_Scene::OnLoad() {
    tex_background = LoadTexture("./res/tex/");
}

void Demo_Scene::OnDraw() {
    window->surface.Clear(Colours::PaleVioletRed);

    window->surface.DrawText("Hello, world!", 32, 32);
}

void Demo_Scene::OnUpdate() {

}

void Demo_Scene::OnUnload() {
    UnloadTexture(tex_background);
}

Demo_Scene::Demo_Scene() : Game(
    GalaEngine::GameInfo {
        "GalaEngine Scene Demo (GalaEngine v" GALAENGINE_VERSION_STRING ")",
        "GalaEngine example project.",
        "Colleen (colleen05)",

        960, 540,

        "./res/"
    }
) {}