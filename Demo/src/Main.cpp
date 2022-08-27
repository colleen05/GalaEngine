#include <GalaEngine/EngineInfo.hpp>
#include <GalaEngine/Game.hpp>
#include <GalaEngine/Colour.hpp>
#include <iostream>
#include <cmath>

class MyGame : public GalaEngine::Game {
    public:
        Vector2 textPos = {32.0f, 0.0f};

        void OnDraw() {
            ClearBackground(C_PURPLE);
            DrawText("Hello, world!", textPos.x, textPos.y, 40, C_WHITE);
        }

        void OnUpdate() {
            textPos.x += GetMouseWheelMove() * 64.0f;
            textPos.y = (std::sin(GetTime()) + 1.0f) / 2.0f * 680.0f;
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
    std::cout << "Using " << GalaEngine::GetEngineInfo() << "." << std::endl;

    GalaEngine::Game *game = new MyGame();
    game->Start();

    return 0;
}