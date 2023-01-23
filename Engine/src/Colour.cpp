#include <GalaEngine/Colour.hpp>

GalaEngine::Colour GalaEngine::Colour::Lerp(Colour c1, Colour c2, const float t) {
    return c1.Lerp(c2, t);
}

Vector4 GalaEngine::Colour::Normalise(Colour colour) {
    return colour.Normalised();
}