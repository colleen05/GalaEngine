#include <Demo_Fonts.hpp>

void Demo_Fonts::OnLoad() {
    font = assets->LoadFont("Pointfree");
}

void Demo_Fonts::OnDraw() {
    window->surface.Clear(bgColour);

    const std::string displayString = "File | Edit | Build | View | Help\n\nGalaEngine Font Demo\nThe quick brown fox jumps over the lazy dog.\n1234567890 !@#$%^&*()\n\nplayer_pos: <347.500, 12.000>\nplayer_vec: <0.3544, 1.000>\ndoFallDamage = true\n\n(scenevar) $target_entity = @btn_a <17.2501, 34.5000>";
    window->surface.DrawText(font, displayString, 8, 8, fontSize, fgColour);
    // window->surface.DrawText(font, displayString, 8, 8, fontSize+1);
    // window->surface.DrawText(font, displayString, 8, 8, fontSize+2);
    // window->surface.DrawText(font, displayString, 8, 8, fontSize+3);
    // window->surface.DrawText(font, displayString, 8, 8, fontSize+4);

    std::string cacheListString = "|";

    for(const auto &item : font->fontCacheList) {
        cacheListString += std::to_string(item.size) + "|";
    }

    window->surface.DrawText(
        "Current Size: " + std::to_string(fontSize) + "\nCached Sizes: " + cacheListString,
        8, 624,
        16, fgColour
    );
}

void Demo_Fonts::OnUpdate() {
    if(input->IsKeyPressed(KEY_UP)) {
        fontSize += 2;
    }else if(input->IsKeyPressed(KEY_DOWN)) {
        fontSize -= 2;
    }

    if(input->IsKeyPressed(KEY_C)) {
        font->ClearCache();
    }

    // Fonts
    if(input->IsKeyPressed(KEY_ONE)) {
        font = GalaEngine::DefaultFont;
    }else if(input->IsKeyPressed(KEY_TWO)) {
        font = assets->GetFont("Pointfree");
    }else if(input->IsKeyPressed(KEY_THREE)) {
        font = assets->GetFont("DroidSans");
    }else if(input->IsKeyPressed(KEY_FOUR)) {
        font = assets->GetFont("Inter");
    }

    // Colours
    if(input->IsKeyPressed(KEY_Q)) {
        bgColour = C_BLACK;
        fgColour = C_WHITE;
    }if(input->IsKeyPressed(KEY_W)) {
        bgColour = C_WHITE;
        fgColour = C_BLACK;
    }if(input->IsKeyPressed(KEY_E)) {
        bgColour = {0x11, 0x11, 0x11, 0xff};
        fgColour = {0xee, 0xee, 0xee, 0xff};
    }

    fontSize += input->GetMouseWheelDelta().y * (input->IsKeyDown(KEY_LEFT_SHIFT) ? 4 : 1);
}

void Demo_Fonts::OnUnload() {
    scene->assets->UnloadAll();
}

Demo_Fonts::Demo_Fonts() : Game(
    GalaEngine::GameInfo {
        "GalaEngine Fonts Demo (GalaEngine v" GALAENGINE_VERSION_STRING ")",
        "GalaEngine example project.",
        "Colleen (colleen05)",
        1280,
        720,
        GalaEngine::AssetPathLayout {
            "./resources/",
            "textures/",
            "sprites/",
            "tilesets/",
            "Fonts/",
            "sounds/",
            "fonts/"
        }
    }
) {}