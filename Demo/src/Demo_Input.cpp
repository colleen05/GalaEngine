#include <Demo_Input.hpp>

// Game class overrides
void Demo_Input::OnLoad() {
    input->BindKeyboard("jump", {KEY_SPACE}, false);
    input->BindGamepadButtons("jump", {GAMEPAD_BUTTON_RIGHT_FACE_DOWN}, false);
    bindingDescriptions.insert(std::make_pair("jump", "Press SPACE, or A on your controller."));

    input->BindKeyboard("use", {KEY_E}, false);
    input->BindMouse("use", {MOUSE_BUTTON_RIGHT}, false);
    bindingDescriptions.insert(std::make_pair("use", "Press E, or right click."));

    input->BindKeyboard("walk_forward", {KEY_W, KEY_UP}, false);
    input->BindGamepadAxis("walk_forward", GAMEPAD_AXIS_LEFT_Y);
    bindingDescriptions.insert(std::make_pair("walk_forward", "Hold W, UP, or move your left joystick."));

    input->BindInput("shoot_primary", GalaEngine::Input {
        /* Keyboard keys   */ {},
        /* Mouse buttons   */ {MOUSE_BUTTON_LEFT},
        /* Gamepad buttons */ {GAMEPAD_BUTTON_LEFT_TRIGGER_1},
        /* Gamepad axis    */ true, GAMEPAD_AXIS_LEFT_TRIGGER
    });
    bindingDescriptions.insert(std::make_pair("shoot_primary", "Left click, or use left triggers on your controller."));
}

void Demo_Input::OnDraw() {
    window->surface.Clear({0x11, 0x11, 0x11, 0xff});

    GUI_Nav(0, 0);

    switch(currentApplet) {
        case Applet::Overview:  Applet_Overview();  break;
        case Applet::Binding:   Applet_Binding();   break;
        case Applet::Log:       Applet_Log();       break;
    }
}

void Demo_Input::OnUpdate() {
    if(currentGamepadDevice < 0)
        currentGamepadDevice = 0;
}

void Demo_Input::OnUnload() {

}

// Extra input stuff
std::vector<MouseButton> Demo_Input::GetMouseButtonsPressed() {
    std::vector<MouseButton> buttons;

    for(const auto &b : {
        MOUSE_BUTTON_LEFT,
        MOUSE_BUTTON_RIGHT,
        MOUSE_BUTTON_MIDDLE,
        MOUSE_BUTTON_SIDE,
        MOUSE_BUTTON_EXTRA,
        MOUSE_BUTTON_FORWARD,
        MOUSE_BUTTON_BACK
    }) {
        if(IsMouseButtonPressed(b))
            buttons.push_back(b);
    }

    return buttons;
}

// Applets
void Demo_Input::Applet_Overview() {
    GUI_DrawKeyboard(320, 32);
    GUI_DrawController(320, 384, currentGamepadDevice);
    GUI_DrawMouse(800, 400);
    GUI_DrawNavKeys(1072, 384);
}

void Demo_Input::Applet_Binding() {
    int boxY = 32;
    for(const auto &[name, input] : input->binds) {
        boxY += GUI_Input(name, bindingDescriptions[name], 320, boxY, currentGamepadDevice) + 8;
    }
}

void Demo_Input::Applet_Log() {
    // Capture inputs
    const int k = GetKeyPressed();
    if(k != 0) inputLog.push_back("KEY: " + std::to_string(k));

    const int b = GetGamepadButtonPressed();
    if(b != -1) inputLog.push_back("GAMEPAD: " + std::to_string(b));

    for(const auto &m : GetMouseButtonsPressed()) {
        inputLog.push_back("MOUSE: " + std::to_string(m));
    }

    // Trim log
    if(inputLog.size() > 27)
        inputLog.erase(inputLog.begin());
    
    // Draw log
    for(int i = 0; i < inputLog.size(); i++) {
        window->surface.DrawText(inputLog[i], 320, 32 + (24 * i));
    }
}

