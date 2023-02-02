#include <GalaEngine/EntityLayer.hpp>

void GalaEngine::EntityLayer::AddEntity(GalaEngine::Entity *entity) {
    entity->layerSurface = surface;
    entities.push_back(entity);
}

void GalaEngine::EntityLayer::RemoveEntity(const GalaEngine::Entity *entity) {
    entities.erase(std::find(entities.begin(), entities.end(), entity));
}

void GalaEngine::EntityLayer::OnStart() {

}

void GalaEngine::EntityLayer::OnUpdate() {
    for(auto &e : entities) {
        e->OnUpdate();
    }
}

void GalaEngine::EntityLayer::OnDraw(const GalaEngine::Camera &camera) {
    surface->Clear(); 

    for(auto &e : entities) {
        surface->DrawSprite(
            *e->sprite, e->spriteFrame,
            e->position.x, e->position.y,
            e->scale.x, e->scale.y,
            e->rotation,
            e->blendColour
        );

        e->layerSurface = surface;
        e->OnDraw();
    }
}

void GalaEngine::EntityLayer::OnDestroy() {

}

GalaEngine::EntityLayer::EntityLayer(const int width, const int height, const Colour clearColour) :
Layer(width, height, clearColour) { }