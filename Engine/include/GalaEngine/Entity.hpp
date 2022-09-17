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
            Vector2 position    = {0.0f, 0.0f};
            Vector2 scale       = {1.0f, 1.0f};
            float   rotation    = 0.0f;

            Sprite *sprite      = nullptr;
            int     spriteFrame = 0;
            Colour  blendColour = C_WHITE;

            virtual void OnStart();
            virtual void OnUpdate();
            virtual void OnDraw();
            virtual void OnDestroy();

            Entity();
    };
}