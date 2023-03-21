#include <GalaEngine/Surface.hpp>

// Point
void GalaEngine::Surface::DrawPixel(int x, int y, Colour colour) {
    BeginTextureMode(renderTexture);
    ::DrawPixel(x, y, colour);
    EndTextureMode();
}

void GalaEngine::Surface::DrawLine(int x1, int y1, int x2, int y2, Colour colour) {
    BeginTextureMode(renderTexture);
    ::DrawLine(x1, y1, x2, y2, colour);
    EndTextureMode();
}

void GalaEngine::Surface::DrawLine(int x1, int y1, int x2, int y2, float thickness, Colour colour) {
    BeginTextureMode(renderTexture);
    ::DrawLineEx(
        {(float)x1, (float)y1},
        {(float)x2, (float)y2},
        thickness, colour
    );
    EndTextureMode();
}

// Primitives
void GalaEngine::Surface::DrawRectangle(int x, int y, int width, int height, Colour colour, bool outline, float thickness) {    
    BeginTextureMode(renderTexture);

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
    BeginTextureMode(renderTexture);
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
    BeginTextureMode(renderTexture);
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
    
    BeginTextureMode(renderTexture);

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
    BeginTextureMode(renderTexture);

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
    BeginTextureMode(renderTexture);
    ::DrawCircleGradient(x, y, radius, innerColour, outerColour);
    EndTextureMode();
}

void GalaEngine::Surface::DrawEllipse(int x, int y, float radiusH, float radiusV, Colour colour, bool outline, float thickness) {
    if(outline && thickness == 0.0f) return;
    
    BeginTextureMode(renderTexture);
    
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
    BeginTextureMode(renderTexture);
    
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
    BeginTextureMode(renderTexture);
    ::DrawTextEx(font, text.c_str(), Vector2 {(float)x, (float)y}, size, 2.0f, colour);
    EndTextureMode();
}

void GalaEngine::Surface::DrawText(std::string text, int x, int y, int size, Colour colour) {
    BeginTextureMode(renderTexture);
    ::DrawText(text.c_str(), x, y, size, colour);
    EndTextureMode();
}

// Textures
void GalaEngine::Surface::DrawTexture(Texture texture, int x, int y, float scaleX, float scaleY, float rotation, Vector2 origin, Colour blendColour) {
    BeginTextureMode(this->renderTexture);
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
    BeginTextureMode(this->renderTexture);
    DrawTexture(texture, x, y, scaleX, scaleY, rotation, {0.0f, 0.0f}, blendColour);
    EndTextureMode();
}

void GalaEngine::Surface::DrawTexture(Texture texture, Rectangle src, Rectangle dest, Colour blendColour) {
    BeginTextureMode(this->renderTexture);
    ::DrawTexturePro(
        texture,
        src,
        dest,
        Vector2 {0.0f, 0.0f},
        0.0f,
        blendColour
    );
    EndTextureMode();
}

void GalaEngine::Surface::DrawTextureTiled(Texture texture, Rectangle src, Rectangle dest, Vector2 origin, float scale, float rotation, Colour blendColour) {
    BeginTextureMode(this->renderTexture);
    ::DrawTextureTiled(
        texture,
        src,
        dest,
        Vector2Multiply(origin, {scale, scale}),
        rotation,
        scale,
        blendColour
    );
    EndTextureMode();
}

