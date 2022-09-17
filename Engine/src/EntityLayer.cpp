#include <GalaEngine/EntityLayer.hpp>

void GalaEngine::EntityLayer::AddEntity(GalaEngine::Entity *entity) {
    _entities.push_back(entity);
}

void GalaEngine::EntityLayer::RemoveEntity(GalaEngine::Entity *entity) {
    _entities.erase(std::find(_entities.begin(), _entities.end(), entity));
}

void GalaEngine::EntityLayer::OnStart() {

}

void GalaEngine::EntityLayer::OnUpdate() {
    for(auto &e : _entities) {
        e->OnUpdate();
    }
}

void GalaEngine::EntityLayer::OnDraw(GalaEngine::Camera camera) {
    for(auto &e : _entities) {
        surface->DrawSprite(
            *e->sprite, e->spriteFrame,
            e->position.x, e->position.y,
            e->scale.x, e->scale.y,
            e->rotation,
            e->blendColour
        );
    }
}

void GalaEngine::EntityLayer::OnDestroy() {

}

GalaEngine::EntityLayer::EntityLayer(int width, int height, Colour clearColour) :
Layer(width, height, clearColour) {

}