#include <Demo_Scene.hpp>

void Demo_Scene::OnLoad() {
    // Load assets
    tex_bgSky = assets->LoadTexture("bg_clouds");
    tex_bgOverlay = assets->LoadTexture("bg_clouds_overlay");

    ts_test = assets->GetTileset("ts_testtiles");

    scene->mainCamera.position  = {0.0f, 0.0f};
    scene->mainCamera.size      = {1024.0f, 576.0f};

    lay_background0 = scene->AddBackgroundLayer(tex_bgSky, C_BLACK);
    lay_background0->scrollSpeed = {32.0f, 12.0f};

    std::vector<uint16_t> tiles = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0x21,
        0x00, 0x47, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0x21,
        0x00, 0x57, 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0x21,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0x21,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0x61, 0x61, 0x61, 0x21,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x26, 0x21, 0x61, 0x21,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x35, 0x36, 0x21, 0x61, 0x21,
        0x63, 0x64, 0x61, 0x63, 0x64, 0x63, 0x64, 0x61, 0x61, 0x61, 0x63, 0x64, 0x61, 0x63, 0x64, 0x21,
        0x21, 0x23, 0x24, 0x21, 0x21, 0x21, 0x23, 0x24, 0x23, 0x24, 0x21, 0x21, 0x23, 0x24, 0x21, 0x21
    };

    lay_tiles = scene->AddTileLayer(ts_test, tiles, 16, 9, C_CLEAR);

    lay_entities = scene->AddEntityLayer();
    
    ent_ball0 = new Ent_Ball(360, 256);
    ent_ball0->spriteFrame = 0;
    ent_ball0->sceneWidth = 1024.0f;
    ent_ball0->sceneHeight = 576.0f;
    scene->PushEntity(ent_ball0, "ball_0");
    lay_entities->AddEntity(ent_ball0);

    ent_ball1 = new Ent_Ball(440, 256);
    ent_ball1->spriteFrame = 1;
    ent_ball1->sceneWidth = 1024.0f;
    ent_ball1->sceneHeight = 576.0f;
    scene->PushEntity(ent_ball1, "ball_1");
    lay_entities->AddEntity(ent_ball1);

    ent_ball2 = new Ent_Ball(520, 256);
    ent_ball2->spriteFrame = 2;
    ent_ball2->sceneWidth = 1024.0f;
    ent_ball2->sceneHeight = 576.0f;
    scene->PushEntity(ent_ball2, "ball_2");
    lay_entities->AddEntity(ent_ball2);

    ent_ball3 = new Ent_Ball(600, 256);
    ent_ball3->spriteFrame = 3;
    ent_ball3->sceneWidth = 1024.0f;
    ent_ball3->sceneHeight = 576.0f;
    scene->PushEntity(ent_ball3, "ball_3");
    lay_entities->AddEntity(ent_ball3);

    lay_foreground = scene->AddBackgroundLayer(tex_bgOverlay, C_CLEAR);
    lay_foreground->scrollSpeed = {96.0f * 10.0f, -48.0f * 10.0f};
    lay_foreground->blendColour = {0xff, 0xff, 0xff, 0xff};
}

void Demo_Scene::OnDraw() {
    const std::string text =
        "FPS: " + std::to_string((int)(1.0f / GetFrameTime())) + "\n" +
        "Entities: " + std::to_string(scene->entities.size()) + "\n" +
        "Layers: " + std::to_string(scene->layers.size()) + "\n";

    window->surface.DrawRectangleRounded(4, 4, 128, 96, 8.0f, {0,0,0,192});
    window->surface.DrawText(text, 12.0f, 12.0f, 20, Colours::White);
}

void Demo_Scene::OnUpdate() {

}

void Demo_Scene::OnUnload() {
    scene->assets->UnloadAll();
}

Demo_Scene::Demo_Scene() : Game(
    GalaEngine::GameInfo {
        "GalaEngine Scene Demo (GalaEngine v" GALAENGINE_VERSION_STRING ")",
        "GalaEngine example project.",
        "Colleen (colleen05)",
        1024,
        576,
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