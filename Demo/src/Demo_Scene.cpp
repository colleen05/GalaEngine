#include <Demo_Scene.hpp>

void Demo_Scene::OnLoad() {
    tex_background = LoadTexture("./res/tex/bg_clouds.png");

    lay_background = new GalaEngine::BackgroundLayer(1024, 576, tex_background);
    lay_background->scrollSpeed = {64.0f, 24.0f};

    scene->PushLayer(lay_background);
}

void Demo_Scene::OnDraw() {
    scene->RenderLayers();

    window->surface.DrawText("Hello, world!", 0, (std::sin(GetTime()) + 1.0f) / 2.0f * 520.0f);
    window->surface.DrawText("FPS: " + std::to_string(1.0f / GetFrameTime()), 8.0f, 8.0f, 20, Colours::GalaBlack);
}

void Demo_Scene::OnUpdate() {
    if(IsKeyDown(KEY_UP)) {
        lay_background->scale.y += GetFrameTime();
    }else if(IsKeyDown(KEY_DOWN)) {
        lay_background->scale.y -= GetFrameTime();
    }

    if(IsKeyDown(KEY_LEFT)) {
        lay_background->scale.x -= GetFrameTime();
    }else if(IsKeyDown(KEY_RIGHT)) {
        lay_background->scale.x += GetFrameTime();
    }
}

void Demo_Scene::OnUnload() {
    UnloadTexture(tex_background);
}

Demo_Scene::Demo_Scene() : Game(
    GalaEngine::GameInfo {
        "GalaEngine Scene Demo (GalaEngine v" GALAENGINE_VERSION_STRING ")",
        "GalaEngine example project.",
        "Colleen (colleen05)",

        1024, 576,

        "./res/"
    }
) {}