#include <GalaEngine/EngineInfo.hpp>
#include <GalaEngine/Game.hpp>
#include <GalaEngine/Colour.hpp>
#include <iostream>
#include <cmath>

class MyGame : public GalaEngine::Game {
    public:
        Texture tex_sprite;
        GalaEngine::Sprite spr_test;
        GalaEngine::Colour clearColour = C_RED;

        int id_origin = 0,
            id_frame = 0;

        float   rotation = 0.0f,
                spr_x = 0.0f,
                spr_y = 0.0f,
                spr_scalex = 1.0f,
                spr_scaley = 1.0f;

        int keypresses_raylib = 0,
            keypresses_mymethod = 0;
        
        void OnLoad() {
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

        void OnDraw() {
            window->surface.Clear(clearColour);
            
            window->surface.DrawText("Frame: " + std::to_string(id_frame), 640, 8 + 20 * 0, 20, C_GALAWHITE);
            window->surface.DrawText("Origin: " + std::to_string(spr_test.origin.x) + ", " + std::to_string(spr_test.origin.y), 640, 8 + 20 * 1, 20, C_GALAWHITE);

            window->surface.DrawText("IsKeyPressed(KEY_SPACE): " + std::to_string(keypresses_raylib), 640, 8 + 20 * 3, 20, C_GALAWHITE);
            window->surface.DrawText("Manual: " + std::to_string(keypresses_mymethod), 640, 8 + 20 * 4, 20, C_GALAWHITE);

            window->surface.DrawSprite(spr_test, id_frame, spr_x, spr_y, spr_scalex, spr_scaley, rotation);

            window->surface.DrawText("FPS: " + std::to_string(1.0f / GetFrameTime()), 8.0f, 8.0f, 20);
        }

        void OnUpdate() {
            clearColour = GalaEngine::Colour::Lerp(Colours::GalaRed, Colours::GalaBlack, (std::sin(GetTime()) + 1.0f) / 2.0f);

            std::cout << std::to_string(clearColour.Normalised().x) << std::endl;

            if(IsKeyPressed(KEY_SPACE)) {
                keypresses_raylib += 1;
            }

            // Frames
            if(IsKeyPressed(KEY_Q)) {
                id_frame -= 1;
            }else if(IsKeyPressed(KEY_E)) {
                id_frame += 1;
            }

            // Rotation
            if(IsKeyDown(KEY_G)) {
                rotation += 90.0f * GetFrameTime();
            }else if(IsKeyDown(KEY_R)) {
                rotation -= 90.0f * GetFrameTime();
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
        }

        void OnUnload() {
            UnloadTexture(tex_sprite);
        }

        MyGame() : Game(
            GalaEngine::GameInfo {
                "GalaEngine Demo (GalaEngine v" GALAENGINE_VERSION_STRING ")",
                "GalaEngine example project.",
                "Colleen (colleen05)",

                1280, 720,

                "./res/"
            }
        ) {}
};

int main() {
    MyGame *game = new MyGame();
    game->Start();

    return 0;
}
