#include <GalaEngine/Layer.hpp>

void GalaEngine::Layer::OnStart     () {}
void GalaEngine::Layer::OnUpdate    () {}
void GalaEngine::Layer::OnDraw      (const GalaEngine::Camera &camera) {}
void GalaEngine::Layer::OnDestroy   () {}

GalaEngine::Layer::Layer(const Surface *surface) {
    surface = surface;
}

GalaEngine::Layer::Layer(const int width, const int height, const Colour clearColour) {
    surface = new Surface(width, height, clearColour);
    OnStart();
}

GalaEngine::Layer::Layer() : Layer(256, 256, C_BLACK) {}

GalaEngine::Layer::~Layer() {
    surface->Destroy();
}