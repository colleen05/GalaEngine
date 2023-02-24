#include <GalaEngine/Camera.hpp>

GalaEngine::Camera::Camera(const int x, const int y, const int width, const int height) {
    this->position = Vector2 {
        (float)x, (float)y
    };
    
    this->size = Vector2 {
        (float)width, (float)height
    };
}

GalaEngine::Camera::Camera() { }