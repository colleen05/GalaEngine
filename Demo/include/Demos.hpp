// Project: GalaEngine Demo
// File: Demos.hpp
// Description: Demo classes.
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <GalaEngine/EngineInfo.hpp>
#include <GalaEngine/Game.hpp>
#include <GalaEngine/Colour.hpp>
#include <iostream>
#include <cmath>

class Demo_Drawing : public GalaEngine::Game {
    public:
        // Variables
        Texture tex_sprite;
        GalaEngine::Sprite spr_test;
        GalaEngine::Colour clearColour = C_RED;

        int id_origin = 0,
            id_frame = 0;

        float   spr_rot = 0.0f,
                spr_x = 0.0f,
                spr_y = 0.0f,
                spr_scalex = 1.0f,
                spr_scaley = 1.0f,
                rec_x = 0.0f,
                rec_y = 232.0f,
                rec_o = 1.0f,
                rec_rot = 0.0f,
                circ_x = 0.0f,
                circ_x2 = 0.0f,
                circ_y = 720.0f - 128.0f,
                circ_r = 64.0f,
                circ_r2 = 64.0f,
                ell_o = 1.0f,
                rrec_r = 8.0f;

        int keypresses_raylib = 0,
            keypresses_mymethod = 0;

        // Game class overrides
        void OnLoad();
        void OnDraw();
        void OnUpdate();
        void OnUnload();

        // Constructor
        Demo_Drawing();
};