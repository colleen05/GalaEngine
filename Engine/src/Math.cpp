#include <GalaEngine/Math.hpp>

Rectangle Math::GetLetterboxedRectangle(const Vector2 contentSize, const Rectangle container) {
    // Calculate aspect ratios.
    const float innerAspect     = contentSize.x   / contentSize.y;
    const float containerAspect = container.width / container.height;
    
    // Calculate "box" (the new rectangle)'s dimensions.
    const float boxWidth =
        (containerAspect  > innerAspect) ?  // Container proportionally wider than inner?
        (container.height * innerAspect) :  // Only take up a portion of the width.
        (container.width);                  // Otherwise, take up the entire width.
    
    const float boxHeight =
        (containerAspect < innerAspect) ?   // Container proportionally taller than inner?
        (container.width / innerAspect) :   // Only take up a portion of the height.
        (container.height);                 // Otherwise, take up the entire height.

    // Create the new rectangle, positioned properly inside the container.
    const Rectangle box = {
        container.x + (container.width  - boxWidth)  / 2.0f,    // Centred horizontally.
        container.y + (container.height - boxHeight) / 2.0f,    // Centred vertically.
        boxWidth, boxHeight     // (We already know the box dimensions!)
    };
    
    // Return the new rectangle.
    return box;
}

Rectangle Math::GetIntegerScaledRectangle(const Vector2 contentSize, const Rectangle container) {
    // Determine largest contained scale factor.
    const float scaleFactor = floor(fmin(
        (container.width  / contentSize.x),
        (container.height / contentSize.y)
    ));

    // Get the scaled content dimensions.
    const float boxWidth  = contentSize.x * scaleFactor;
    const float boxHeight = contentSize.y * scaleFactor;

    // Construct the new rectangle.
    const Rectangle box = {
        (container.width  - boxWidth)  / 2.0f,
        (container.height - boxHeight) / 2.0f,
        boxWidth, boxHeight
    };

    // Return the new rectangle.
    return box;
}