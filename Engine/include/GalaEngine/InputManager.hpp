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
    /*! @brief Inputs for binding
     *  @details Various values detailing which inputs should be checked for a
     *  binding.
     */
    struct Input {
        std::vector<KeyboardKey> keys;              //!< Keyboard keys
        std::vector<MouseButton> mouseButtons;      //!< Mouse buttons
        std::vector<GamepadButton> gamepadButtons;  //!< Gamepad (controller) buttons, such as ABXY, L1, R1, START, etc..
        
        bool hasAxis = false;                           //!< Flag to read axis data
        GamepadAxis gamepadAxis = GAMEPAD_AXIS_LEFT_X;  //!< Gamepad (controller) analogue sticks
    };

    /*! @brief Input binding and state-getting
     *  @details Provides an interface for binding inputs to names, and
     *  checking their states.
     */
    class InputManager {
        public:
            std::map<std::string, Input> binds; //!< Map of names to inputs

            /*! @name Direct Input Checking
             *  @details Get input states directly from Input struct.
             *  @param input The input struct.
             *  @param device The device to check.
             */
            /// @{
            static bool IsPressed(const Input &input, const int device = 0);    //!< If an input has just be activated.
            static bool IsDown(const Input &input, const int device = 0);       //!< If an input is currently activated.
            static bool IsReleased(const Input &input, const int device = 0);   //!< If an input has just be de-activated.
            static Vector2 GetMouseDelta();     //!< Get mouse movement delta.
            static Vector2 GetMousePosition();  //!< Get mouse position within window.
            /// @}

            /*! @name Named Input Checking
             *  @details Get input states from bound names.
             *  @param inputName The input name.
             *  @param device The device to check.
             */
            /// @{
            bool IsPressed(const std::string &inputName, const int device = 0);     //!< If an input has just be activated.
            bool IsDown(const std::string &inputName, const int device = 0);        //!< If an input is currently activated.
            bool IsReleased(const std::string &inputName, const int device = 0);    //!< If an input has just be de-activated.
            /// @}

            /*! @name Floating-point Inputs
             *  @details Get floating-point states of inputs (such as
             *  joysticks). Will return a floating-point number between -1.0f
             *  and 1.0f of an input. Useful for joystick axes, but will also
             *  return boolean inputs as 0.0f or 1.0f.
             *  @param input The input struct.
             *  @param inputName The input name.
             *  @param device The device to check.
             */
            /// @{
            static float GetFloat(const Input &input, const int device = 0);    //!< Get float of input by struct.
            float GetFloat(const std::string &inputName, const int device = 0); //!< Get float of input by name.
            /// @}

            /*! @name Direct Joystick Checking
             *  @details Get joystick states directly from device ID.
             *  @param device The device to check.
             */
            /// @{
            static Vector2 GetLeftJoystick(const int device = 0);   //!< Get left joystick position.
            static Vector2 GetRightJoystick(const int device = 0);  //!< Get right joystick position.
            /// @}

            /*! @name Binding Inputs
             *  @details Bind inputs to names.
             *  @param device The device to check.
             */
            /// @{
            /*! @brief Bind an input to a name, by struct.
             *  @param inputName The input name.
             *  @param input The input struct.
             */
            void BindInput(const std::string &inputName, const Input &input);
            /*! @brief Bind keyboard keys to input, by name.
             *  @details Creates, appends, or overwrites keys in a named input
             *  binding.
             *  @param inputName The input name.
             *  @param keys Each keyboard key.
             *  @param overwrite Whether or not to overwrite the keys in the binding.
             */
            void BindKeyboard(const std::string &inputName, const std::vector<KeyboardKey> &keys, const bool overwrite = true);
            /*! @brief Bind mouse buttons to input, by name.
             *  @details Creates, appends, or overwrites mouse buttons in a named
             *  input binding.
             *  @param inputName The input name.
             *  @param buttons Each mouse button.
             *  @param overwrite Whether or not to overwrite the mouse buttons in the binding.
             */
            void BindMouse(const std::string &inputName, const std::vector<MouseButton> &buttons, const bool overwrite = true);
            /*! @brief Bind gamepad (controller) buttons to input, by name.
             *  @details Creates, appends, or overwrites gamepad (controller)
             *  buttons in a named input binding.
             *  @param inputName The input name.
             *  @param buttons Each gamepad button.
             *  @param overwrite Whether or not to overwrite the keys in the binding.
             */
            void BindGamepadButtons(const std::string &inputName, const std::vector<GamepadButton> &buttons, const bool overwrite = true);
            /*! @brief Bind gamepad (controller) axis to input, by name.
             *  @details Sets the gamepad (controller) axis of an input
             *  binding, such as a joystick's axis or trigger.
             *  @param inputName The input name.
             *  @param axis The gamepad (controller) axis.
             */
            void BindGamepadAxis(const std::string &inputName, const GamepadAxis axis);
            /*! @brief Clear bindings of an input.
             *  @param inputName The input name.
             */
            void ClearBinds(const std::string &inputName);
            /// @}

            /*! @brief Constructor
             *  @details Construct InputManager with pre-defined input
             *  bindings.
             *  @param binds Map of names to Input structs.
             */
            InputManager(std::map<std::string, Input> binds);
            InputManager();
    };
}