#include <GalaEngine/Layer.hpp>

void GalaEngine::Layer::OnStart     () {}
void GalaEngine::Layer::OnUpdate    () {}
void GalaEngine::Layer::OnDraw      (GalaEngine::Camera camera) {}
void GalaEngine::Layer::OnDestroy   () {}

GalaEngine::Layer::Layer(Surface *surface) {
    surface = surface;
}

GalaEngine::Layer::Layer(int width, int height, Colour clearColour) {
    surface = new Surface(width, height, clearColour);
    OnStart();
}

GalaEngine::Layer::Layer() : Layer(256, 256, C_BLACK) {}

GalaEngine::Layer::~Layer() {
    surface->Destroy();
}