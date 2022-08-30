#include <Demo_Drawing.hpp>

void Demo_Drawing::OnLoad() {
    tex_sprite = LoadTexture("./res/tex/spr_test.png");

    spr_test = GalaEngine::Sprite {
        tex_sprite,
        {0.0f, 0.0f},
        std::vector<Rectangle> {
            {0.0f, 0.0f,    64.0f, 64.0f},
            {64.0f, 0.0f,   64.0f, 64.0f},
            {0.0f, 64.0f,   64.0f, 64.0f},
            {64.0f, 64.0f,  64.0f, 64.0f},
            {32.0f, 32.0f,  64.0f, 64.0f}
        }
    };
}

void Demo_Drawing::OnDraw() {
    window->surface.Clear(clearColour);

    // Elipse tests
    for(int i = 0; i < 8; i++) {
        bool outline = true;

        if(IsKeyDown(KEY_O)) {
            outline = !(i == 7);
        }

        window->surface.DrawEllipse(
            1280.0f / 2.0f, 720.0f / 2.0f,
            1280.0f / 4.0f * (rec_o / i),
            720.0f / 4.0f * (rec_o / i),
            Colours::Crimson, outline,
            IsKeyDown(KEY_O) ? 2.0f : 1.0f
        );
    }

    // Outline tests
    window->surface.DrawCircle(32.0f, 720.0f - 32.0f, 32.0f, Colours::Orange, true, ell_o);
    window->surface.DrawEllipse(128.0f, 720.0f - 32.0f, 32.0f, 32.0f, Colours::Yellow, true, ell_o);
    window->surface.DrawEllipse(128.0f, 720.0f - 96.0f, 64.0f, 32.0f, Colours::Yellow, true, ell_o);
    window->surface.DrawRectangle(192.0f, 720.0f - 48.0f, 64.0f, 32.0f, Colours::YellowGreen, true, ell_o);
    window->surface.DrawRectangleRounded(288.0f, 720.0f - 64.0f, 96.0f, 48.0f, rrec_r, Colours::Green, IsKeyUp(KEY_O), ell_o);

    // Line tests
    window->surface.DrawLine(1280.0f / 2.0f, 0.0f, rec_x, rec_y, Colours::SeaGreen);
    window->surface.DrawLine(1280.0f / 2.0f, 720.0f, rec_x, rec_y, 4.0f, Colours::ForestGreen);

    // Triangle tests
    window->surface.DrawTriangle(
        64.0f, rec_x * (720.0f / 1280.0f) + 64.0f,
        32.0f, rec_x * (720.0f / 1280.0f) + circ_r2 * 4.0f,
        96.0f, rec_x * (720.0f / 1280.0f) + circ_r2 * 4.0f,
        Colours::Violet,
        IsKeyUp(KEY_O)
    );

    // Rectangles tests
    window->surface.DrawRectangleColours(1024.0f, rec_x * (720.0f / 1280.0f), circ_r2 * 2.0f, circ_r * 2.0f, C_RED, C_GREEN, C_BLUE, C_YELLOW);
    window->surface.DrawRectangle(rec_x, rec_y, 256.0f, 128.0f, Colours::CornflowerBlue);
    window->surface.DrawRectangle(rec_x-16, rec_y-16, 256.0f + 32.0f, 128.0f + 32.0f, Colours::Gold, true, rec_o);
    window->surface.DrawRectangle(rec_x, rec_y, 256.0f, 128.0f, rec_rot * 2.0f, {0.0f, 0.0f}, Colours::BlueViolet);
    window->surface.DrawRectangle(rec_x+128.0f, rec_y+64.0f, 256.0f, 128.0f, rec_rot * 3.0f, {128.0f, 64.0f}, Colours::Purple);

    // Circles tests
    window->surface.DrawCircle(circ_x2, circ_y, circ_r2 * 1.25f, Colours::Blue);
    window->surface.DrawCircle(circ_x2, circ_y, circ_r2 * 1.5f, Colours::LawnGreen, true, 4.0f);
    window->surface.DrawCircle(circ_x2, circ_y, circ_r2 * 1.5f, Colours::Blue, true, 2.0f);
    window->surface.DrawCircle(circ_x, circ_y, circ_r, Colours::DarkGoldenrod, Colours::Yellow);

    // Sprite test & text tests
    window->surface.DrawSprite(spr_test, id_frame, spr_x, spr_y, spr_scalex, spr_scaley, spr_rot);
    
    window->surface.DrawText("Frame: " + std::to_string(id_frame), 640, 8 + 20 * 0, 20, C_GALAWHITE);
    window->surface.DrawText("Origin: " + std::to_string(spr_test.origin.x) + ", " + std::to_string(spr_test.origin.y), 640, 8 + 20 * 1, 20, C_GALAWHITE);
    window->surface.DrawText("FPS: " + std::to_string(1.0f / GetFrameTime()), 8.0f, 8.0f, 20);
}

