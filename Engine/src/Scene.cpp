#include <GalaEngine/Scene.hpp>

void GalaEngine::Scene::PushLayer(Layer *layer) {
    _layers.insert(std::pair<uint8_t, Layer*>(
        _layers.size(),
        layer
    ));

    layer->OnStart();
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
                0.0f, (float)layerTexture.height,
                (float)layerTexture.width,
                -(float)layerTexture.height
            },
            Rectangle {
                0.0f, 0.0f,
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

GalaEngine::Scene::Scene(Surface *targetSurface) {
    this->targetSurface = targetSurface;
}

GalaEngine::Scene::Scene() {

}