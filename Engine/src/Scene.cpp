#include <GalaEngine/Scene.hpp>

std::shared_ptr<GalaEngine::Camera> GalaEngine::Scene::GetCamera(const int id) {
    if(id < 0 || id >= cameras.size()) return std::shared_ptr<GalaEngine::Camera>(nullptr);
    return cameras[id];
}

size_t GalaEngine::Scene::PushCamera(std::shared_ptr<GalaEngine::Camera> camera, int position) {
    if(position < -1 || position >= cameras.size()) position = cameras.size();
    if(position == -1) position = cameras.size();

    cameras.insert(cameras.begin() + position, camera);
    return position;
}

void GalaEngine::Scene::RemoveCamera(int position) {
    if(position < -1 || position >= cameras.size()) return;
    if(position == -1) position = cameras.size() - 1;

    cameras.erase(cameras.begin() + position);
}

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

    targetSurface->Resize(width, height);
}

Vector2 GalaEngine::Scene::GetSize() {
    return Vector2 {(float)_width, (float)_height};
}

void GalaEngine::Scene::Update() {
    for(auto &e : entities) {
        auto &ent = e.second;

        const Vector2 cameraSize = cameras[0]->GetSize();

        ent->sceneMousePosition = Vector2 {
            (float) (GetMouseX()) / GetScreenWidth()  * cameraSize.x + cameras[0]->position.x,
            (float) (GetMouseY()) / GetScreenHeight() * cameraSize.y + cameras[0]->position.y
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

    // Update scene context members
    for(auto &[name, ent] : entities) {
        ent->sceneWidth = _width;
        ent->sceneHeight = _height;
        ent->sceneEntities = &entities;
        ent->sceneLayers = &layers;
    }
}

void GalaEngine::Scene::RenderLayers() {
    if(targetSurface == nullptr) return;
    if(cameras.empty()) return;

    for(auto &camera : cameras) {
        if(!camera->visible) continue;

        auto            &cameraTexture      = camera->surface->renderTexture;
        const Vector2   cameraPosition      = camera->position;
        const Vector2   cameraSize          = camera->GetSize();
        const Rectangle cameraScreenport    = camera->screenport;

        for(const auto &layer : layers) {
            auto &layerTexture = layer->surface->renderTexture.texture;
            
            layer->OnDraw(*camera);

            BeginTextureMode(cameraTexture);
            DrawTexturePro(
                layerTexture,
                Rectangle {
                    std::floor(cameraPosition.x),
                    layerTexture.height - (cameraSize.y + std::floor(cameraPosition.y)),
                    cameraSize.x,
                    -cameraSize.y
                },
                Rectangle {
                    0.0f,
                    0.0f,
                    (float)cameraTexture.texture.width,
                    (float)cameraTexture.texture.height
                },
                {0.0f, 0.0f},
                0.0f,
                layer->blendColour
            );
            EndTextureMode();
        }

        // Copy camera texture to target surface
        BeginTextureMode(targetSurface->renderTexture);
        DrawTexturePro(
            cameraTexture.texture,
            Rectangle {
                0, cameraSize.y,
                cameraSize.x, -cameraSize.y
            },
            Rectangle {
                cameraScreenport.x,
                cameraScreenport.y,
                (float)cameraScreenport.width,
                (float)cameraScreenport.height
            },
            {0.0f, 0.0f},
            0.0f,
            C_WHITE
        );
        EndTextureMode();
    }
}

GalaEngine::Scene::Scene(Surface *targetSurface, const int width, const int height) {
    this->targetSurface = targetSurface;
    this->_width        = width;
    this->_height       = height;
}

GalaEngine::Scene::Scene() { }

GalaEngine::Scene::~Scene() {
    cameras.clear();
}