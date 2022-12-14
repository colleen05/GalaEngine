// Project: GalaEngine
// File: Entity.hpp
// Description: Entity class
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <raylib.h>
#include <iostream>
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

            Vector2     worldMousePosition = {0.0f, 0.0f};
            Vector2     bboxSize = {32.0f, 32.0f};
            Rectangle   bbox = {0.0f, 0.0f, 32.0f, 32.0f};

            // Events
            virtual void OnSignal(std::string message);
            virtual void OnStart();
            virtual void OnUpdate();
            virtual void OnDraw();
            virtual void OnDestroy();

            Entity(int x, int y);
            Entity();
    };
}