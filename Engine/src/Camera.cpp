#include <GalaEngine/Camera.hpp>

void GalaEngine::Camera::SetSize(const float width, const float height) {
    _size = { width, height };
    surface->Resize(width, height);
}

Vector2 GalaEngine::Camera::GetSize() {
    return _size;
}

GalaEngine::Camera::Camera(const int x, const int y, const int width, const int height) {
    this->position = Vector2 { (float)x, (float)y };
    this->_size = Vector2 { (float)width, (float)height };

    this->surface = new Surface(width, height, C_CLEAR);
}

GalaEngine::Camera::Camera() { }