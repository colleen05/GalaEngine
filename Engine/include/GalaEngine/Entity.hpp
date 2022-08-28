// Project: GalaEngine
// File: Entity.hpp
// Description: Entity class
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <raylib.h>
#include <GalaEngine/Sprite.hpp>
#include <GalaEngine/Colour.hpp>

namespace GalaEngine {
    class Entity {
        public:
            Vector2 position;
            Sprite *sprite;
            Colour blendColour;

            virtual void OnStart();
            virtual void OnUpdate();
            virtual void OnDraw();
            virtual void OnDestroy();

            Entity();
    };
}