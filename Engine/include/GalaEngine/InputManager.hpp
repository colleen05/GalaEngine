// Project: GalaEngine
// File: InputManager.hpp
// Description: Input managing class
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <raylib.h>

#include <string>
#include <vector>
#include <map>

namespace GalaEngine {
    struct Input {
        std::vector<KeyboardKey>    keys;           // Keyboard keys
        std::vector<MouseButton>    mouseButtons;   // Mouse buttons
        std::vector<GamepadButton>  gamepadButtons; // Gamepad (controller) buttons, such as ABXY, L1, R1, START, etc..
        
        bool        hasAxis     = false;                // Flag to read axis data
        GamepadAxis gamepadAxis = GAMEPAD_AXIS_LEFT_X;  // Gamepad (controller) analogue sticks
    };

    class InputManager {
        public:
            // Variables
            std::map<std::string, Input> binds;

            // Binds
            static bool IsPressed   (Input input);
            static bool IsDown      (Input input);
            static bool IsReleased  (Input input);

            bool        IsPressed   (std::string inputName);
            bool        IsDown      (std::string inputName);
            bool        IsReleased  (std::string inputName);

            static float GetFloat   (Input input);
            float        GetFloat   (std::string inputName);

            // Joystick
            static Vector2 GetLeftJoystick  (int controller = 0);
            static Vector2 GetRightJoystick (int controller = 0);

            // Constructors
            InputManager(std::map<std::string, Input> binds);
            InputManager();
    };
}