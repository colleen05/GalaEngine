#include <iostream>
#include <GalaEngine/EngineInfo.hpp>

int main() {
    std::cout << "Using " << GalaEngine::GetEngineInfo() << "." << std::endl;
    return 0;
}