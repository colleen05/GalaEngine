#include <GalaEngine/EngineInfo.hpp>
#include <GalaEngine/Window.hpp>
#include <GalaEngine/Colour.hpp>
#include <iostream>

int main() {
    std::cout << "Using " << GalaEngine::GetEngineInfo() << "." << std::endl;

    GalaEngine::Window window("GalaEngine Demo", 1280, 720);
    window.Init();

    while(!window.ShouldClose()) {
        BeginDrawing();
        ClearBackground(C_BLACK);
        EndDrawing();
    }

    window.Exit();
    
    return 0;
}