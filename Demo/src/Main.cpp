#include <GalaEngine/EngineInfo.hpp>
#include <GalaEngine/Window.hpp>
#include <iostream>

int main() {
    std::cout << "Using " << GalaEngine::GetEngineInfo() << "." << std::endl;
    
    GalaEngine::Window window("GalaEngine Demo", 1280, 720);

    while(!window.ShouldClose()) {
        BeginDrawing();
        ClearBackground(SKYBLUE);
        EndDrawing();
    }

    window.Exit();
    
    return 0;
}