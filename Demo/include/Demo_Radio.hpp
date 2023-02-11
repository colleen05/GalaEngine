// Project: GalaEngine Demo
// File: Demo_Radio.hpp
// Description: Sound management demo.
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <GalaEngine/EngineInfo.hpp>
#include <GalaEngine/Game.hpp>
#include <GalaEngine/Colour.hpp>
#include <iostream>
#include <cmath>

class Demo_Radio : public GalaEngine::Game {
    public:
        struct TrackListing {
            std::string name;
            int length;
            GalaEngine::Colour c1, c2;
        };

        std::map<std::string, TrackListing> trackListings;
        std::string currentTrack = "";

        GalaEngine::Sprite *spr_button;

        bool isPlaying = false;

        // Game class overrides
        void OnLoad();
        void OnDraw();
        void OnUpdate();
        void OnUnload();

        // Etc..
        void LoadTrack(const TrackListing &track);

        // GUI
        void GUI_DrawAlbum(const TrackListing &track, const int x, const int y, const int size = 256);
        void GUI_ListItem(const TrackListing &track, const int x, const int y);
        void GUI_BackButton();
        void GUI_PlayButton();
        void GUI_ForwardButton();

        // Constructor
        Demo_Radio();
};