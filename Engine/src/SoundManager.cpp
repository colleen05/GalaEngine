#include <GalaEngine/SoundManager.hpp>

// Playback control
void GalaEngine::SoundManager::Play(const Sound &sound, const float volume, const float pitch, const float pan, const bool multi) {
    // Setup sound options
    SetSoundVolume(sound, volume);
    SetSoundPitch(sound, pitch);
    SetSoundPan(sound, (pan / 2.0f) + 0.5f);

    // Play sound
    if(multi)   PlaySoundMulti(sound);
    else        PlaySound(sound);
}

void GalaEngine::SoundManager::Play(const Sound &sound, const bool multi) {
    Play(sound, 1.0f, 1.0f, 0.0f, multi);
}

void GalaEngine::SoundManager::Stop(const Sound &sound) {
    StopSound(sound);
}

void GalaEngine::SoundManager::StopAll() {
    StopSoundMulti();
}

void GalaEngine::SoundManager::Pause(const Sound &sound) {
    PauseSound(sound);
}

void GalaEngine::SoundManager::Resume(const Sound &sound) {
    ResumeSound(sound);
}


// Status getters
bool GalaEngine::SoundManager::IsPlaying(const Sound &sound) {
    return IsSoundPlaying(sound);
}


// Constructors
GalaEngine::SoundManager::SoundManager() { }