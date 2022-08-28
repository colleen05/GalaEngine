#include <GalaEngine/Surface.hpp>

GalaEngine::Surface::Surface(int width, int height) {
    Image img = GenImageColor(width, height, C_BLACK);

    texture = LoadTextureFromImage(img);

    UnloadImage(img);
}