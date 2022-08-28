#include <GalaEngine/EngineInfo.hpp>
#include <GalaEngine/Game.hpp>
#include <GalaEngine/Colour.hpp>
#include <iostream>
#include <vector>
#include <cmath>

class MyGame : public GalaEngine::Game {
    public:
        void OnDraw() {
            
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
    std::cout << "Using " << GalaEngine::GetEngineInfo() << "." << std::endl;

    GalaEngine::Game *game = new MyGame();
    game->Start();

    return 0;
}