// Project: GalaEngine
// File: Game.hpp
// Description: Game class
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <GalaEngine/Window.hpp>
#include <GalaEngine/AssetManager.hpp>
#include <GalaEngine/InputManager.hpp>
#include <GalaEngine/SoundManager.hpp>
#include <GalaEngine/Surface.hpp>
#include <GalaEngine/Scene.hpp>
#include <iostream>
#include <array>

namespace GalaEngine {
    /*! @brief Game information
     *  @details Contains information on a game, such as metadata, settings,
     *  and other information which is useful for the runtime of the game.
     */
    struct GameInfo {
        std::string title;          //!< Title that will be displayed in the window.
        std::string description;    //!< Description of the game.
        std::string author;         //!< Author(s) of the game.

        int defaultWidth;   //!< Default width for game window.
        int defaultHeight;  //!< Default height for game window.

        AssetPathLayout assetPaths; //!< Path layout for resource files.
    };

    /*! @brief Base game class
     *  @details This class is the container for all base game logic and
     *  context members. Override this class to define your basic game
     *  behaviour.
     */
    class Game {
        protected:
            bool _shouldEnd = false;                    //!< Should the game end?
            std::array<bool, KEY_KP_EQUAL> _keyStates;  //!< Key states.

        public:
            GameInfo info; //!< Game information and metadata

            /*! @name Game Context Members
             *  @details These members are of game context elements, which
             *  are passed down to multiple classes.
             */
            /// @{
            GalaEngine::Window       *window = nullptr; //!< Game window.
            GalaEngine::Scene        *scene  = nullptr; //!< Container for layers and entities.
            GalaEngine::AssetManager *assets = nullptr; //!< Manager for assets.
            GalaEngine::InputManager *input  = nullptr; //!< Input bindings manager.
            GalaEngine::SoundManager *sound  = nullptr; //!< Sound management.
            /// @}

            /*! @name "Event" Methods
             *  @details These methods are executed at different points within
             *  the Game's lifetime. Override these functions to define your
             *  own game behaviour.
             */
            /// @{
            /*! @brief Loading behaviour.
             *  @details This function is called once upon the game starting.
             *  Override this function to define start-up behaviour, such as
             *  pre-loading assets, setting up subsystems, and/or setting up
             *  the scene.
             */
            virtual void OnLoad();
            /*! @brief Updating behaviour.
             *  @details This function is called repeatedly. Overload this
             *  function to define behaviour that should be executed as fast
             *  as possible.
             */
            virtual void OnUpdate();
            /*! @brief Drawing behaviour.
             *  @details This function is called once per frame, always after
             *  **OnLoad()**. Override this function to define behaviour that
             *  should be called once per frame, such as drawing.
             */
            virtual void OnDraw();
            /*! @brief Unloading behaviour.
             *  @details This function is called once upon the game ending.
             *  Override this function to define at-end behaviour, such as
             *  clearing memory, de-initialising subsystems, creating backup
             *  saves, etc...
             */
            virtual void OnUnload();
            /// @}

            void Start();   //!< Start the game.
            void End();     //!< End the game.
            
            /*! @brief Constructor
             *  @details Called upon initialisation. It is not recommended to
             *  override this function.
             *  @param info Game info
             */
            Game(const GameInfo &info);
            Game();
    };
}