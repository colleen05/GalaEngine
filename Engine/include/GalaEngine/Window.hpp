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
    /*! @brief Window class
     *  @details Contains an interface for controlling the game's window.
     */
    class Window {
        private:
            std::string _title;     //!< Window title
            int _width;             //!< Window width
            int _height;            //!< Window height
            int _targetFPS;         //!< Target FPS
            std::array<bool, KEY_KP_EQUAL> _keyStates; //!< Key states

        public:
            Surface surface; //!< Top-level render target.

            /*! @name General Functions
             *  @details These functions are called at different stages of the
             *  Window's lifetime.
             */
            /// @{
            void Init();    //!< Setup window and surface.
            void Render();  //!< Draw **surface** to window.
            void Close();   //!< Close window.
            /// @}

            /*! @name Getters
             *  @details Use these functions to get current properties of the
             *  window.
             *  @param monitor A monitor ID (_**-1** means the **current monitor**_).
             */
            /// @{
            bool ShouldClose();     //!< Get whether or not the window should close.
            bool IsReady();         //!< Get whether or not the window is ready for use.
            bool IsFullscreen();    //!< Get whether or not the window is fullscreen.
            bool IsMinimised();     //!< Get whether or not the window is minimised.
            bool IsMaximised();     //!< Get whether or not the window is maximised.
            bool IsFocused();       //!< Get whether or not the window is focused.
            bool IsResized();       //!< Get whether or not the window has been resized.

            float GetFPS(); //!< Get the current FPS.

            int GetWidth();             //!< Get the current width of the window.
            int GetHeight();            //!< Get the current height of the window.
            Vector2 GetSize();          //!< Get the current size of the window.
            Vector2 GetPosition();      //!< Get the current position of the window.
            int GetMonitorCount();      //!< Get the number of monitors available.
            int GetCurrentMonitor();    //!< Get the current monitor's ID.

            int GetMonitorWidth(const int monitor = -1);            //!< Get the specified monitor's width.
            int GetMonitorHeight(const int monitor = -1);           //!< Get the specified monitor's height.
            Vector2 GetMonitorSize(const int monitor = -1);         //!< Get the specified monitor's size.
            float GetMonitorPhysicalWidth(const int monitor = -1);  //!< Get the specified monitor's physical width.
            float GetMonitorPhysicalHeight(const int monitor = -1); //!< Get the specified monitor's physical height.
            Vector2 GetMonitorPhysicalSize(const int monitor = -1); //!< Get the specified monitor's physical size.
            float GetMonitorRefreshRate(const int monitor = -1);    //!< Get the specified monitor's refresh rate.
            std::string GetMonitorName(const int monitor = -1);     //!< Get the name of the specified monitor.
            /// @}

            /*! @name Setters
             *  @details Use these functions to set current properties of the
             *  window.
             */
            /// @{
            void SetTitle(const std::string &title);    //!< Set the current 

            void ToggleFullscreen();    //!< Toggle whether or not the window is fullscreen.
            void SetMinimised();        //!< Set minimised.
            void SetMaximised();        //!< Set maximised.

            void SetWidth       (const int width);                      //!< Set the width of the window.
            void SetHeight      (const int height);                     //!< Set the height of the window.
            void SetSize        (const int width, const int height);    //!< Set the size of the window.
            void SetPosition    (const int x, const int y);             //!< Set the position of the window.
            void SetTargetFPS   (const float fps);                      //!< Set the target FPS of the window.
            /// @}

            /*! @brief Constructor
             *  @details Construct a window with a title, size, and target FPS.
             *  @param title The title of the window.
             *  @param width The width of the window.
             *  @param height The height of the window.
             *  @param targetFPS The target FPS of the window.
             */
            Window(const std::string &title, const int width, const int height, const int targetFPS = 60);
            Window();
    };
}