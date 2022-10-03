#include <GalaEngine/Surface.hpp>

// Point
void GalaEngine::Surface::DrawPixel(int x, int y, Colour colour) {
    BeginTextureMode(texture);
    ::DrawPixel(x, y, colour);
    EndTextureMode();
}

void GalaEngine::Surface::DrawLine(int x1, int y1, int x2, int y2, Colour colour) {
    BeginTextureMode(texture);
    ::DrawLine(x1, y1, x2, y2, colour);
    EndTextureMode();
}

void GalaEngine::Surface::DrawLine(int x1, int y1, int x2, int y2, float thickness, Colour colour) {
    BeginTextureMode(texture);
    ::DrawLineEx(
        {(float)x1, (float)y1},
        {(float)x2, (float)y2},
        thickness, colour
    );
    EndTextureMode();
}

// Primitives
void GalaEngine::Surface::DrawRectangle(int x, int y, int width, int height, Colour colour, bool outline, float thickness) {    
    BeginTextureMode(texture);

    if(outline){
        if(thickness >= 0.0f) { // Draw inner outline
            ::DrawRectangleLinesEx(
                Rectangle {
                    (float) x, (float) y,
                    (float) width, (float) height
                },
                thickness,
                colour
            );
        }else { // Draw outer outline
            ::DrawRectangleLinesEx(
                Rectangle {
                    (float) x + thickness, (float) y + thickness,
                    (float) width - thickness * 2.0f, (float) height - thickness * 2.0f
                },
                -thickness,
                colour
            );
        }
    }else {
        ::DrawRectangle(x, y, width, height, colour);
    }

    EndTextureMode();
}

void GalaEngine::Surface::DrawRectangle(int x, int y, int width, int height, float rotation, Vector2 origin, Colour colour) {
    BeginTextureMode(texture);
    ::DrawRectanglePro(
        Rectangle {
            (float)x, (float)y,
            (float)width, (float)height
        },
        origin, rotation, colour
    );
    EndTextureMode();
}

void GalaEngine::Surface::DrawRectangleColours(int x, int y, int width, int height, Colour c1, Colour c2, Colour c3, Colour c4) {
    BeginTextureMode(texture);
    ::DrawRectangleGradientEx(
        Rectangle {
            (float)x, (float)y,
            (float)width, (float)height
        },
        c1, c2, c3, c4
    );
    EndTextureMode();
}

void GalaEngine::Surface::DrawRectangleRounded(int x, int y, int width, int height, float radius, Colour colour, bool outline, float thickness) {
    if(outline && thickness == 0.0f) return;
    
    BeginTextureMode(texture);

    float roundness = (2.0f * radius) / std::min(width, height);
    roundness = Clamp(roundness, 0.0f, 1.0f);

    if(outline){
        if(thickness >= 0.0f) { // Draw inner outline
            ::DrawRectangleRoundedLines(
                Rectangle {
                    (float) x + thickness, (float) y + thickness,
                    (float) width - thickness * 2.0f, (float) height - thickness * 2.0f
                },
                roundness, 16,
                thickness,
                colour
            );
        }else { // Draw outer outline
            ::DrawRectangleRoundedLines(
                Rectangle {
                    (float) x, (float) y,
                    (float) width, (float) height
                },
                roundness, 16,
                -thickness,
                colour
            );
        }
    }else {
        ::DrawRectangleRounded(
                Rectangle {
                    (float) x, (float) y,
                    (float) width, (float) height
                },
                roundness, 16,
                colour
        );
    }

    EndTextureMode();
}

void GalaEngine::Surface::DrawCircle(int x, int y, float radius, Colour colour, bool outline, float thickness) {
    BeginTextureMode(texture);

    if(outline) {
        ::DrawRing(
            {(float)x, (float)y},
            radius - thickness,
            radius,
            0.0f, 360.0f,
            128.0f,
            colour
        );
    }else {
        ::DrawCircle(x, y, radius, colour);
    }

    EndTextureMode();
}

void GalaEngine::Surface::DrawCircle(int x, int y, float radius, Colour innerColour, Colour outerColour) {
    BeginTextureMode(texture);
    ::DrawCircleGradient(x, y, radius, innerColour, outerColour);
    EndTextureMode();
}

