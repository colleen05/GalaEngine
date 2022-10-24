// Project: GalaEngine
// File: Window.hpp
// Description: Window creation and management class.
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <raylib.h>
#include <string>
#include <array>
#include <GalaEngine/Surface.hpp>

namespace GalaEngine {
    class Window {
        private:
            std::string _title;
            int _width, _height;
            int _targetFPS;
            std::array<bool, KEY_KP_EQUAL> _keyStates;

        public:
            // Surface
            Surface surface;

            // Events
            void Init();
            void Render();
            void Close();

            // Getters
            bool ShouldClose();
            bool IsReady();
            bool IsFullscreen();
            bool IsMinimised();
            bool IsMaximised();
            bool IsFocused();
            bool IsResized();

            float   GetFPS();

            int     GetWidth                ();
            int     GetHeight               ();
            Vector2 GetSize                 ();
            Vector2 GetPosition             ();
            int     GetMonitorCount         ();
            int     GetCurrentMonitor       ();
            int     GetMonitorWidth         (int monitor = -1);
            int     GetMonitorHeight        (int monitor = -1);
            Vector2 GetMonitorSize          (int monitor = -1);
            float   GetMonitorPhysicalWidth (int monitor = -1);
            float   GetMonitorPhysicalHeight(int monitor = -1);
            Vector2 GetMonitorPhysicalSize  (int monitor = -1);
            float   GetMonitorRefreshRate   (int monitor = -1);

            std::string GetMonitorName(int monitor = -1);

            // Setters
            void SetTitle(std::string title);

            void ToggleFullscreen   ();
            void SetMinimised       (bool minimised);
            void SetMaximised       (bool maximised);

            void SetWidth       (int width);
            void SetHeight      (int height);
            void SetSize        (int width, int height);
            void SetPosition    (int x, int y);
            void SetTargetFPS   (float fps);

            // Constructors
            Window(std::string title, int width, int height, int targetFPS = 60);
            Window();
    };
}