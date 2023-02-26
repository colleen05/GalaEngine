// Project: GalaEngine
// File: Math.hpp
// Description: Various utility maths functions.
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#include <raylib.h>
#include <math.h>

/*! @brief Maths functions
 *  @details Contains a variety of useful maths utility functions.
 */
namespace Math {
    /*! @brief Calculate a letteboxed rectangle's bounds.
     *  @details Get a rectangle which retains a given dimension's
     *  aspect-ratio, contained within the bounds of a container. Similar to
     *  CSS's `object-fit: contain;` property.
     *  @param contentSize The size of the content to fit.
     *  @param container The bounds in which to contain the content.
     *  @returns The fit rectangle.
     */
    Rectangle GetLetterboxedRectangle(const Vector2 contentSize, const Rectangle container);

    /*! @brief Calculate an integer-scaled rectangle's bounds.
     *  @details Get a rectangle which returns the content's bounds, centred
     *  within the container, scaled up to the largest-fitting integer factor.
     *  @param contentSize The size of the content to fit.
     *  @param container The bounds in which to contain the content.
     *  @returns The fit rectangle.
     */
    Rectangle GetIntegerScaledRectangle(const Vector2 contentSize, const Rectangle container);
}