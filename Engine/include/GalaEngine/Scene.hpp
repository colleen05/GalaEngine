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
            int _width  = 640;  //!< Scene width.
            int _height = 480;  //!< Scene height.

        public:
            /*! @name Internal Data & Structures
             *  @details These are internal containers and data for the Scene
             *  to keep track of and manage by itself.
             *  @warning It is highly recommended against modifying the
             *  contents of these containers directly. Doing so may result in
             *  unintentional stale pointer bugs.
             */
            /// @{
            std::map<std::string, Entity*>  entities;  //!< Map of names to entities.
            std::vector<Layer*> layers; //!< Vector of layers.
            /// @}

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
             */
            /// @{
            /*! @brief Push an entity to the Scene.
             *  @details Pushes an entity into the entity container,
             *  submitting the management to the Scene and its members.
             *  @param entity The entity to push.
             *  @param name The entity name.
             *  @attention Once you push an Entity, deleting it before calling
             *  **RemoveEntity()** will cause stale pointers.
             */
            void PushEntity(Entity *entity, const std::string &name = "");
            /*! @brief Get entity from the Scene.
             *  @details Gets a pointer to an entity, if found by name (or
             *  **nullptr**).
             *  @param name The name of the entity to get.
             *  @returns A pointer to the found entity (or **nullptr**).
             *  @attention Be cautious about using pointers returned by this
             *  function, as they may quickly go stale.
             */
            Entity *GetEntity(const std::string &name);
            /*! @brief Remove entity from the scene (by name).
             *  @details Removes an entity from the entity containers (by
             *  name), and (by default), destroys the entity.
             *  @param name The name of the entity.
             *  @param destroy Whether or not to destroy and delete the entity.
             */
            void RemoveEntity(const std::string &name, const bool destroy = true);
            /*! @brief Remove entity from the scene (by pointer).
             *  @details Removes an entity from the entity containers (by
             *  pointer), and (by default), destroys the entity.
             *  @param entity A pointer to the entity to remove.
             *  @param destroy Whether or not to destroy and delete the entity.
             */
            void RemoveEntity(Entity *entity, const bool destroy = true);
            /*! @brief Push a Layer to the Scene.
             *  @details Pushes an existing Layer into the layer containers,
             *  submitting the management to the Scene.
             *  @param layer A pointer to the layer.
             *  @param position The position to insert into. If -1, will push to the end.
             *  @returns Layer position.
             *  @attention Once you push a Layer, deleting it before calling
             *  **RemoveLayer()** will cause stale pointers.
             */
            size_t PushLayer(Layer *layer, int position = -1);
            /*! @brief Get layer from the Scene.
             *  @details Gets a pointer to a layer, if found by position (or
             *  **nullptr**).
             *  @param position The position of the layer to get.
             *  @returns A pointer to the found layer (or **nullptr**).
             *  @attention Be cautious about using pointers returned by this
             *  function, as they may quickly go stale.
             */
            Layer *GetLayer(const int position);
            /*! @brief Remove layer from the scene (by pointer).
             *  @details Removes a layer from the layer container (by
             *  position), and (by default), destroys the layer.
             *  @param position The position of the layer.
             *  @param destroy Whether or not to destroy and delete the layer.
             */
            void RemoveLayer(const int position, const bool destroy = true);
            /*! @brief Remove layer from the scene (by pointer).
             *  @details Removes a layer from the layer container (by
             *  pointer), and (by default), destroys the layer.
             *  @param layer A pointer to the layer to remove.
             *  @param destroy Whether or not to destroy and delete the layer.
             */
            void RemoveLayer(Layer *layer, const bool destroy = true);
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
             *  @details Updates the width and height, and (optionally) resizes
             *  all layers.
             *  @param width New width
             *  @param height New height
             *  @param resizeLayers Whether or not to resize layers.
             */
            void Resize(const int width, const int height, const bool resizeLayers = true);
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