// Sprites
void GalaEngine::Surface::DrawSprite(Sprite sprite, int frame, int x, int y, float scaleX, float scaleY, float rotation, Colour blendColour) {
    frame = frame % sprite.frameRects.size();

    BeginTextureMode(renderTexture);
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

void GalaEngine::Surface::DrawNSlice(NSlice nslice, int x, int y, int width, int height, Colour blendColour) {
    BeginTextureMode(renderTexture);
    BeginScissorMode(x, y, width, height);

    // Borders
    const int topBorder     = nslice.centreSlice.y;
    const int rightBorder   = nslice.centreSlice.x + nslice.centreSlice.width;
    const int bottomBorder  = nslice.centreSlice.y + nslice.centreSlice.height;
    const int leftBorder    = nslice.centreSlice.x;

    const Rectangle srcTopLeft      = { 0.0f, 0.0f, (float)leftBorder, (float)topBorder };
    const Rectangle srcTop          = { (float)leftBorder, 0.0f, nslice.centreSlice.width, (float)topBorder};
    const Rectangle srcTopRight     = { (float)rightBorder, 0.0f, (float)(nslice.texture.width - rightBorder), (float)topBorder };
    const Rectangle srcLeft         = { 0.0f, (float)topBorder, (float)leftBorder, nslice.centreSlice.height };
    const Rectangle srcCentre       = nslice.centreSlice;
    const Rectangle srcRight        = { (float)rightBorder, (float)topBorder, (float)(nslice.texture.width - rightBorder), nslice.centreSlice.height };
    const Rectangle srcBottomLeft   = { 0.0f, (float)bottomBorder, (float)leftBorder, (float)(nslice.texture.height - bottomBorder) };
    const Rectangle srcBottom       = { (float)leftBorder, (float)bottomBorder, nslice.centreSlice.width, (float)(nslice.texture.height - bottomBorder)};
    const Rectangle srcBottomRight  = { (float)rightBorder, (float)bottomBorder, (float)(nslice.texture.width - rightBorder), (float)(nslice.texture.height - bottomBorder) };

    // Centre
    const Rectangle destCentre = {
        (float)x + srcTopLeft.width,
        (float)y + srcTopLeft.height, 
        (float)(width - srcLeft.width - srcRight.width),
        (float)(height - srcTop.height - srcBottom.height)
    };

    if(nslice.stretchSlices[4]) {
        ::DrawTexturePro(nslice.texture, srcCentre, destCentre, Vector2 {0.0f, 0.0f}, 0.0f, blendColour);
    }else {
        ::DrawTextureTiled(nslice.texture, srcCentre, destCentre, Vector2 {0.0f, 0.0f}, 0.0f, 1.0f, blendColour);
    }

    // Top
    const Rectangle destTop = { destCentre.x, (float)y, destCentre.width, srcTop.height };

    if(nslice.stretchSlices[0]) {
        ::DrawTexturePro(nslice.texture, srcTop, destTop, Vector2 {0.0f, 0.0f}, 0.0f, blendColour);
    }else {
        ::DrawTextureTiled(nslice.texture, srcTop, destTop, Vector2 {0.0f, 0.0f}, 0.0f, 1.0f, blendColour);
    }

    // Right
    const Rectangle destRight = { destCentre.x + destCentre.width, destCentre.y, srcRight.width, destCentre.height };

    if(nslice.stretchSlices[1]) {
        ::DrawTexturePro(nslice.texture, srcRight, destRight, Vector2 {0.0f, 0.0f}, 0.0f, blendColour);
    }else {
        ::DrawTextureTiled(nslice.texture, srcRight, destRight, Vector2 {0.0f, 0.0f}, 0.0f, 1.0f, blendColour);
    }

    // Bottom
    const Rectangle destBottom = { destCentre.x, destCentre.y + destCentre.height, destCentre.width, srcBottom.height };

    if(nslice.stretchSlices[2]) {
        ::DrawTexturePro(nslice.texture, srcBottom, destBottom, Vector2 {0.0f, 0.0f}, 0.0f, blendColour);
    }else {
        ::DrawTextureTiled(nslice.texture, srcBottom, destBottom, Vector2 {0.0f, 0.0f}, 0.0f, 1.0f, blendColour);
    }

    // Left
    const Rectangle destLeft = { (float)x, destCentre.y, srcLeft.width, destCentre.height };

    if(nslice.stretchSlices[3]) {
        ::DrawTexturePro(nslice.texture, srcLeft, destLeft, Vector2 {0.0f, 0.0f}, 0.0f, blendColour);
    }else {
        ::DrawTextureTiled(nslice.texture, srcLeft, destLeft, Vector2 {0.0f, 0.0f}, 0.0f, 1.0f, blendColour);
    }

    // Top-left
    ::DrawTextureRec(
        nslice.texture, srcTopLeft,
        Vector2 { (float)x, (float)y }, blendColour
    );

    // Top-right
    ::DrawTextureRec(
        nslice.texture, srcTopRight,
        Vector2 { (float)(x+width)-srcTopRight.width, (float)y }, blendColour
    );

    // Bottom-left
    ::DrawTextureRec(
        nslice.texture, srcBottomLeft,
        Vector2 { (float)x, (float)(y+height)-srcBottomLeft.height }, blendColour
    );

    // Bottom-right
    ::DrawTextureRec(
        nslice.texture, srcBottomRight,
        Vector2 { (float)(x+width)-srcBottomRight.width, (float)(y+height)-srcBottomRight.height }, blendColour
    );

    EndScissorMode();
    EndTextureMode();
}

void GalaEngine::Surface::Resize(int width, int height) {
    UnloadRenderTexture(renderTexture);
    renderTexture = LoadRenderTexture(width, height);
}

void GalaEngine::Surface::Clear(Colour colour) {
    BeginTextureMode(renderTexture);
    ClearBackground(colour);
    EndTextureMode();
}

void GalaEngine::Surface::Clear() {
    Clear(clearColour);
}

Image GalaEngine::Surface::GetImage() {
    Image img = LoadImageFromTexture(renderTexture.texture);
    ImageFlipVertical(&img);

    return img;
}

void GalaEngine::Surface::Destroy() {
    UnloadRenderTexture(renderTexture);
    renderTexture.id = 0;
}

GalaEngine::Surface::Surface(int width, int height, Colour colour) {
    renderTexture = LoadRenderTexture(width, height);
    clearColour = colour;
}

GalaEngine::Surface::Surface() {}