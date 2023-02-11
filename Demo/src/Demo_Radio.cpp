#include <Demo_Radio.hpp>

void Demo_Radio::OnLoad() {
    LoadTrack({"bgm_jam",    0, {0xff, 0x55, 0x00, 0x55}, {0xff, 0x00, 0xaa, 0x55}});
    LoadTrack({"bgm_techno", 0, {0x00, 0xaa, 0xff, 0x55}, {0xaa, 0x00, 0xff, 0x55}});
    LoadTrack({"bgm_ooo",    0, {0xaa, 0xff, 0x00, 0x55}, {0x00, 0xaa, 0x00, 0x55}});
    LoadTrack({"bgm_weird",  0, {0x00, 0xaa, 0xff, 0x55}, {0x00, 0xff, 0x55, 0x55}});

    spr_button = assets->LoadSprite("ui_radio_button");
}

void Demo_Radio::OnDraw() {
    window->surface.DrawTexture(assets->GetTexture("bg_radio"), 0, 0);

    size_t items = 0;
    for(const auto &[name, item] : trackListings) {
        GUI_ListItem(item, 32, 96 + (80 * items));
        items++;
    }

    if(trackListings.find(currentTrack) != trackListings.end()) {
        const auto &track = trackListings[currentTrack];
        const auto &curSound = assets->GetSound(currentTrack);

        uint8_t alpha = Clamp(128 + (sin(GetTime() * 2.0f) + 1.0f) / 2 * 128, 0, 255);

        window->surface.DrawTexture(assets->GetTexture("ui_radio_status"), 464, 96, 1.0f, 1.0f, 0.0f, {0xff, 0xff, 0xff, alpha});
        GUI_DrawAlbum(track, 488, 152);
        window->surface.DrawText(currentTrack, 488, 416, 20, Colours::Aqua);

        GUI_BackButton();
        GUI_PlayButton();
        GUI_ForwardButton();
    }
}

void Demo_Radio::OnUpdate() {
}

void Demo_Radio::OnUnload() {

}

void Demo_Radio::LoadTrack(const TrackListing &track) {
    const auto &snd = assets->LoadSound(track.name);
    trackListings.emplace(track.name, track);
}

void Demo_Radio::GUI_DrawAlbum(const TrackListing &track, const int x, const int y, const int size) {
    const float scale = (float)size / 256.0f;

    window->surface.DrawTexture(
        assets->GetTexture("ui_radio_album"),
        x, y, scale, scale
    );

    const auto midColour = GalaEngine::Colour::Lerp(track.c1, track.c2, 0.5f);
    window->surface.DrawRectangleColours(x, y, size, size, track.c1, midColour, track.c2, midColour);
}

void Demo_Radio::GUI_ListItem(const TrackListing &track, const int x, const int y) {
    const bool hovered = CheckCollisionPointRec(
        GetMousePosition(),
        Rectangle {(float)x, (float)y, 400.0f, 80.0f}
    );

    window->surface.DrawTexture(assets->GetTexture("ui_radio_item"), x, y);
    window->surface.DrawText(track.name, x + 96, y + 32, 20, (track.name == currentTrack) ? Colours::Aqua : Colours::White);

    GUI_DrawAlbum(track, x + 4, y + 4, 72);

    if(hovered) {
        window->surface.DrawTexture(assets->GetTexture("ui_radio_item"), x, y);

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            const auto &curSound = assets->GetSound(currentTrack);
            sound->Stop(curSound);

            currentTrack = track.name;
            sound->Play(assets->GetSound(track.name), false);
        }
    }
}

void Demo_Radio::GUI_BackButton() {
    const auto &[firstName, firstTrack] = *trackListings.begin();

    const float alpha = (currentTrack == firstName) ? 0.5f : 1.0f;
    window->surface.DrawSprite(*spr_button, 2, 528, 480, 1.0f, 1.0f, 0.0f, {0xff, 0xff, 0xff, (uint8_t)(alpha * 255)});

    if(currentTrack == firstName) return;

    if( IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        CheckCollisionPointRec(GetMousePosition(), {528.0f, 480.0f, 48.0f, 48.0f})
    ) {
        const auto &curSound = assets->GetSound(currentTrack);
        sound->Stop(curSound);
        
        const auto &track = *(--trackListings.find(currentTrack));
        currentTrack = track.first;
        sound->Play(assets->GetSound(track.first), false);
    }
}

void Demo_Radio::GUI_PlayButton() {
    const auto &curSound = assets->GetSound(currentTrack);

    window->surface.DrawSprite(*spr_button, sound->IsPlaying(curSound) ? 0 : 1, 592, 480);

    if( IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        CheckCollisionPointRec(GetMousePosition(), {592.0f, 480.0f, 48.0f, 48.0f})
    ) {
        if(sound->IsPlaying(curSound)) {
            sound->Pause(curSound);
        } else {
            sound->Resume(curSound);
        }
    }
}

void Demo_Radio::GUI_ForwardButton() {
    const auto &[lastName, lastTrack]   = *(--trackListings.end());

    const float alpha = (currentTrack == lastName) ? 0.5f : 1.0f;
    window->surface.DrawSprite(*spr_button, 3, 656, 480, 1.0f, 1.0f, 0.0f, {0xff, 0xff, 0xff, (uint8_t)(alpha * 255)});

    if(currentTrack == lastName) return;

    if( IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        CheckCollisionPointRec(GetMousePosition(), {656.0f, 480.0f, 48.0f, 48.0f})
    ) {
        const auto &curSound = assets->GetSound(currentTrack);
        sound->Stop(curSound);

        const auto &track = *(++trackListings.find(currentTrack));
        currentTrack = track.first;
        sound->Play(assets->GetSound(track.first), false);
    }
}

Demo_Radio::Demo_Radio() : Game(
    GalaEngine::GameInfo {
        "GalaEngine Radio (GalaEngine v" GALAENGINE_VERSION_STRING ")",
        "GalaEngine example project.",
        "Colleen (colleen05)",

        800, 600,

        GalaEngine::AssetPathLayout {
            "./resources/",
            "textures/",
            "sprites/",
            "tilesets/",
            "sounds/",
            "fonts/"
        }
    }
) {}