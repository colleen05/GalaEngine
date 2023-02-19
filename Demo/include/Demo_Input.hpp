// Project: GalaEngine Demo
// File: Demo_Input.hpp
// Description: Input management & binding demo.
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <GalaEngine/EngineInfo.hpp>
#include <GalaEngine/Game.hpp>
#include <GalaEngine/Colour.hpp>
#include <iostream>
#include <cmath>

class Demo_Input : public GalaEngine::Game {
    public:
        // Sizes of key buttons in units of 16 pixels.
        const std::vector<std::vector<int>> keySizes = {
            {3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  6},
            {4,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  5},
            {5,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  8},
            {6,  3,  3,  3,  3,  3,  3,  3,  3,  3,  3,  11},
            {5,  4,  4,  21, 4,  4,  4,  5}
        };

        // Keycode and display text for each key.
        const std::vector<std::vector<std::pair<std::string, KeyboardKey>>>
        keyLabels = {
            {{"~", KEY_GRAVE},            {"1", KEY_ONE},  {"2", KEY_TWO},  {"3", KEY_THREE},  {"4", KEY_FOUR},  {"5", KEY_FIVE},  {"6", KEY_SIX},  {"7", KEY_SEVEN},  {"8", KEY_EIGHT},  {"9", KEY_NINE},    {"0", KEY_ZERO},       {"-", KEY_MINUS},         {"+", KEY_EQUAL},          {"BKSP", KEY_BACKSPACE}},
            {{"TAB", KEY_TAB},            {"Q", KEY_Q},    {"W", KEY_W},    {"E", KEY_E},      {"R", KEY_R},     {"T", KEY_T},     {"Y", KEY_Y},    {"U", KEY_U},      {"I", KEY_I},      {"O", KEY_O},       {"P", KEY_P},          {"{", KEY_LEFT_BRACKET},  {"}", KEY_RIGHT_BRACKET},  {"\\", KEY_BACKSLASH}},
            {{"CAPS", KEY_CAPS_LOCK},     {"A", KEY_A},    {"S", KEY_S},    {"D", KEY_D},      {"F", KEY_F},     {"G", KEY_G},     {"H", KEY_H},    {"J", KEY_J},      {"K", KEY_K},      {"L", KEY_L},       {";", KEY_SEMICOLON},  {"'", KEY_APOSTROPHE},    {"ENTER", KEY_ENTER}},
            {{"SHIFT", KEY_LEFT_SHIFT},   {"Z", KEY_Z},    {"X", KEY_X},    {"C", KEY_C},      {"V", KEY_V},     {"B", KEY_B},     {"N", KEY_N},    {"M", KEY_M},      {"<", KEY_COMMA},  {">", KEY_PERIOD},  {"/", KEY_SLASH},      {"SHIFT", KEY_RIGHT_SHIFT}},
            {{"CTRL", KEY_LEFT_CONTROL},  {" ", KEY_LEFT_SUPER},  {"ALT", KEY_LEFT_ALT},  {"", KEY_SPACE},  {"ALT", KEY_RIGHT_ALT},  {" ", KEY_RIGHT_SUPER},  {" ", KEY_KB_MENU},  {"CTRL", KEY_RIGHT_CONTROL}}
        };

        // Applets
        enum class Applet {
            Overview,
            Binding,
            Log
        } currentApplet = Applet::Overview;

        const std::map<Applet, std::string> appletNames = {
            {Applet::Overview, "Overview"},
            {Applet::Binding, "Bindings"},
            {Applet::Log, "Input Log"}
        };

        // Etc..
        std::map<std::string, std::string> bindingDescriptions;
        std::vector<std::string> inputLog;
        int currentGamepadDevice = 0;

        // Game class overrides
        void OnLoad();
        void OnDraw();
        void OnUpdate();
        void OnUnload();

        // Extra input stuff
        std::vector<MouseButton> GetMouseButtonsPressed();

        // Applets
        void Applet_Overview();
        void Applet_Binding();
        void Applet_Log();

        // GUI Components
        bool GUI_Button(const std::string &text, const int x, const int y, const int w, const int h, const bool highlighted = false);
        void GUI_Nav(const int x, const int y);

        void GUI_Key(const std::string &label, const int x, const int y, const int w, const KeyboardKey key);
        void GUI_DrawKeyboard(const int x, const int y);
        int  GUI_Input(const std::string &inputName, const std::string &description, const int x, const int y, const int device = 0);
        
        void GUI_GamepadStick(const int x, const int y, const int side, const int device = 0);
        void GUI_GamepadShoulder(const int x, const int y, const int side, const int device = 0);
        void GUI_GamepadFaceButtons(const int x, const int y, const int side, const int device = 0);
        void GUI_GamepadMiddleButtons(const int x, const int y, const int device = 0);
        void GUI_DrawController(const int x, const int y, const int device = 0);

        // Constructor
        Demo_Input();
};