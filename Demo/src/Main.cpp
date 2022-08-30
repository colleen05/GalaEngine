#include <GalaEngine/EngineInfo.hpp>
#include <GalaEngine/Game.hpp>
#include <GalaEngine/Colour.hpp>
#include <iostream>
#include <cmath>

#include <Demo_Drawing.hpp>

int main() {
    GalaEngine::Game *game = new Demo_Drawing();
    game->Start();

    return 0;
}
