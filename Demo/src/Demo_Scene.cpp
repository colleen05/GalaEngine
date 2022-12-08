#include <Demo_Scene.hpp>

void Demo_Scene::OnLoad() {
    HideCursor();

    scene->Resize(2048, 1152);

    // Setup flower_click binds
    input->BindKeyboard("flower_click", {KEY_A, KEY_Q});
    input->BindMouse("flower_click", {MOUSE_BUTTON_LEFT});

    // Setup default flower_drag binds
    input->BindInput("flower_drag", {{KEY_SPACE}, {MOUSE_BUTTON_RIGHT}, {}, false, GAMEPAD_AXIS_LEFT_X});

    // Overwrite keyboard binds individually
    input->BindKeyboard("flower_drag", {KEY_D}, true);
    input->BindKeyboard("flower_drag", {KEY_E}, false);

    // Add mouse binds
    input->BindMouse("flower_drag", {MOUSE_BUTTON_MIDDLE});

    // Add gamepad binds
    input->BindGamepadButtons("flower_click", {GAMEPAD_BUTTON_RIGHT_FACE_DOWN});
    input->BindGamepadButtons("flower_drag", {GAMEPAD_BUTTON_RIGHT_FACE_RIGHT});

    input->BindGamepadAxis("cam_x", GAMEPAD_AXIS_RIGHT_X);
    input->BindGamepadAxis("cam_y", GAMEPAD_AXIS_RIGHT_Y);

    input->BindGamepadAxis("cur_x", GAMEPAD_AXIS_LEFT_X);
    input->BindGamepadAxis("cur_y", GAMEPAD_AXIS_LEFT_Y);

    input->BindGamepadAxis("zoom_in", GAMEPAD_AXIS_RIGHT_TRIGGER);
    input->BindGamepadAxis("zoom_out", GAMEPAD_AXIS_LEFT_TRIGGER);

    // Load assets
    assets->LoadSound("sfx/chime", "sfx_chime.ogg");

    tex_bgSky = assets->LoadTexture("backgrounds/clouds", "bg_clouds.png");
    tex_bgOverlay = assets->LoadTexture("backgrounds/clouds_overlay", "bg_clouds_overlay.png");
    tex_cursor = assets->LoadTexture("curosr", "cursor.png");

    assets->LoadTexture("sprites/flower", "spr_flower.png");
    
    assets->LoadSprite("flower", "flower.yml");

    scene->mainCamera.position  = {0.0f, 0.0f};
    scene->mainCamera.size      = {1024.0f, 576.0f};

    lay_background0 = scene->AddBackgroundLayer(tex_bgSky, C_BLACK);
    lay_background0->scrollSpeed = {32.0f, 12.0f};

    ts_test.texture = assets->LoadTexture("tilesets/testtiles", "ts_testtiles.png");
    ts_test.tileSize = 64;

    std::vector<uint16_t> tiles = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x47, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x57, 0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x61, 0x61, 0x61, 0x61, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x25, 0x26, 0x21, 0x61, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x35, 0x36, 0x21, 0x61, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x63, 0x64, 0x61, 0x63, 0x64, 0x63, 0x64, 0x61, 0x61, 0x61, 0x63, 0x64, 0x61, 0x63, 0x64, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x21, 0x23, 0x24, 0x21, 0x21, 0x21, 0x23, 0x24, 0x23, 0x24, 0x21, 0x21, 0x23, 0x24, 0x21, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    lay_tiles = scene->AddTileLayer(ts_test, tiles, 32, 18, C_CLEAR);

    lay_entities = scene->AddEntityLayer();
    
    ent_flower0 = new Ent_Flower(360, 256);
    ent_flower0->spriteFrame = 0;
    scene->PushEntity(ent_flower0, "flower_0");
    lay_entities->AddEntity(ent_flower0);

    ent_flower1 = new Ent_Flower(440, 256);
    ent_flower1->spriteFrame = 1;
    scene->PushEntity(ent_flower1, "flower_1");
    lay_entities->AddEntity(ent_flower1);

    ent_flower2 = new Ent_Flower(520, 256);
    ent_flower2->spriteFrame = 2;
    scene->PushEntity(ent_flower2, "flower_2");
    lay_entities->AddEntity(ent_flower2);

    ent_flower3 = new Ent_Flower(600, 256);
    ent_flower3->spriteFrame = 3;
    scene->PushEntity(ent_flower3, "flower_3");
    lay_entities->AddEntity(ent_flower3);

    lay_foreground = scene->AddBackgroundLayer(tex_bgOverlay, C_CLEAR);
    lay_foreground->scrollSpeed = {96.0f * 10.0f, -48.0f * 10.0f};
    lay_foreground->blendColour = {0xff, 0xff, 0xff, 0xff};
}

void Demo_Scene::OnDraw() {
    scene->RenderLayers();

    window->surface.DrawText("FPS: " + std::to_string(1.0f / GetFrameTime()), 8.0f, 8.0f, 20, Colours::GalaBlack);

    window->surface.DrawTexture(tex_cursor, GetMouseX()-16.0f, GetMouseY()-16.0f);
}

void Demo_Scene::OnUpdate() {
    if(IsKeyDown(KEY_UP)) {
        scene->mainCamera.position.y -= 512.0f * GetFrameTime();
    }else if(IsKeyDown(KEY_DOWN)) {
        scene->mainCamera.position.y += 512.0f * GetFrameTime();
    }

    if(IsKeyDown(KEY_LEFT)) {
        scene->mainCamera.position.x -= 512.0f * GetFrameTime();
    }else if(IsKeyDown(KEY_RIGHT)) {
        scene->mainCamera.position.x += 512.0f * GetFrameTime();
    }

    scene->mainCamera.position.x += 720.0f * input->GetFloat("cam_x") * GetFrameTime();
    scene->mainCamera.position.y += 720.0f * input->GetFloat("cam_y") * GetFrameTime();

    auto mousePos = GetMousePosition();
    SetMousePosition(
        mousePos.x + (480.0f * input->GetFloat("cur_x") * GetFrameTime()),
        mousePos.y + (480.0f * input->GetFloat("cur_y") * GetFrameTime())
    );

    auto zoomAmt = 0.0f;

    if(std::abs(GetMouseWheelMove() - 0.0f) > __FLT_EPSILON__) {
        zoomAmt = GetMouseWheelMove();
    }else {
        zoomAmt = (input->GetFloat("zoom_in") - input->GetFloat("zoom_out")) / 2.0f;
    }

    scene->mainCamera.size = Vector2Subtract(
        scene->mainCamera.size,
        Vector2Multiply(
            Vector2 {32.0f, 18.0f},
            Vector2 {zoomAmt, zoomAmt}
        )
    );
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
            "./res/",
            "textures/",
            "sounds/",
            "fonts/"
        }
    }
) {}