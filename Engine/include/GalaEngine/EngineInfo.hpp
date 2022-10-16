// Project: GalaEngine
// File: EngineInfo.hpp
// Description: Engine information definitions and function.
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#define GALAENGINE_VERSION_MAJOR 0
#define GALAENGINE_VERSION_MINOR 2
#define GALANEGINE_VERSION_PATCH 0

// r = release, a = alpha, b = beta, d = in-development
#define GALAENGINE_VERSION_RELEASE 'd'

#define GALAENGINE_VERSION_STRING "0.2.0-d"

namespace GalaEngine {
    const char* GetEngineInfo();
}
