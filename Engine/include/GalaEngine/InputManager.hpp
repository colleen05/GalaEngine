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
            static bool IsPressed   (const Input &input, const int device = 0);
            static bool IsDown      (const Input &input, const int device = 0);
            static bool IsReleased  (const Input &input, const int device = 0);

            bool        IsPressed   (const std::string &inputName, const int device = 0);
            bool        IsDown      (const std::string &inputName, const int device = 0);
            bool        IsReleased  (const std::string &inputName, const int device = 0);

            // Joysticks
            static float GetFloat   (const Input &input, const int device = 0);
            float        GetFloat   (const std::string &inputName, const int device = 0);

            static Vector2 GetLeftJoystick  (const int device = 0);
            static Vector2 GetRightJoystick (const int device = 0);

            // Binding
            void BindInput          (const std::string &inputName, const Input &input);
            void BindKeyboard       (const std::string &inputName, const std::vector<KeyboardKey> &keys, const bool overwrite = true);
            void BindMouse          (const std::string &inputName, const std::vector<MouseButton> &buttons, const bool overwrite = true);
            void BindGamepadButtons (const std::string &inputName, const std::vector<GamepadButton> &buttons, const bool overwrite = true);
            void BindGamepadAxis    (const std::string &inputName, const GamepadAxis axis);

            void ClearBinds (const std::string &inputName);

            // Mouse
            Vector2 GetMouseDelta();
            Vector2 GetMousePosition();

            // Constructors
            InputManager(std::map<std::string, Input> binds);
            InputManager();
    };
}