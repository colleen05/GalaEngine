#include <Ent_Ball.hpp>

void Ent_Ball::OnStart() {
    sprite = assets->GetSprite("balls");
    bboxSize = {64.0f, 64.0f};

    float speed = 480.0f + GetRandomValue(-64, 128);
    float angle = GetRandomValue(0, 360);

    velocity = Vector2 {
        cos(angle * DEG2RAD) * speed,
        sin(angle * DEG2RAD) * speed
    };
}

void Ent_Ball::OnUpdate() {
    position.x += velocity.x * GetFrameTime();
    position.y += velocity.y * GetFrameTime();

    if((position.x < 0.0f) || (position.x > (sceneWidth - 64.0f))) velocity.x *= -1.0f;
    if((position.y < 0.0f) || (position.y > (sceneHeight - 64.0f))) velocity.y *= -1.0f;
}

void Ent_Ball::OnDraw() {
    
}

Ent_Ball::Ent_Ball(int x, int y) : Entity(x, y) {}