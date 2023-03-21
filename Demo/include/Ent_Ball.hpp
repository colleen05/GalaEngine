// Project: GalaEngine
// File: Ent_Ball.hpp
// Description: Custom "ball" entity for demonstration.
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <GalaEngine/Entity.hpp>

class Ent_Ball : public GalaEngine::Entity {
    public:
        Vector2 velocity = {0.0f, 0.0f};

        void OnStart();
        void OnUpdate();
        void OnDraw();

        Ent_Ball(int x, int y);
        Ent_Ball();
};