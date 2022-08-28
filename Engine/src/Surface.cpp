#include <GalaEngine/Surface.hpp>

void GalaEngine::Surface::DrawText(std::string text, int x, int y, int size, Colour colour) {
    BeginTextureMode(texture);
    ::DrawText(text.c_str(), x, y, size, colour);
    EndTextureMode();
}

void GalaEngine::Surface::DrawSprite(Sprite sprite, int frame, int x, int y, float scaleX, float scaleY, float rotation, Colour blendColour) {

}

void GalaEngine::Surface::Clear(Colour colour) {
    BeginTextureMode(texture);
    ClearBackground(colour);
    EndTextureMode();
}

void GalaEngine::Surface::Clear() {
    BeginTextureMode(texture);
    ClearBackground(clearColour);
    EndTextureMode();
}

void GalaEngine::Surface::Update() {

}

Image GalaEngine::Surface::GetImage() {
    Image img = LoadImageFromTexture(texture.texture);
    ImageFlipVertical(&img);

    return img;
}

GalaEngine::Surface::Surface(int width, int height, Colour colour) {
    texture = LoadRenderTexture(width, height);
    clearColour = colour;
}

GalaEngine::Surface::Surface() {
    
}