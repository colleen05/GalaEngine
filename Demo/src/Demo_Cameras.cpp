#include <Demo_Cameras.hpp>

void Demo_Cameras::SetupRoomTiles() {
    // Red quadrant
    lay_tiles->tiles[lay_tiles->GetTileIndex(1  * 64, 1 * 64)] = 001;
    lay_tiles->tiles[lay_tiles->GetTileIndex(14 * 64, 1 * 64)] = 003;
    lay_tiles->tiles[lay_tiles->GetTileIndex(1  * 64, 7 * 64)] = 021;
    lay_tiles->tiles[lay_tiles->GetTileIndex(14 * 64, 7 * 64)] = 023;

    // Render
    lay_tiles->Render();
}

void Demo_Cameras::OnLoad() {
    scene->AddBackgroundLayer(
        assets->GetTexture("bg_grid"),
        C_BLACK
    );

    scene->GetLayer(0)->blendColour = C_BLACK;

    lay_tiles = scene->AddTileLayer(
        assets->GetTileset("funkyfloor"),
        std::vector<uint16_t>(32*18, 0),
        32, 18
    );

    scene->GetCamera(0)->SetSize(512, 288);
    scene->GetCamera(0)->screenport = {
        (1024 - 512) / 2.0f,
        (576 - 288) / 2.0f,
        512.0f, 288.0f
    };

    SetupRoomTiles();
}

void Demo_Cameras::OnDraw() {
    if(showCameraNumbers) {
        int i = 0;

        for(auto &c : scene->cameras) {
            const GalaEngine::Colour colour = (i == activeCamera) ? C_BLUE : C_LTGREY;

            window->surface.DrawRectangle(
                c->screenport.x, c->screenport.y,
                c->screenport.width, c->screenport.height,
                colour, true, 2.0f
            );

            window->surface.DrawText(
                "Camera " + std::to_string(i) + "\n",
                c->screenport.x + 8,
                c->screenport.y + 8,
                16, colour
            );

            i++;
        }
    }
}

void Demo_Cameras::OnUpdate() {
    if(scene->cameras.size() > 0)
        activeCamera = activeCamera % scene->cameras.size();

    auto camera = scene->GetCamera(activeCamera);

    if(camera) {
        const Vector2 cameraSize = camera->GetSize();

        if(input->IsKeyDown(KEY_LEFT_SHIFT)) {
            // Scale viewport
            if(input->IsKeyDown(KEY_W))         camera->SetSize(cameraSize.x, cameraSize.y - 128.0f * GetFrameTime());
            else if(input->IsKeyDown(KEY_S))    camera->SetSize(cameraSize.x, cameraSize.y + 128.0f * GetFrameTime());

            if(input->IsKeyDown(KEY_A))         camera->SetSize(cameraSize.x - 128.0f * GetFrameTime(), cameraSize.y);
            else if(input->IsKeyDown(KEY_D))    camera->SetSize(cameraSize.x + 128.0f * GetFrameTime(), cameraSize.y);

            // Scale screenport
            if(input->IsKeyDown(KEY_UP))        camera->screenport.height -= 128.0f * GetFrameTime();
            else if(input->IsKeyDown(KEY_DOWN)) camera->screenport.height += 128.0f * GetFrameTime();

            if(input->IsKeyDown(KEY_LEFT))      camera->screenport.width -= 128.0f * GetFrameTime();
            else if(input->IsKeyDown(KEY_RIGHT))camera->screenport.width += 128.0f * GetFrameTime();
        }else {
            // Move viewport
            if(input->IsKeyDown(KEY_W))         camera->position.y -= 128.0f * GetFrameTime();
            else if(input->IsKeyDown(KEY_S))    camera->position.y += 128.0f * GetFrameTime();

            if(input->IsKeyDown(KEY_A))         camera->position.x -= 128.0f * GetFrameTime();
            else if(input->IsKeyDown(KEY_D))    camera->position.x += 128.0f * GetFrameTime();

            // Move screenport
            if(input->IsKeyDown(KEY_UP))        camera->screenport.y -= 128.0f * GetFrameTime();
            else if(input->IsKeyDown(KEY_DOWN)) camera->screenport.y += 128.0f * GetFrameTime();
            
            if(input->IsKeyDown(KEY_LEFT))      camera->screenport.x -= 128.0f * GetFrameTime();
            else if(input->IsKeyDown(KEY_RIGHT))camera->screenport.x += 128.0f * GetFrameTime();
        }

        if(input->IsKeyPressed(KEY_TAB)) {
            if(input->IsKeyDown(KEY_LEFT_SHIFT)) 
                scene->GetCamera(activeCamera)->visible = !scene->GetCamera(activeCamera)->visible;
            else
                activeCamera++;
        }
    }

    if(input->IsKeyPressed(KEY_INSERT)) {
        scene->PushCamera(std::make_shared<GalaEngine::Camera>(0, 0, 512, 288));
    }else if(input->IsKeyPressed(KEY_DELETE)) {
        scene->RemoveCamera(activeCamera);
    } else if(input->IsKeyPressed(KEY_LEFT_CONTROL)) {
        showCameraNumbers = !showCameraNumbers;
    }
}

void Demo_Cameras::OnUnload() {
    scene->assets->UnloadAll();
}

Demo_Cameras::Demo_Cameras() : Game(
    GalaEngine::GameInfo {
        "GalaEngine Cameras Demo (GalaEngine v" GALAENGINE_VERSION_STRING ")",
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