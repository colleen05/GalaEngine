#include <GalaEngine/InputManager.hpp>

// Gamepad availability
bool GalaEngine::InputManager::IsGamepadAvailable(const int device) { return ::IsGamepadAvailable(device); }

// State-getting
bool GalaEngine::InputManager::IsKeyPressed          (const KeyboardKey key)    { return ::IsKeyPressed(key);              }
bool GalaEngine::InputManager::IsKeyDown             (const KeyboardKey key)    { return ::IsKeyDown(key);                 }
bool GalaEngine::InputManager::IsKeyReleased         (const KeyboardKey key)    { return ::IsKeyReleased(key);             }
bool GalaEngine::InputManager::IsMouseButtonPressed  (const MouseButton button) { return ::IsMouseButtonPressed(button);   }
bool GalaEngine::InputManager::IsMouseButtonDown     (const MouseButton button) { return ::IsMouseButtonDown(button);      }
bool GalaEngine::InputManager::IsMouseButtonReleased (const MouseButton button) { return ::IsMouseButtonReleased(button);  }

bool GalaEngine::InputManager::IsGamepadButtonPressed(const GamepadButton button, const int device) {
    return ::IsGamepadButtonPressed(device, button);
}

bool GalaEngine::InputManager::IsGamepadButtonDown(const GamepadButton button, const int device) {
    return ::IsGamepadButtonDown(device, button);
}

bool GalaEngine::InputManager::IsGamepadButtonReleased(const GamepadButton button, const int device) {
    return ::IsGamepadButtonReleased(device, button);
}

bool GalaEngine::InputManager::IsPressed(const Input &input, const int device) {
    for(auto &k : input.keys) {
        if(IsKeyPressed(k)) return true;
    }

    for(auto &b : input.mouseButtons) {
        if(IsMouseButtonPressed(b)) return true;
    }

    if(IsGamepadAvailable(device)) {
        for(auto &b : input.gamepadButtons) {
            if(IsGamepadButtonPressed(b, device)) return true;
        }
    }
    
    return false;
}

bool GalaEngine::InputManager::IsDown(const Input &input, const int device) {
    for(auto &k : input.keys) {
        if(IsKeyDown(k)) return true;
    }

    for(auto &b : input.mouseButtons) {
        if(IsMouseButtonDown(b)) return true;
    }

    if(IsGamepadAvailable(device)) {
        for(auto &b : input.gamepadButtons) {
            if(IsGamepadButtonDown(b, device)) return true;
        }
    }
    
    return false;
}

bool GalaEngine::InputManager::IsReleased(const Input &input, const int device) {
    for(auto &k : input.keys) {
        if(IsKeyReleased(k)) return true;
    }

    for(auto &b : input.mouseButtons) {
        if(IsMouseButtonReleased(b)) return true;
    }

    if(IsGamepadAvailable(device)) {
        for(auto &b : input.gamepadButtons) {
            if(IsGamepadButtonReleased(b, device)) return true;
        }
    }
    
    return false;
}

float GalaEngine::InputManager::GetGamepadAxisMovement(const GamepadAxis axis, const int device) {
    const float movement = ::GetGamepadAxisMovement(device, axis);

    switch(axis) {
        case GAMEPAD_AXIS_LEFT_TRIGGER:
        case GAMEPAD_AXIS_RIGHT_TRIGGER:
            return (movement + 1.0f) / 2.0f;
        case GAMEPAD_AXIS_LEFT_Y:
        case GAMEPAD_AXIS_RIGHT_Y:
            return (movement == 0.0f) ? 0.0f : -movement;
        default: break;
    }

    return movement;
}

Vector2 GalaEngine::InputManager::GetMouseDelta     () { return ::GetMouseDelta();      }
Vector2 GalaEngine::InputManager::GetMouseWheelDelta() { return ::GetMouseWheelMoveV(); }
Vector2 GalaEngine::InputManager::GetMousePosition  () { return ::GetMousePosition();   }

// Named input checking
bool GalaEngine::InputManager::IsPressed(const std::string &inputName, const int device) {
    if(binds.find(inputName) != binds.end()) {
        return IsPressed(binds[inputName], device);
    }
    
    return false;
}

bool GalaEngine::InputManager::IsDown(const std::string &inputName, const int device) {
    if(binds.find(inputName) != binds.end()) {
        return IsDown(binds[inputName], device);
    }
    
    return false;
}

bool GalaEngine::InputManager::IsReleased(const std::string &inputName, const int device) {
    if(binds.find(inputName) != binds.end()) {
        return IsReleased(binds[inputName], device);
    }
    
    return false;
}

