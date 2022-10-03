#include <GalaEngine/BackgroundLayer.hpp>

void GalaEngine::BackgroundLayer::OnStart() {
    
}

void GalaEngine::BackgroundLayer::OnUpdate() {
    offset.x += scrollSpeed.x * GetFrameTime();
    offset.y += scrollSpeed.y * GetFrameTime();
}

void GalaEngine::BackgroundLayer::OnDraw(GalaEngine::Camera camera) {
    surface->Clear();
    
    surface->DrawTexture(
        background,
        Rectangle {
            offset.x, offset.y,
            (float)surface->renderTexture.texture.width * scale.x,
            (float)surface->renderTexture.texture.height * scale.y
        },
        Rectangle {
            0.0f, 0.0f,
            (float)surface->renderTexture.texture.width,
            (float)surface->renderTexture.texture.height
        }
    );
}

void GalaEngine::BackgroundLayer::OnDestroy() {
    
}

GalaEngine::BackgroundLayer::BackgroundLayer(
    int width, int height,
    Texture background, Colour clearColour
) : Layer(width, height, clearColour) {
    this->background = background;
}

GalaEngine::BackgroundLayer::BackgroundLayer() : Layer() {}