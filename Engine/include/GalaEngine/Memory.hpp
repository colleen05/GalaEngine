// Project: GalaEngine
// File: Memory.hpp
// Description: Provides aliases and functions for memory management.
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <memory>

/*! @brief A smart pointer (shared).
 *  @details An alias around std::shared_ptr<T>.
 */
template <class T>
using Shared = std::shared_ptr<T>;

/*! @brief Creates a smart pointer.
 *  @details Constructs and returns a Shared<T>.
 *  @param args Arguments to construct the T object.
 */
template<typename T, typename... Args>
inline Shared<T> Make(Args&&... args) {
    return std::make_shared<T>(args...);
}