void GalaEngine::Surface::DrawEllipse(int x, int y, float radiusH, float radiusV, Colour colour, bool outline, float thickness) {
    if(outline && thickness == 0.0f) return;
    
    BeginTextureMode(texture);
    
    if(outline) {
        if(thickness > std::min(radiusH, radiusV)) { // Draw solid ellipse
            ::DrawEllipse(x, y, radiusH, radiusV, colour);
        }else if(thickness == 1.0f) { // Draw single outline
            ::DrawEllipseLines(x, y, radiusH, radiusV, colour);
        }else {
            if(thickness > 0.0f) { // Draw inner outline
                for(int i = 0; i < thickness * 2; i++) {
                    ::DrawEllipseLines(x, y, radiusH - (float)(i) / 2.0f, radiusV - (float)(i) / 2.0f, colour);
                }
            }else { // Draw outer outline
                for(int i = 0; i < -thickness * 2; i++) {
                    ::DrawEllipseLines(x, y, radiusH + (float)(i) / 2.0f, radiusV + (float)(i) / 2.0f, colour);
                }
            }
        }
    }else {
        ::DrawEllipse(x, y, radiusH, radiusV, colour);
    }
    
    EndTextureMode();
}

void GalaEngine::Surface::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, Colour colour, bool outline) {
    BeginTextureMode(texture);
    
    if(outline){
        ::DrawTriangleLines(
            {(float) x1, (float) y1},
            {(float) x2, (float) y2},
            {(float) x3, (float) y3},
            colour
        );
    }else {
        ::DrawTriangle(
            {(float) x1, (float) y1},
            {(float) x2, (float) y2},
            {(float) x3, (float) y3},
            colour
        );
    }

    EndTextureMode();
}

// Text
void GalaEngine::Surface::DrawText(Font font, std::string text, int x, int y, int size, Colour colour) {
    BeginTextureMode(texture);
    ::DrawTextEx(font, text.c_str(), Vector2 {(float)x, (float)y}, size, 2.0f, colour);
    EndTextureMode();
}

void GalaEngine::Surface::DrawText(std::string text, int x, int y, int size, Colour colour) {
    BeginTextureMode(texture);
    ::DrawText(text.c_str(), x, y, size, colour);
    EndTextureMode();
}

// Textures
void GalaEngine::Surface::DrawTexture(Texture texture, int x, int y, float scaleX, float scaleY, float rotation, Vector2 origin, Colour blendColour) {
    BeginTextureMode(this->texture);
    ::DrawTexturePro(
        texture,
        Rectangle {
            0.0f, 0.0f,
            (float) texture.width,
            (float) texture.height
        },
        Rectangle {
            (float)x,
            (float)y,
            texture.width * scaleX,
            texture.height * scaleY
        },
        Vector2Multiply(origin, {scaleX, scaleY}),
        rotation,
        blendColour
    );
    EndTextureMode();
}

void GalaEngine::Surface::DrawTexture(Texture texture, int x, int y, float scaleX, float scaleY, float rotation, Colour blendColour) {
    BeginTextureMode(this->texture);
    DrawTexture(texture, x, y, scaleX, scaleY, rotation, {0.0f, 0.0f}, blendColour);
    EndTextureMode();
}

void GalaEngine::Surface::DrawTexture(Texture texture, Rectangle src, Rectangle dest, Colour blendColour) {
    BeginTextureMode(this->texture);
    ::DrawTexturePro(
        texture,
        src,
        dest,
        {0.0f, 0.0f},
        0.0f,
        blendColour
    );
    EndTextureMode();
}

// Sprites
void GalaEngine::Surface::DrawSprite(Sprite sprite, int frame, int x, int y, float scaleX, float scaleY, float rotation, Colour blendColour) {
    BeginTextureMode(texture);
    ::DrawTexturePro(
        sprite.texture,
        sprite.frameRects[frame],
        Rectangle {
            (float)x,
            (float)y,
            sprite.frameRects[frame].width * scaleX,
            sprite.frameRects[frame].height * scaleY
        },
        Vector2Multiply(sprite.origin, {scaleX, scaleY}),
        rotation,
        blendColour
    );
    EndTextureMode();
}

void GalaEngine::Surface::Clear(Colour colour) {
    BeginTextureMode(texture);
    ClearBackground(colour);
    EndTextureMode();
}

void GalaEngine::Surface::Clear() {
    BeginTextureMode(texture);
    ClearBackground(clearColour);
    EndTextureMode();
}

Image GalaEngine::Surface::GetImage() {
    Image img = LoadImageFromTexture(texture.texture);
    ImageFlipVertical(&img);

    return img;
}

void GalaEngine::Surface::Destroy() {
    UnloadRenderTexture(texture);
    texture.id = 0;
}

GalaEngine::Surface::Surface(int width, int height, Colour colour) {
    texture = LoadRenderTexture(width, height);
    clearColour = colour;
}

GalaEngine::Surface::Surface() {}