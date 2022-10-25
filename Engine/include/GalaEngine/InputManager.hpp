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
#include <algorithm>

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

            // State-getting
            static bool IsPressed   (Input input, int device = 0);
            static bool IsDown      (Input input, int device = 0);
            static bool IsReleased  (Input input, int device = 0);

            bool        IsPressed   (std::string inputName, int device = 0);
            bool        IsDown      (std::string inputName, int device = 0);
            bool        IsReleased  (std::string inputName, int device = 0);

            // Joysticks
            static float GetFloat   (Input input, int device = 0);
            float        GetFloat   (std::string inputName, int device = 0);

            static Vector2 GetLeftJoystick  (int device = 0);
            static Vector2 GetRightJoystick (int device = 0);

            // Binding
            void BindInput          (std::string inputName, Input input);
            void BindKeyboard       (std::string inputName, std::vector<KeyboardKey> keys, bool overwrite = true);
            void BindMouse          (std::string inputName, std::vector<MouseButton> buttons, bool overwrite = true);
            void BindGamepadButtons (std::string inputName, std::vector<GamepadButton> buttons, bool overwrite = true);
            void BindGamepadAxis    (std::string inputName, GamepadAxis axis);

            void ClearBinds (std::string inputName);

            // Mouse
            Vector2 GetMouseDelta();
            Vector2 GetMousePosition();

            // Constructors
            InputManager(std::map<std::string, Input> binds);
            InputManager();
    };
}