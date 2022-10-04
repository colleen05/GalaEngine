#include <GalaEngine/Scene.hpp>

uint32_t GalaEngine::Scene::PushEntity(GalaEngine::Entity *entity, std::string name) {
    uint32_t id = _entities.size();

    entity->assets = assets;
    _entities.insert(std::pair<uint32_t, Entity*>(id, entity));

    if(!name.empty()) _entityNames.insert_or_assign(name, id);

    entity->OnStart();

    return id;
}

GalaEngine::Entity *GalaEngine::Scene::GetEntity(std::string name) {
    auto ent = _entityNames.find(name);
    return (ent != _entityNames.end()) ? _entities[(*ent).second] : nullptr;
}

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

GalaEngine::EntityLayer *GalaEngine::Scene::AddEntityLayer(Colour clearColour, int position) {
    auto layer = new GalaEngine::EntityLayer(_width, _height, clearColour);
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
    for(auto &e : _entities) {
        auto &ent = e.second;

        ent->worldMousePosition = Vector2 {
            (float) (GetMouseX()) / GetScreenWidth()  * mainCamera.size.x + mainCamera.position.x,
            (float) (GetMouseY()) / GetScreenHeight() * mainCamera.size.y + mainCamera.position.y
        };

        ent->bbox = Rectangle {ent->position.x, ent->position.y, ent->bboxSize.x, ent->bboxSize.y};
    }

    for(auto &p : _layers) {
        p.second->OnUpdate();
    }
}

void GalaEngine::Scene::RenderLayers() {
    if(targetSurface == nullptr) return;

    for(auto &p : _layers) {
        auto &layerTexture = p.second->surface->renderTexture.texture;

        p.second->OnDraw(mainCamera);

        BeginTextureMode(targetSurface->renderTexture);
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
                (float)targetSurface->renderTexture.texture.width,
                (float)targetSurface->renderTexture.texture.height
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