#include <GalaEngine/EngineInfo.hpp>
#include <GalaEngine/Game.hpp>
#include <GalaEngine/Colour.hpp>
#include <iostream>
#include <cmath>

class MyGame : public GalaEngine::Game {
    public:
        Texture tex_sprite;
        GalaEngine::Sprite spr_test;
        GalaEngine::Colour clearColour = C_GALARED;

        int id_origin = 0,
            id_frame = 0,
            spr_x = 0,
            spr_y = 0;

        float rotation = 0.0f;
        
        void OnLoad() {
            tex_sprite = LoadTexture("./res/tex/spr_test.png");

            spr_test = GalaEngine::Sprite {
                tex_sprite,
                {0.0f, 0.0f},
                std::vector<Rectangle> {
                    {0.0f, 0.0f,    64.0f, 64.0f},
                    {64.0f, 0.0f,   64.0f, 64.0f},
                    {0.0f, 64.0f,   64.0f, 64.0f},
                    {64.0f, 64.0f,  64.0f, 64.0f}
                }
            };
        }

        void OnDraw() {
            window->surface.Clear(clearColour);
            
            window->surface.DrawText("Frame: " + std::to_string(id_frame), 640, 8 + 20 * 0, 20, C_GALAWHITE);
            window->surface.DrawText("Origin: " + std::to_string(spr_test.origin.x) + ", " + std::to_string(spr_test.origin.y), 640, 8 + 20 * 1, 20, C_GALAWHITE);

            window->surface.DrawSprite(spr_test, id_frame, spr_x, spr_y, 1.0f, 1.0f, rotation);

            window->surface.DrawText("FPS: " + std::to_string(GetFPS()), 8.0f, 8.0f, 20);
        }

        void OnUpdate() {
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
            if(IsKeyDown(KEY_UP)) {
                spr_y -= 128.0f * GetFrameTime();
            }else if(IsKeyDown(KEY_DOWN)) {
                spr_y += 128.0f * GetFrameTime();
            }

            if(IsKeyDown(KEY_LEFT)) {
                spr_x -= 64.0f * GetFrameTime();
            }else if(IsKeyDown(KEY_RIGHT)) {
                spr_x += 64.0f * GetFrameTime();
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
    GalaEngine::Game *game = new MyGame();
    game->Start();

    return 0;
}
