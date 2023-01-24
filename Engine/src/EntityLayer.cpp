#include <GalaEngine/EntityLayer.hpp>

void GalaEngine::EntityLayer::AddEntity(GalaEngine::Entity *entity) {
    entity->layerSurface = surface;
    _entities.push_back(entity);
}

void GalaEngine::EntityLayer::RemoveEntity(const GalaEngine::Entity *entity) {
    _entities.erase(std::find(_entities.begin(), _entities.end(), entity));
}

void GalaEngine::EntityLayer::OnStart() {

}

void GalaEngine::EntityLayer::OnUpdate() {
    for(auto &e : _entities) {
        e->OnUpdate();
    }
}

void GalaEngine::EntityLayer::OnDraw(const GalaEngine::Camera &camera) {
    surface->Clear(); 

    for(auto &e : _entities) {
        surface->DrawSprite(
            *e->sprite, e->spriteFrame,
            e->position.x, e->position.y,
            e->scale.x, e->scale.y,
            e->rotation,
            e->blendColour
        );

        e->OnDraw();
    }
}

void GalaEngine::EntityLayer::OnDestroy() {

}

GalaEngine::EntityLayer::EntityLayer(const int width, const int height, const Colour clearColour) :
Layer(width, height, clearColour) { }