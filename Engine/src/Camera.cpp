#include <GalaEngine/Camera.hpp>

GalaEngine::Camera::Camera(int x, int y, int width, int height) {
    this->position = Vector2 {
        (float)x, (float)y
    };
    
    this->size = Vector2 {
        (float)width, (float)height
    };
}

GalaEngine::Camera::Camera() {

}