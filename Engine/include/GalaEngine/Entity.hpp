// Project: GalaEngine
// File: Entity.hpp
// Description: Entity class
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <raylib.h>
#include <iostream>
#include <GalaEngine/Sprite.hpp>
#include <GalaEngine/Colour.hpp>
#include <GalaEngine/AssetManager.hpp>
#include <GalaEngine/InputManager.hpp>
#include <GalaEngine/SoundManager.hpp>
#include <GalaEngine/Window.hpp>
#include <GalaEngine/Layer.hpp>

namespace GalaEngine {
    /*! @brief Entity base class
     *  @details An object that has a renderable sprite, and custom behaviour,
     *  which is managed by classes such as EntityLayer and Scene. Override
     *  this class to create your own entities.
     */
    class Entity {
        public:
            /*! @name Game Context Members
             *  @details These members are of game context elements, which are
             *  passed down from the Game class, to the Scene class, and
             *  finally, to the Entity class.
             */
            /// @{
            GalaEngine::Window       *window = nullptr; //!< Pointer to the game's window.
            GalaEngine::AssetManager *assets = nullptr; //!< Pointer to the game's asset management interface.
            GalaEngine::InputManager *input  = nullptr; //!< Pointer to the game's input management interface.
            GalaEngine::SoundManager *sound  = nullptr; //!< Pointer to the game's sound management interface.
            /// @}

            /*! @name Scene Context Members
             *  @details These members are of scene context elements, which are
             *  updated by the Scene class.
             */
            /// @{
            int sceneWidth  = 0; //!< Scene width
            int sceneHeight = 0; //!< Scene height
            std::map<std::string, Entity*>  *sceneEntities  = nullptr; //!< Pointer to the scene's entities container.
            std::vector<Layer*>             *sceneLayers    = nullptr; //!< Pointer to the scene's layers container.
            /// @}
            
            /*! @brief The current layer's Surface.
             *  @details Pointer to the current layer's (usually an
             *  EntityLayer's) Surface. Drawing to this surface can be useful,
             *  such as drawing simple particles, or debugging info.
             */
            GalaEngine::Surface *layerSurface = nullptr;

            /*! @name Transform Properties
             *  @details These members are transform properties, which can be
             *  used for positioning a rendered sprite with rotation and scale
             *  (such as with an EntityLayer), collision detection, or physics.
             */
            /// @{
            Vector2 position    = {0.0f, 0.0f}; //!< The physical position of the entity.
            Vector2 scale       = {1.0f, 1.0f}; //!< The scale of the entity.
            float   rotation    = 0.0f;         //!< The rotation of the entity (in degrees).
            /// @}

            /*! @name Visual Properties
             *  @details These members are used by the EntityLayer when
             *  rendering the sprite.
             */
            /// @{
            Sprite *sprite      = nullptr;  //!< Pointer to sprite.
            int     spriteFrame = 0;        //!< The current frame of the sprite.
            Colour  blendColour = C_WHITE;  //!< The blend colour of the sprite.
            /// @}

            /*! @name Misc. Context Properties
             *  @details These members are miscellaneous context, which are
             *  (often) updated or used by other classes.
             */
            /// @{
            Vector2     sceneMousePosition = {0.0f, 0.0f};      //!< Where the mouse is in scene-coordinates (rather than within the window).
            Vector2     bboxSize = {32.0f, 32.0f};              //!< The size of the bounding-box of the entity.
            Rectangle   bbox     = {0.0f, 0.0f, 32.0f, 32.0f};  //!< The bounding-box of the entity after calculations.
            /// @}


            /*! @name "Event" methods
             *  @details These functions are executed by other classes, such as
             *  the EntityLayer class, upon different stages of the Entity's
             *  lifetime. Override these functions to define behaviour to be
             *  executed upon different events.
             */
            /// @{
            virtual void OnSignal(const std::string &message);  //!< Handle messages (e.g., commands) from other classes or entities.
            virtual void OnStart();     //!< Behaviour executed upon attaching to a Scene.
            virtual void OnUpdate();    //!< Behaviour executed upon a Scene update.
            virtual void OnDraw();      //!< Behaviour executed once per frame.
            virtual void OnDestroy();   //!< Behaviour executed upon destruction.
            /// @}

            /*! @brief Constructor
             *  @details Constructs an entity with supplied coordinates.
             *  @param x X coordinate.
             *  @param y Y coordinate.
             */
            Entity(int x, int y);
            Entity();
    };
}