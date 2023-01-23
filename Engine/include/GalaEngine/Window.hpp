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
            int     GetMonitorWidth         (const int monitor = -1);
            int     GetMonitorHeight        (const int monitor = -1);
            Vector2 GetMonitorSize          (const int monitor = -1);
            float   GetMonitorPhysicalWidth (const int monitor = -1);
            float   GetMonitorPhysicalHeight(const int monitor = -1);
            Vector2 GetMonitorPhysicalSize  (const int monitor = -1);
            float   GetMonitorRefreshRate   (const int monitor = -1);

            std::string GetMonitorName(const int monitor = -1);

            // Setters
            void SetTitle(const std::string &title);

            void ToggleFullscreen   ();
            void SetMinimised       (const bool minimised);
            void SetMaximised       (const bool maximised);

            void SetWidth       (const int width);
            void SetHeight      (const int height);
            void SetSize        (const int width, const int height);
            void SetPosition    (const int x, const int y);
            void SetTargetFPS   (const float fps);

            // Constructors
            Window(const std::string &title, const int width, const int height, const int targetFPS = 60);
            Window();
    };
}