#include <GalaEngine/InputManager.hpp>

// State-getting
bool GalaEngine::InputManager::IsPressed(Input input, int device) {
    for(auto &k : input.keys) {
        if(IsKeyPressed(k)) return true;
    }

    for(auto &b : input.mouseButtons) {
        if(IsMouseButtonPressed(b)) return true;
    }

    if(IsGamepadAvailable(device)) {
        for(auto &b : input.gamepadButtons) {
            if(IsGamepadButtonPressed(device, b)) return true;
        }
    }
    
    return false;
}

bool GalaEngine::InputManager::IsDown(Input input, int device) {
    for(auto &k : input.keys) {
        if(IsKeyDown(k)) return true;
    }

    for(auto &b : input.mouseButtons) {
        if(IsMouseButtonDown(b)) return true;
    }

    if(IsGamepadAvailable(device)) {
        for(auto &b : input.gamepadButtons) {
            if(IsGamepadButtonDown(device, b)) return true;
        }
    }
    
    return false;
}

bool GalaEngine::InputManager::IsReleased(Input input, int device) {
    for(auto &k : input.keys) {
        if(IsKeyReleased(k)) return true;
    }

    for(auto &b : input.mouseButtons) {
        if(IsMouseButtonReleased(b)) return true;
    }

    if(IsGamepadAvailable(device)) {
        for(auto &b : input.gamepadButtons) {
            if(IsGamepadButtonReleased(device, b)) return true;
        }
    }
    
    return false;
}

bool GalaEngine::InputManager::IsPressed(std::string inputName, int device) {
    if(binds.find(inputName) != binds.end()) {
        return IsPressed(binds[inputName], device);
    }
    
    return false;
}

bool GalaEngine::InputManager::IsDown(std::string inputName, int device) {
    if(binds.find(inputName) != binds.end()) {
        return IsDown(binds[inputName], device);
    }
    
    return false;
}

bool GalaEngine::InputManager::IsReleased(std::string inputName, int device) {
    if(binds.find(inputName) != binds.end()) {
        return IsReleased(binds[inputName], device);
    }
    
    return false;
}

// Joysticks
float GalaEngine::InputManager::GetFloat(Input input, int device) {
    if(!input.hasAxis) return 0.0f;
    if(!IsGamepadAvailable(device)) return 0.0f;

    return GetGamepadAxisMovement(device, input.gamepadAxis);
}

float GalaEngine::InputManager::GetFloat(std::string inputName, int device) {
    if(binds.find(inputName) != binds.end()) {
        return GetFloat(binds[inputName], device);
    }
    
    return 0.0f;
}

Vector2 GalaEngine::InputManager::GetLeftJoystick(int device) {
    if(!IsGamepadAvailable(device)) return {0.0f, 0.0f};

    return Vector2 {
        GetGamepadAxisMovement(device, GAMEPAD_AXIS_LEFT_X),
        GetGamepadAxisMovement(device, GAMEPAD_AXIS_LEFT_Y)
    };
}

Vector2 GalaEngine::InputManager::GetRightJoystick(int device) {
    if(!IsGamepadAvailable(device)) return {0.0f, 0.0f};

    return Vector2 {
        GetGamepadAxisMovement(device, GAMEPAD_AXIS_RIGHT_X),
        GetGamepadAxisMovement(device, GAMEPAD_AXIS_RIGHT_Y)
    };
}

// Binding
void GalaEngine::InputManager::BindInput(std::string inputName, Input input) {
    if(binds.find(inputName) != binds.end()) {
        binds[inputName] = input;
    }
}

void GalaEngine::InputManager::BindKeyboard(std::string inputName, std::vector<KeyboardKey> keys, bool overwrite) {
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

void GalaEngine::InputManager::BindMouse(std::string inputName, std::vector<MouseButton> buttons, bool overwrite) {
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

void GalaEngine::InputManager::BindGamepadButtons(std::string inputName, std::vector<GamepadButton> buttons, bool overwrite) {
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

void GalaEngine::InputManager::BindGamepadAxis(std::string inputName, GamepadAxis axis) {
    if(binds.find(inputName) != binds.end()) {
        binds[inputName].hasAxis = true;
        binds[inputName].gamepadAxis = axis;
    }else {
        binds.insert_or_assign(inputName, GalaEngine::Input {
            {}, {}, {}, true, axis
        });
    }
}

void GalaEngine::InputManager::ClearBinds(std::string inputName) {
    if(binds.find(inputName) != binds.end()) binds.clear();
}

// Misc.
Vector2 GalaEngine::InputManager::GetMouseDelta() {
    return ::GetMouseDelta();
}

Vector2 GalaEngine::InputManager::GetMousePosition() {
    return ::GetMousePosition();
}

// Constructors
GalaEngine::InputManager::InputManager(std::map<std::string, Input> binds) {
    this->binds = binds;
}

GalaEngine::InputManager::InputManager() : InputManager(
    std::map<std::string, Input>()
) {}