// Joysticks
float GalaEngine::InputManager::GetFloat(const Input &input, const int device) {
    // Handling boolean inputs
    if(IsDown(input, device)) return 1.0f;
    
    // Gamepad inputs
    if((!input.hasAxis) || (!IsGamepadAvailable(device))) return 0.0f;

    return GetGamepadAxisMovement(input.gamepadAxis, device);
}

float GalaEngine::InputManager::GetFloat(const std::string &inputName, const int device) {
    if(binds.find(inputName) != binds.end()) {
        return GetFloat(binds[inputName], device);
    }
    
    return 0.0f;
}

Vector2 GalaEngine::InputManager::GetLeftJoystick(const int device) {
    if(!IsGamepadAvailable(device)) return {0.0f, 0.0f};

    return Vector2 {
        GetGamepadAxisMovement(GAMEPAD_AXIS_LEFT_X, device),
        GetGamepadAxisMovement(GAMEPAD_AXIS_LEFT_Y, device)
    };
}

Vector2 GalaEngine::InputManager::GetRightJoystick(const int device) {
    if(!IsGamepadAvailable(device)) return {0.0f, 0.0f};

    return Vector2 {
        GetGamepadAxisMovement(GAMEPAD_AXIS_RIGHT_X, device),
        GetGamepadAxisMovement(GAMEPAD_AXIS_RIGHT_Y, device)
    };
}

// Binding
void GalaEngine::InputManager::BindInput(const std::string &inputName, const Input &input) {
    binds.insert_or_assign(inputName, input);
}

void GalaEngine::InputManager::BindKeyboard(const std::string &inputName, const std::vector<KeyboardKey> &keys, const bool overwrite) {
    if(binds.find(inputName) != binds.end()) {
        auto &bindKeys = binds[inputName].keys;

        if(overwrite) {
            // Overwrite input vector
            bindKeys = keys;
        }else {
            // Only add unique elements
            for(auto &k : keys) {
                // If input key/button not found...
                if(std::find(bindKeys.begin(), bindKeys.end(), k) == bindKeys.end()) {
                    // Push it into the vector.
                    bindKeys.push_back(k);
                }
            }
        }
    }else {
        binds.insert_or_assign(inputName, GalaEngine::Input {
            keys, {}, {}, false, GAMEPAD_AXIS_LEFT_X
        });
    }
}

void GalaEngine::InputManager::BindMouse(const std::string &inputName, const std::vector<MouseButton> &buttons, const bool overwrite) {
    if(binds.find(inputName) != binds.end()) {
        auto &bindButtons = binds[inputName].mouseButtons;

        if(overwrite) {
            // Overwrite input vector
            bindButtons = buttons;
        }else {
            // Only add unique elements
            for(auto &b : buttons) {
                // If input key/button not found...
                if(std::find(bindButtons.begin(), bindButtons.end(), b) == bindButtons.end()) {
                    // Push it into the vector.
                    bindButtons.push_back(b);
                }
            }
        }
    }else {
        binds.insert_or_assign(inputName, GalaEngine::Input {
            {}, buttons, {}, false, GAMEPAD_AXIS_LEFT_X
        });
    }
}

void GalaEngine::InputManager::BindGamepadButtons(const std::string &inputName, const std::vector<GamepadButton> &buttons, const bool overwrite) {
    if(binds.find(inputName) != binds.end()) {
        auto &bindButtons = binds[inputName].gamepadButtons;

        if(overwrite) {
            // Overwrite input vector
            bindButtons = buttons;
        }else {
            // Only add unique elements
            for(auto &b : buttons) {
                // If input key/button not found...
                if(std::find(bindButtons.begin(), bindButtons.end(), b) == bindButtons.end()) {
                    // Push it into the vector.
                    bindButtons.push_back(b);
                }
            }
        }
    }else {
        binds.insert_or_assign(inputName, GalaEngine::Input {
            {}, {}, buttons, false, GAMEPAD_AXIS_LEFT_X
        });
    }
}

void GalaEngine::InputManager::BindGamepadAxis(const std::string &inputName, const GamepadAxis axis) {
    if(binds.find(inputName) != binds.end()) {
        binds[inputName].hasAxis = true;
        binds[inputName].gamepadAxis = axis;
    }else {
        binds.insert_or_assign(inputName, GalaEngine::Input {
            {}, {}, {}, true, axis
        });
    }
}

void GalaEngine::InputManager::ClearBinds(const std::string &inputName) {
    if(binds.find(inputName) != binds.end()) binds.clear();
}

// Constructors
GalaEngine::InputManager::InputManager(std::map<std::string, Input> binds) {
    this->binds = binds;
}

GalaEngine::InputManager::InputManager() : InputManager(
    std::map<std::string, Input>()
) {}