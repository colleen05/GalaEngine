#include <GalaEngine/Scene.hpp>

void GalaEngine::Scene::PushLayer(Layer *layer, int position) {
    _layers.insert(std::pair<uint8_t, Layer*>(
        (position >= 0) ? position : _layers.size(),
        layer
    ));

    layer->OnStart();
}

GalaEngine::BackgroundLayer *GalaEngine::Scene::AddBackgroundLayer(Texture texture, Colour clearColour, int position) {
    auto layer = new GalaEngine::BackgroundLayer(_width, _height, texture, clearColour);
    PushLayer(layer, position);
    return layer;
}

GalaEngine::TileLayer *GalaEngine::Scene::AddTileLayer(Tileset tileset, std::vector<uint16_t> tiles, int width, int height, Colour clearColour, int position){
    auto layer = new GalaEngine::TileLayer(tileset, tiles, width, height);
    PushLayer(layer, position);
    return layer;
}

void GalaEngine::Scene::Resize(int width, int height) {
    _width = width;
    _height = height;
}

void GalaEngine::Scene::Update() {
    for(auto &p : _layers) {
        p.second->OnUpdate();
    }
}

void GalaEngine::Scene::RenderLayers() {
    if(targetSurface == nullptr) return;

    for(auto &p : _layers) {
        auto &layerTexture = p.second->surface->texture.texture;

        p.second->OnDraw(mainCamera);

        BeginTextureMode(targetSurface->texture);
        DrawTexturePro(
            layerTexture,
            Rectangle {
                mainCamera.position.x,
                layerTexture.height - (mainCamera.size.y + mainCamera.position.y),
                mainCamera.size.x,
                -mainCamera.size.y
            },
            Rectangle {
                0.0f,
                0.0f,
                (float)targetSurface->texture.texture.width,
                (float)targetSurface->texture.texture.height
            },
            {0.0f, 0.0f},
            0.0f,
            p.second->blendColour
        );
        EndTextureMode();
    }
}

GalaEngine::Scene::Scene(Surface *targetSurface, int width, int height) {
    this->targetSurface = targetSurface;
    this->_width        = width;
    this->_height       = height;
}

GalaEngine::Scene::Scene() {

}