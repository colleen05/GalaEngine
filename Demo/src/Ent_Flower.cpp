#include <Ent_Flower.hpp>

void Ent_Flower::OnStart() {
    bboxSize = {64.0f, 64.0f};
}

void Ent_Flower::OnUpdate() {
    if(CheckCollisionPointRec(worldMousePosition, bbox)) {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            spriteFrame = (spriteFrame + 1) % 4;
            PlaySound(assets->GetSound("sfx/chime"));
        }
    
        if(IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) position = {worldMousePosition.x - 32.0f, worldMousePosition.y - 32.0f};
    }
}

Ent_Flower::Ent_Flower(int x, int y) : Entity(x, y) {}