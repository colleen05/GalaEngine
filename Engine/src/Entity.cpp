#include <GalaEngine/Entity.hpp>

void GalaEngine::Entity::OnSignal   (std::string message)   {}
void GalaEngine::Entity::OnStart    () {}
void GalaEngine::Entity::OnUpdate   () {}
void GalaEngine::Entity::OnDraw     () {}
void GalaEngine::Entity::OnDestroy  () {}

GalaEngine::Entity::Entity(int x, int y) {
    position = Vector2 {(float)x, (float)y};
}

GalaEngine::Entity::Entity() : Entity(0, 0) { }