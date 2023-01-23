// Project: GalaEngine
// File: SoundManager.hpp
// Description: Sound management class for sound playback
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <string>
#include <map>
#include <raylib.h>

namespace GalaEngine {
    class SoundManager {
        public:
            // Playback control
            void Play(const Sound &sound, const float volume = 1.0f, const float pitch = 1.0f, const float pan = 0.0f, const bool multi = true);
            void Play(const Sound &sound, const bool multi);
            void Stop(const Sound &sound);
            void StopAll();
            void Pause(const Sound &sound);
            void Resume(const Sound &sound);

            // Status getters
            bool IsPlaying(const Sound &sound);

            // Constructor
            SoundManager();
    };
}