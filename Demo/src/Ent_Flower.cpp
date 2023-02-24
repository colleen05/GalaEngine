#include <Ent_Flower.hpp>

void Ent_Flower::OnStart() {
    sprite = assets->GetSprite("flower");
    bboxSize = {64.0f, 64.0f};
}

void Ent_Flower::OnUpdate() {
    if(CheckCollisionPointRec(sceneMousePosition, bbox)) {
        if(input->IsPressed("flower_click")) {
            spriteFrame = (spriteFrame + 1) % 4;
            sound->Play(assets->GetSound("sfx_chime"), true);
        }
    
        if(input->IsDown("flower_drag")) position = {sceneMousePosition.x - 32.0f, sceneMousePosition.y - 32.0f};
    }
}

void Ent_Flower::OnDraw() {
    layerSurface->DrawText(std::to_string(spriteFrame), position.x, position.y, 20, C_GALARED);
}

Ent_Flower::Ent_Flower(int x, int y) : Entity(x, y) {}