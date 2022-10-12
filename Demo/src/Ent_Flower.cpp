#include <Ent_Flower.hpp>

void Ent_Flower::OnStart() {
    sprite = assets->GetSprite("flower");
    bboxSize = {64.0f, 64.0f};
}

void Ent_Flower::OnUpdate() {
    if(CheckCollisionPointRec(worldMousePosition, bbox)) {
        if(input->IsPressed("flower_click")) {
            spriteFrame = (spriteFrame + 1) % 4;
            PlaySound(assets->GetSound("sfx/chime"));
        }
    
        if(input->IsDown("flower_drag")) position = {worldMousePosition.x - 32.0f, worldMousePosition.y - 32.0f};
    }
}

Ent_Flower::Ent_Flower(int x, int y) : Entity(x, y) {}