#include <Demo_NSlices.hpp>

void Demo_NSlices::OnLoad() {
    
}

void Demo_NSlices::OnDraw() {
    window->surface.DrawNSlice(
        *assets->GetNSlice(currentNSlice),
        sliceWindow.x, sliceWindow.y,
        sliceWindow.width, sliceWindow.height,
        C_WHITE
    );

    if(showPreview) {
        window->surface.DrawNSlice(
            *assets->GetNSlice(currentNSlice),
            slicePreview.x, slicePreview.y,
            slicePreview.width, slicePreview.height,
            (input->IsKeyDown(KEY_LEFT_SHIFT)) ? C_WHITE : (GalaEngine::Colour){0xff, 0xff, 0xff, 0x7f}
        );
    }
}

void Demo_NSlices::OnUpdate() {
    showPreview = input->IsMouseButtonDown(MOUSE_BUTTON_LEFT);

    if(input->IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        slicePreview.x = GetMouseX();
        slicePreview.y = GetMouseY();
    }

    if(input->IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        slicePreview.width = (GetMouseX() - slicePreview.x);
        slicePreview.height = (GetMouseY() - slicePreview.y);
    }

    if(input->IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        sliceWindow = slicePreview;
    }

    if(input->IsKeyPressed(KEY_ONE)) {
        currentNSlice = "numbers";
    }else if(input->IsKeyPressed(KEY_TWO)) {
        currentNSlice = "gui_window";
    }else if(input->IsKeyPressed(KEY_THREE)) {
        currentNSlice = "carpet";
    }
}

void Demo_NSlices::OnUnload() {
    scene->assets->UnloadAll();
}

Demo_NSlices::Demo_NSlices() : Game(
    GalaEngine::GameInfo {
        "GalaEngine 9-Slice Demo (GalaEngine v" GALAENGINE_VERSION_STRING ")",
        "GalaEngine example project.",
        "Colleen (colleen05)",
        1280,
        720,
        GalaEngine::AssetPathLayout {
            "./resources/",
            "textures/",
            "sprites/",
            "tilesets/",
            "nslices/",
            "sounds/",
            "fonts/"
        }
    }
) {}