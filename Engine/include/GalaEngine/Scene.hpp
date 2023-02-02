// Project: GalaEngine
// File: Scene.hpp
// Description: Scene class for managing entities and layers
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <GalaEngine/Entity.hpp>
#include <GalaEngine/Layer.hpp>
#include <GalaEngine/BackgroundLayer.hpp>
#include <GalaEngine/EntityLayer.hpp>
#include <GalaEngine/TileLayer.hpp>
#include <GalaEngine/Camera.hpp>
#include <GalaEngine/AssetManager.hpp>
#include <GalaEngine/InputManager.hpp>
#include <GalaEngine/SoundManager.hpp>
#include <GalaEngine/Window.hpp>
#include <iostream>
#include <map>
#include <stdint.h>

namespace GalaEngine {
    /*! @brief Scene class
     *  @details Class for managing various game elements such as layers,
     *  entities, assets, etc... Use this as an interface between these
     *  so-called elements from the Game class.
     */
    class Scene {
        protected:
            /*! @name Internal Data & Structures
             *  @details These are internal containers and data for the Scene
             *  to keep track of and manage by itself.
             */
            /// @{
            std::map<uint8_t, Layer*>   _layers;    //!< Map of Layer IDs to layers.
            std::map<uint32_t, Entity*> _entities;  //!< Map of Entity IDs to entities.

            std::map<std::string, uint8_t>  _layerNames;    //!< Map of names to Layer IDs.
            std::map<std::string, uint32_t> _entityNames;   //!< Map of names to Entity IDs.

            int _width  = 640;  //!< Scene width
            int _height = 480;  //!< Scene height
            /// @}

        public:
            // Surface, camera, and asset manager
            Surface *targetSurface = nullptr;   //!< The Surface everything is rendered to.
            GalaEngine::Camera mainCamera;      //!< The main Camera.

            /*! @name Game Context Members
             *  @details These members are of game context elements, which are
             *  passed down from the Game class, to this class, and finally, to
             *  the Entity class.
             */
            /// @{
            GalaEngine::Window *window = nullptr;       //!< The game's window.
            GalaEngine::AssetManager *assets = nullptr; //!< The primary asset managing interface.
            GalaEngine::InputManager *input  = nullptr; //!< The primary input interface.
            GalaEngine::SoundManager *sound  = nullptr; //!< The primary sound interface.
            /// @}

            /*! @name Entities & Layers
             *  @details Here are functions which handle entity and layer
             *  management.
             *  @todo
             *  - Add **RemoveEntity()**
             *  - Add **RemoveLayer()**
             */
            /// @{
            /*! @brief Push an Entity to the Scene.
             *  @details Pushes an entity into the entity containers,
             *  submitting the management to the Scene and its members.
             *  @param entity The entity to push.
             *  @param name The entity name.
             *  @returns The ID of the newly pushed entity.
             *  @attention Once you push an Entity, deleting it before calling
             *  **RemoveEntity()** will cause stale pointers.
             */
            uint32_t PushEntity(Entity *entity, const std::string &name = "");
            /*! @brief Get Entity from the Scene.
             *  @details Gets a pointer to an Entity, if found by name (or
             *  **nullptr**).
             *  @param name The name of the entity to get.
             *  @returns A pointer to the found entity (or **nullptr**).
             *  @attention Be cautious about using pointers returned by this
             *  function, as they may quickly go stale.
             */
            Entity *GetEntity(const std::string &name);
            /*! @brief Push a Layer to the Scene.
             *  @details Pushes an existing Layer into the layer containers,
             *  submitting the management to the Scene.
             *  @param layer A pointer to the layer.
             *  @param position The position to insert into. If -1, will push to the end.
             *  @attention Once you push a Layer, deleting it before calling
             *  **RemoveLayer()** will cause stale pointers.
             */
            void PushLayer(Layer *layer, const int position = -1);
            /*! @brief Create and push a BackgroundLayer.
             *  @details Creates a BackgroundLayer and pushes it into the layer
             *  containers.
             *  @param texture The background texture.
             *  @param clearColour The background colour.
             *  @param position The position to insert into.
             *  @returns A pointer to the new layer.
             *  @see PushLayer()
             *  @see BackgroundLayer
             */
            BackgroundLayer *AddBackgroundLayer(const Texture texture, const Colour clearColour = C_CLEAR, const int position = -1);
            /*! @brief Create and push an EntityLayer.
             *  @details Creates an EntityLayer and pushes it into the layer
             *  containers.
             *  @param clearColour The layer's Surface clear colour.
             *  @param position The position to insert into.
             *  @returns A pointer to the new layer.
             *  @see PushLayer()
             *  @see EntityLayer
             */
            EntityLayer *AddEntityLayer(const Colour clearColour = C_CLEAR, const int position = -1);
            /*! @brief Create and push a TileLayer.
             *  @details Creates a TileLayer and pushes it into the layer
             *  containers.
             *  @param tileset The Tileset to use.
             *  @param tiles The tilemap vector.
             *  @param width Number of tiles horizontally.
             *  @param height Number of the tiles vertically.
             *  @param clearColour The layer's Surface clear colour.
             *  @param position The position to insert into.
             *  @returns A pointer to the new layer.
             *  @see PushLayer()
             *  @see TileLayer
             */
            TileLayer *AddTileLayer(const Tileset &tileset, const std::vector<uint16_t> &tiles, const int width, const int height, const Colour clearColour = C_CLEAR, const int position = -1);
            /// @}

            /*! @name Misc. Interfacing
             */
            /// @{
            /*! @brief Resize the Scene.
             *  @details Updates the width and height, and resizes all layers.
             *  @param width New width
             *  @param height New height
             */
            void Resize(const int width, const int height);
            Vector2 GetSize();      //!< Get the size of the Scene.
            void Update();          //!< Update the Scene.
            void RenderLayers();    //!< Render all the contained layers.
            /// @}

            /*! @brief Constructor
             *  @details Constructs a new Scene with specified width, height,
             *  and existing Surface.
             *  @param targetSurface The surface to draw to (such as a Window surface).
             *  @param width The width of the Scene.
             *  @param height The height of the Scene.
             */
            Scene(Surface *targetSurface, const int width = 640, const int height = 480);
            Scene();
    };
}