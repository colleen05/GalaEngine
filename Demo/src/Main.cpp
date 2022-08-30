#include <GalaEngine/EngineInfo.hpp>
#include <GalaEngine/Game.hpp>
#include <GalaEngine/Colour.hpp>
#include <iostream>
#include <cmath>

#include <Demo_Drawing.hpp>

int main() {
    GalaEngine::Game *game = nullptr;

    InitWindow(640, 480, "GalaEngine Demos");
    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        // Logic
        if(IsKeyPressed(KEY_ONE)) {
            game = new Demo_Drawing();
        }

        // Drawing
        BeginDrawing();
        ClearBackground(C_BLACK);

        DrawText("[1] - Surface functions.", 8, 16, 20, C_WHITE);

        EndDrawing();

        // If demo is selected...
        if(game != nullptr) {
            CloseWindow();
            game->Start();
        }
    }

    return 0;
}