void Demo_Drawing::OnUpdate() {
    // Animation
    if(IsKeyUp(KEY_P)){
        clearColour = GalaEngine::Colour::Lerp(Colours::GalaRed, Colours::GalaBlack, (std::sin(GetTime()) + 1.0f) / 2.0f);

        rec_x   = (std::cos(GetTime()) + 1.0f) / 2.0f * (1280.0f - 256.0f);
        rec_rot = (std::cos(GetTime()) + 1.0f) / 2.0f * (360.0f);

        circ_x  = (std::cos(GetTime()) + 1.0f) / 2.0f * (1280.0f - 128.0f) + 64.0f;
        circ_x2 = (std::sin(GetTime()) + 1.0f) / 2.0f * (1280.0f - 128.0f) + 64.0f;
        circ_r  = (std::sin(GetTime()) + 1.0f) / 2.0f * (56.0f) + 8.0f;
        circ_r2 = (std::cos(GetTime()) + 1.0f) / 2.0f * (56.0f) + 8.0f;

        rec_o = (std::sin(GetTime() * 4.0f) + 1.0f) / 2.0f * 4.0f + 1.0f;
    }

    // Frames
    if(IsKeyPressed(KEY_Q)) {
        id_frame -= 1;
    }else if(IsKeyPressed(KEY_E)) {
        id_frame += 1;
    }

    // Rotation
    if(IsKeyDown(KEY_G)) {
        spr_rot += 90.0f * GetFrameTime();
    }else if(IsKeyDown(KEY_R)) {
        spr_rot -= 90.0f * GetFrameTime();
    }

    // Movement
    if(IsKeyDown(KEY_W)) {
        spr_y -= 128.0f * GetFrameTime() * spr_scaley;
    }else if(IsKeyDown(KEY_S)) {
        spr_y += 128.0f * GetFrameTime() * spr_scaley;
    }

    if(IsKeyDown(KEY_A)) {
        spr_x -= 128.0f * GetFrameTime() * spr_scalex;
    }else if(IsKeyDown(KEY_D)) {
        spr_x += 128.0f * GetFrameTime() * spr_scalex;
    }

    // Origin
    if(IsKeyPressed(KEY_Z)) {
        spr_test.origin = {0.0f, 0.0f};
    }else if(IsKeyPressed(KEY_X)) {
        spr_test.origin = {32.0f, 32.0f};
    }

    // Scale
    if(IsKeyDown(KEY_C)) {
        spr_scalex -= 1.0f * GetFrameTime();
        spr_scaley -= 1.0f * GetFrameTime();
    }else if(IsKeyDown(KEY_V)) {
        spr_scalex += 1.0f * GetFrameTime();
        spr_scaley += 1.0f * GetFrameTime();
    }

    // Ellipse outline
    if(IsKeyPressed(KEY_N)) {
        ell_o -= 1.0f;
    }else if(IsKeyPressed(KEY_M)) {
        ell_o += 1.0f;
    }

    // Roundrec radius
    if(IsKeyPressed(KEY_J)) {
        rrec_r -= 1.0f;
    }else if(IsKeyPressed(KEY_K)) {
        rrec_r += 1.0f;
    }
}

void Demo_Drawing::OnUnload() {
    UnloadTexture(tex_sprite);
}

Demo_Drawing::Demo_Drawing() : Game(
    GalaEngine::GameInfo {
        "GalaEngine Drawing Demo (GalaEngine v" GALAENGINE_VERSION_STRING ")",
        "GalaEngine example project.",
        "Colleen (colleen05)",

        1280, 720,

        "./res/"
    }
) {}