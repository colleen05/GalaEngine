// Project: GalaEngine
// File: Demo_Scene.hpp
// Description: Scene testing
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <GalaEngine/EngineInfo.hpp>
#include <GalaEngine/Game.hpp>
#include <GalaEngine/Colour.hpp>
#include <GalaEngine/BackgroundLayer.hpp>
#include <GalaEngine/EntityLayer.hpp>
#include <GalaEngine/TileLayer.hpp>
#include <GalaEngine/Tileset.hpp>
#include <iostream>
#include <cmath>

#include <Ent_Ball.hpp>

class Demo_Scene : public GalaEngine::Game {
    public:
        Texture tex_bgSky;
        Texture tex_bgOverlay;

        GalaEngine::Tileset ts_test;

        GalaEngine::BackgroundLayer *lay_background0;
        GalaEngine::BackgroundLayer *lay_background1;
        GalaEngine::EntityLayer     *lay_entities;
        GalaEngine::BackgroundLayer *lay_foreground;
        GalaEngine::TileLayer *lay_tiles;

        Ent_Ball *ent_ball0, *ent_ball1, *ent_ball2, *ent_ball3;

        // Game class overrides
        void OnLoad();
        void OnDraw();
        void OnUpdate();
        void OnUnload();

        // Constructor
        Demo_Scene();
};