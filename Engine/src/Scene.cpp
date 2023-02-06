#include <GalaEngine/Scene.hpp>

void GalaEngine::Scene::PushEntity(GalaEngine::Entity *entity, const std::string &name) {
    if(entity == nullptr) return;

    entity->window  = window;
    entity->assets  = assets;
    entity->input   = input;
    entity->sound   = sound;

    if(!name.empty()) entities.insert_or_assign(name, entity);

    entity->OnStart();
}

GalaEngine::Entity *GalaEngine::Scene::GetEntity(const std::string &name) {
    const auto &it_ent = entities.find(name);
    if(it_ent == entities.end()) return nullptr;

    return (*it_ent).second;
}

void GalaEngine::Scene::RemoveEntity(const std::string &name, const bool destroy) {
    const auto &it_ent = entities.find(name);
    if(it_ent == entities.end()) return;

    if(destroy) delete (*it_ent).second;
    entities.erase(it_ent);
}

void GalaEngine::Scene::RemoveEntity(Entity *entity, const bool destroy) {
    const auto &it_ent = std::find_if(
        entities.begin(), entities.end(),
        [entity](const auto &e){
            return e.second == entity;
        }
    );

    if(it_ent == entities.end()) return;

    if(destroy) delete (*it_ent).second;
    entities.erase(it_ent);
}

size_t GalaEngine::Scene::PushLayer(Layer *layer, int position) {
    if( (position < 0) ||
        (position > layers.size())
    ) position = layers.size();

    layers.insert(layers.begin() + position, layer);

    layer->OnStart();

    return position;
}

GalaEngine::Layer *GalaEngine::Scene::GetLayer(const int position) {
    if((position < 0) || (position >= layers.size())) return nullptr;
    return layers[position];
}

void GalaEngine::Scene::RemoveLayer(const int position, const bool destroy) {
    if((position < 0) || (position >= layers.size())) return;

    if(destroy) delete layers[position];
    layers.erase(layers.begin() + position);
}

void GalaEngine::Scene::RemoveLayer(Layer *layer, const bool destroy) {
    size_t layerPos = 0;

    for(int i = 0; i < layers.size(); i++) {
        if(layers[i] == layer) {
            if(destroy) delete layers[i];
            layers.erase(layers.begin() + i);
            return;
        }
    }
}

GalaEngine::BackgroundLayer *GalaEngine::Scene::AddBackgroundLayer(const Texture texture, const Colour clearColour, const int position) {
    auto layer = new GalaEngine::BackgroundLayer(_width, _height, texture, clearColour);
    PushLayer(layer, position);
    return layer;
}

GalaEngine::EntityLayer *GalaEngine::Scene::AddEntityLayer(const Colour clearColour, const int position) {
    auto layer = new GalaEngine::EntityLayer(_width, _height, clearColour);
    PushLayer(layer, position);
    return layer;
}

GalaEngine::TileLayer *GalaEngine::Scene::AddTileLayer(const Tileset &tileset, const std::vector<uint16_t> &tiles, const int width, const int height, const Colour clearColour, const int position){
    auto layer = new GalaEngine::TileLayer(tileset, tiles, width, height, clearColour);
    PushLayer(layer, position);
    return layer;
}

void GalaEngine::Scene::Resize(const int width, const int height, const bool resizeLayers) {
    _width = width;
    _height = height;

    if(resizeLayers) {
        for(const auto &layer : layers)
            layer->surface->Resize(width, height);
    }
}

void GalaEngine::Scene::Update() {
    for(auto &e : entities) {
        auto &ent = e.second;

        ent->worldMousePosition = Vector2 {
            (float) (GetMouseX()) / GetScreenWidth()  * mainCamera.size.x + mainCamera.position.x,
            (float) (GetMouseY()) / GetScreenHeight() * mainCamera.size.y + mainCamera.position.y
        };

        ent->bbox = Rectangle {
            ent->position.x,
            ent->position.y,
            ent->bboxSize.x,
            ent->bboxSize.y
        };
    }

    for(auto &layer : layers) {
        layer->OnUpdate();
    }
}

void GalaEngine::Scene::RenderLayers() {
    if(targetSurface == nullptr) return;

    for(const auto &layer : layers) {
        auto &layerTexture = layer->surface->renderTexture.texture;

        layer->OnDraw(mainCamera);

        BeginTextureMode(targetSurface->renderTexture);
        DrawTexturePro(
            layerTexture,
            Rectangle {
                std::floor(mainCamera.position.x),
                layerTexture.height - (mainCamera.size.y + std::floor(mainCamera.position.y)),
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
            layer->blendColour
        );
        EndTextureMode();
    }
}

GalaEngine::Scene::Scene(Surface *targetSurface, const int width, const int height) {
    this->targetSurface = targetSurface;
    this->_width        = width;
    this->_height       = height;
}

GalaEngine::Scene::Scene() {

}