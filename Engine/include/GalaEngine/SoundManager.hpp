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
    /*! @brief Sound management class
     *  @details Provides an interface for sound playback.
     */
    class SoundManager {
        public:
            /*! @name Playback Control
             *  @details Use these functions to control the playback of sounds.
             */
            /// @{
            /*! @brief Play a sound.
             *  @details Plays back a sound with supplied parameters.
             *  @param sound The sound to play.
             *  @param volume The volume of which to play the sound (0.0f = silent; 1.0f = source volume).
             *  @param pitch The putch of which to play the sound (0.0f = 0Hz; 1.0 = source pitch).
             *  @param pan The pan (ratio of left:right volume) of which to play the sound (-1.0f = left; 0.0f = centre; 1.0f = right).
             *  @param multi Whether or not multiple of this sound may be played.
             *  @note A sound must be **multi** to be paused and resumed.
             */
            void Play(const Sound &sound, const float volume = 1.0f, const float pitch = 1.0f, const float pan = 0.0f, const bool multi = true);
            /*! @brief Play a sound.
             *  @details Plays a sound with default parameters, with explicit
             *  **multi**.
             *  @param sound The sound to play.
             *  @param multi Whether or not multiple of this sound may be played.
             */
            void Play(const Sound &sound, const bool multi);
            /*! @brief Stop a sound.
             *  @details Stops the playback of a currently playing sound.
             *  @param sound The sound to stop.
             *  @note Sounds played as **multi** cannot be stopped.
             */
            void Stop(const Sound &sound);
            /*! @brief Stop all sounds.
             *  @details Stops the playback all of the currently playing
             *  sounds.
             */
            void StopAll();
            /*! @brief Pause a sound.
             *  @details Pauses the playback of a currently playing sound.
             *  @param sound The sound the pause.
             *  @note Sounds played as **multi** cannot be paused.
             */
            void Pause(const Sound &sound);
            /*! @brief Resume a sound.
             *  @details Resumes a paused sound's playback.
             *  @param sound The sound to resume.
             */
            void Resume(const Sound &sound);
            /// @}

            /*! @name Getters
             *  @details Use these functions to get the state of sounds.
             */
            /// @{
            /*! @brief Get if sound is playing.
             *  @details Get if a sound is currently playing.
             *  @param sound The sound to check.
             *  @returns **true** if the sound is playing.
             *  @note Sounds played as **multi** cannot be checked.
             */
            bool IsPlaying(const Sound &sound);
            /// @}

            /*! @brief Constructor
             *  @details Constructs the SoundManager.
             */
            SoundManager();
    };
}