// GUI Components
bool Demo_Input::GUI_Button(const std::string &text, const int x, const int y, const int w, const int h, const bool highlighted) {
    const bool hovered = CheckCollisionPointRec(
        GetMousePosition(),
        (Rectangle) {
            (float)x, (float)y,
            (float)w, (float)h
        }
    );

    window->surface.DrawRectangleRounded(
        x, y, w, h, 4.0f,
        highlighted ? C_GREY :
            (hovered ? C_GREY : C_DKGREY)
    );

    window->surface.DrawText(text, x + 8, y + 6, 20, C_WHITE);

    return hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void Demo_Input::GUI_Nav(const int x, const int y) {
    // Background
    window->surface.DrawRectangle(x, y, 288, 720, {0x22, 0x22, 0x22, 0xff});

    // Items
    int appletY = 8;
    for(auto &[applet, name] : appletNames) {
        if(GUI_Button(name, x + 8, y + appletY, 272, 48, (currentApplet == applet))) {
            inputLog.clear();
            currentApplet = applet;
        }

        appletY += 52;
    }
}

void Demo_Input::GUI_Key(const std::string &label, const int x, const int y, const int w, const KeyboardKey key) {
    window->surface.DrawRectangleRounded(
        x, y, w, 48.0f, 6.0f,
        IsKeyDown(key) ? C_GREY : C_DKGREY
    );

    switch(key) {
        case KEY_LEFT_SUPER:
        case KEY_RIGHT_SUPER:
            window->surface.DrawTexture(assets->GetTexture("icon_key_super"), x, y);
            break;
        case KEY_KB_MENU:
            window->surface.DrawTexture(assets->GetTexture("icon_key_menu"), x, y);
            break;
        case KEY_TAB:
            window->surface.DrawTexture(assets->GetTexture("icon_key_tab"), x, y);
            break;
        case KEY_BACKSPACE:
            window->surface.DrawTexture(assets->GetTexture("icon_key_backspace"), x, y);
            break;
        case KEY_UP:
            window->surface.DrawSprite(*assets->GetSprite("icons_input_arrows"), 0, x, y);
            break;
        case KEY_DOWN:
            window->surface.DrawSprite(*assets->GetSprite("icons_input_arrows"), 1, x, y);
            break;
        case KEY_LEFT:
            window->surface.DrawSprite(*assets->GetSprite("icons_input_arrows"), 2, x, y);
            break;
        case KEY_RIGHT:
            window->surface.DrawSprite(*assets->GetSprite("icons_input_arrows"), 3, x, y);
            break;
        default:
            window->surface.DrawText(label, x + 8, y + 8, 20, C_WHITE);
            break;
    }
}

void Demo_Input::GUI_DrawNavKeys(const int x, const int y) {
    // Top keys
    GUI_Key("IN", x,       y, 48, KEY_INSERT);
    GUI_Key("HM", x + 64,  y, 48, KEY_HOME);
    GUI_Key("PU", x + 128, y, 48, KEY_PAGE_UP);
    GUI_Key("DL", x,       y + 64, 48, KEY_DELETE);
    GUI_Key("EN", x + 64,  y + 64, 48, KEY_END);
    GUI_Key("PD", x + 128, y + 64, 48, KEY_PAGE_DOWN);

    // Arrow keys
    GUI_Key("^", x + 64,    y + 160, 48, KEY_UP);
    GUI_Key("v", x + 64,    y + 224, 48, KEY_DOWN);
    GUI_Key("<", x,         y + 224, 48, KEY_LEFT);
    GUI_Key(">", x + 128,   y + 224, 48, KEY_RIGHT);
}

void Demo_Input::GUI_DrawKeyboard(const int x, const int y) {
    int curKeyY = 0;
    for(int row = 0; row < keySizes.size(); row++) {
        int curKeyX = 0;

        for(int key = 0; key < keySizes[row].size(); key++) {
            const int keySize = keySizes[row][key];

            GUI_Key(
                keyLabels[row][key].first,
                x + curKeyX, y + curKeyY,
                keySize * 16,
                keyLabels[row][key].second
            );

            curKeyX += (keySize + 1) * 16;
        }

        curKeyY += 64;
    }
}

void Demo_Input::GUI_DrawMouse(const int x, const int y) {
    // Body
    window->surface.DrawRectangleRounded(x, y + 32, 144, 224, 72.0f, C_DKGREY);
    window->surface.DrawTexture(assets->GetTexture("ui_input_wire"), x, y - 48);

    // LMB
    window->surface.DrawRectangleRounded(
        x, y + 32, 64, 96, 8.0f,
        IsMouseButtonDown(MOUSE_BUTTON_LEFT) ?
            C_LTGREY : C_GREY
    );

    // RMB
    window->surface.DrawRectangleRounded(
        x + 80, y + 32, 64, 96, 8.0f,
        IsMouseButtonDown(MOUSE_BUTTON_RIGHT) ?
            C_LTGREY : C_GREY
    );

    // Wheel
    window->surface.DrawRectangleRounded(
        x + 56, y + 32, 32, 96, 4.0f,
        IsMouseButtonDown(MOUSE_BUTTON_MIDDLE) ?
            C_LTGREY : GalaEngine::Colour {0x22, 0x22, 0x22, 0xff}
    );

    const float wheelMovement = GetMouseWheelMove();
    if(abs(wheelMovement) > EPSILON) {
        window->surface.DrawSprite(
            *assets->GetSprite("ui_input_wheel"),
            (wheelMovement > 0.0f) ? 0 : 1,
            x + 64, y + 32
        );
    }
}

int Demo_Input::GUI_Input(const std::string &inputName, const std::string &description, const int x, const int y, const int device) {
    const std::string text = inputName + ":\n  " + description;
    const Vector2 textSize = MeasureTextEx(GetFontDefault(), text.c_str(), 20, 0.0f);

    const float inputState = input->GetFloat(inputName, device);
    const int boxHeight    = textSize.y + 16;
    const int boxWidth     = inputState * 928.0f;

    window->surface.DrawRectangleRounded(x, y, 928, boxHeight, 8.0f, C_DKGREY);
    
    if(inputState >= 0.0f) {
        window->surface.DrawRectangleRounded(x, y, boxWidth, boxHeight, 8.0f, C_GREY);
    }else {
        window->surface.DrawRectangleRounded(x + 928 + boxWidth, y, -boxWidth, boxHeight, 8.0f, C_GREY);
    }

    window->surface.DrawText(text, x + 8, y + 8, 20, C_WHITE);
    window->surface.DrawText(std::to_string(inputState), x + 800.0f, y + 16, 20, C_LTGREY);

    return textSize.y + 16;
}

void Demo_Input::GUI_GamepadStick(const int x, const int y, const int side, const int device) {
    const Vector2 stickOffset = (side == 0) ?
        input->GetLeftJoystick(device) :
        input->GetRightJoystick(device);

    const bool stickButtonDown = (side == 0) ?
        IsGamepadButtonDown(device, GAMEPAD_BUTTON_LEFT_THUMB) :
        IsGamepadButtonDown(device, GAMEPAD_BUTTON_RIGHT_THUMB);

    window->surface.DrawCircle(x, y, 40.0f, {0x22, 0x22, 0x22, 0xff});
    window->surface.DrawCircle(
        x + (stickOffset.x * 20.0f),
        y + (stickOffset.y * 20.0f),
        20.0f, stickButtonDown ? C_DKGREY : C_GREY
    );
}

void Demo_Input::GUI_GamepadShoulder(const int x, const int y, const int side, const int device) {
    const float trigger = (side == 0) ?
        GetGamepadAxisMovement(device, GAMEPAD_AXIS_LEFT_TRIGGER) :
        GetGamepadAxisMovement(device, GAMEPAD_AXIS_RIGHT_TRIGGER);
    
    const bool shoulderButtonDown = (side == 0) ?
        IsGamepadButtonDown(device, GAMEPAD_BUTTON_LEFT_TRIGGER_1) :
        IsGamepadButtonDown(device, GAMEPAD_BUTTON_RIGHT_TRIGGER_1);

    // Trigger
    window->surface.DrawRectangleRounded(
        x, y, 80, 32, 8.0f,
        GalaEngine::Colour {0x22, 0x22, 0x22, 0xff}
    );

    window->surface.DrawRectangleRounded(
        x, y, trigger * 80.0f, 32, 8.0f,
        C_GREY
    );

    // Trigger
    window->surface.DrawRectangleRounded(
        x, y + 32, 80, 32, 8.0f,
        shoulderButtonDown ?
            C_GREY : GalaEngine::Colour {0x22, 0x22, 0x22, 0xff}
    );
}

void Demo_Input::GUI_GamepadFaceButtons(const int x, const int y, const int side, const int device) {
    const bool up = (side == 0) ?
        IsGamepadButtonDown(device, GAMEPAD_BUTTON_LEFT_FACE_UP) :
        IsGamepadButtonDown(device, GAMEPAD_BUTTON_RIGHT_FACE_UP);

    const bool down = (side == 0) ?
        IsGamepadButtonDown(device, GAMEPAD_BUTTON_LEFT_FACE_DOWN) :
        IsGamepadButtonDown(device, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);

    const bool left = (side == 0) ?
        IsGamepadButtonDown(device, GAMEPAD_BUTTON_LEFT_FACE_LEFT) :
        IsGamepadButtonDown(device, GAMEPAD_BUTTON_RIGHT_FACE_LEFT);

    const bool right = (side == 0) ?
        IsGamepadButtonDown(device, GAMEPAD_BUTTON_LEFT_FACE_RIGHT) :
        IsGamepadButtonDown(device, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT);

    window->surface.DrawCircle(x, y - 24, 16.0f, up    ? C_GREY : GalaEngine::Colour {0x22, 0x22, 0x22, 0xff});
    window->surface.DrawCircle(x, y + 24, 16.0f, down  ? C_GREY : GalaEngine::Colour {0x22, 0x22, 0x22, 0xff});
    window->surface.DrawCircle(x - 24, y, 16.0f, left  ? C_GREY : GalaEngine::Colour {0x22, 0x22, 0x22, 0xff});
    window->surface.DrawCircle(x + 24, y, 16.0f, right ? C_GREY : GalaEngine::Colour {0x22, 0x22, 0x22, 0xff});
}

void Demo_Input::GUI_GamepadMiddleButtons(const int x, const int y, const int device) {
    const bool leftDown   = IsGamepadButtonDown(device, GAMEPAD_BUTTON_MIDDLE_LEFT);
    const bool middleDown = IsGamepadButtonDown(device, GAMEPAD_BUTTON_MIDDLE);
    const bool rightDown  = IsGamepadButtonDown(device, GAMEPAD_BUTTON_MIDDLE_RIGHT);

    // Left (Select)
    window->surface.DrawRectangleRounded(
        x, y, 96, 32, 16.0f,
        leftDown ?
            C_GREY : GalaEngine::Colour {0x22, 0x22, 0x22, 0xff}
    );

    // Middle (X-button)
    window->surface.DrawRectangleRounded(
        x, y + 48, 96, 32, 16.0f,
        middleDown ?
            C_GREY : GalaEngine::Colour {0x22, 0x22, 0x22, 0xff}
    );

    // Right (Start)
    window->surface.DrawRectangleRounded(
        x, y + 96, 96, 32, 16.0f,
        rightDown ?
            C_GREY : GalaEngine::Colour {0x22, 0x22, 0x22, 0xff}
    );
}

void Demo_Input::GUI_DrawController(const int x, const int y, const int device) {
    window->surface.DrawRectangleRounded(
        x, y + 64,
        352, 208,
        16.0f,
        C_DKGREY
    );

    GUI_GamepadStick(x + 56, y + 120, 0, device);
    GUI_GamepadFaceButtons(x + 56, y + 216, 0, device);
    GUI_GamepadShoulder(x + 16, y, 0, device);

    GUI_GamepadStick(x + 296, y + 216, 1, device);
    GUI_GamepadFaceButtons(x + 296, y + 120, 1, device);
    GUI_GamepadShoulder(x + 256, y, 1, device);

    GUI_GamepadMiddleButtons(x + 128, y + 128, device);

    window->surface.DrawText("Device #" + std::to_string(currentGamepadDevice), x + 16, y+288, 20, C_LTGREY);
    
    if(GUI_Button("<", x + 140, y + 280, 32, 32))
        currentGamepadDevice--;

    if(GUI_Button(">", x + 180, y + 280, 32, 32))
        currentGamepadDevice++;
}

// Constructor
Demo_Input::Demo_Input() : Game(
    GalaEngine::GameInfo {
        "GalaEngine Input Demo (GalaEngine v" GALAENGINE_VERSION_STRING ")",
        "GalaEngine example project.",
        "Colleen (colleen05)",

        1280, 720,

        GalaEngine::AssetPathLayout {
            "./resources/",
            "textures/",
            "sprites/",
            "tilesets/",
            "sounds/",
            "fonts/"
        }
    }
) {}