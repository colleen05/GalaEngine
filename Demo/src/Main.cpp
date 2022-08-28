#include <GalaEngine/EngineInfo.hpp>
#include <GalaEngine/Game.hpp>
#include <GalaEngine/Colour.hpp>
#include <iostream>

class MyGame : public GalaEngine::Game {
    public:
        void OnDraw() {
            window->surface.Clear(C_GALARED);
            window->surface.DrawText("Hello, world!", 32, 32);
        }

        void OnUpdate() {
            
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
