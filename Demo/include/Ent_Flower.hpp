// Project: GalaEngine
// File: Ent_Flower.hpp
// Description: Custom "flower" entity for demonstration.
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <GalaEngine/Entity.hpp>

class Ent_Flower : public GalaEngine::Entity {
    public:
        void OnStart();
        void OnUpdate();

        Ent_Flower(int x, int y);
        Ent_Flower();
};