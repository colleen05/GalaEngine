#include <GalaEngine/InputManager.hpp>

// Binding
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

// Constructors
GalaEngine::InputManager::InputManager(std::map<std::string, Input> binds) {
    this->binds = binds;
}

GalaEngine::InputManager::InputManager() : InputManager(
    std::map<std::string, Input>()
) {}