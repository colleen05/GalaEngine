#include <GalaEngine/Colour.hpp>

GalaEngine::Colour GalaEngine::Colour::Lerp(Colour colour, float t) {
    return Colour {
        (uint8_t)((float)r + t * (float)(colour.r - r)),
        (uint8_t)((float)g + t * (float)(colour.g - g)),
        (uint8_t)((float)b + t * (float)(colour.b - b)),
        (uint8_t)((float)a + t * (float)(colour.a - a))
    };
}

GalaEngine::Colour GalaEngine::Colour::Lerp(Colour c1, Colour c2, float t) {
    return c1.Lerp(c2, t);
}

Vector4 GalaEngine::Colour::Normalised() {
    return Vector4 {
        (float)(r) / 255.0f,
        (float)(g) / 255.0f,
        (float)(b) / 255.0f,
        (float)(a) / 255.0f
    };
}

Vector4 GalaEngine::Colour::Normalise(Colour colour) {
    return colour.Normalised();
}