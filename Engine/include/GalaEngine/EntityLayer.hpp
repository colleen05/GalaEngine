// Project: GalaEngine
// File: EntityLayer.hpp
// Description: Inherited class from Layer which supports entity updating and rendering
// Authors: Colleen (@colleen05)
// https://github.com/colleen05/GalaEngine
// Distributed under the zlib license.

#pragma once

#include <GalaEngine/Layer.hpp>
#include <GalaEngine/Entity.hpp>
#include <algorithm>

namespace GalaEngine {
    /*! @brief Entities layer
     *  @details Manages updating and rendering entities to its Surface.
     *  @see Entity
     */
    class EntityLayer : public Layer {
        public:
            /*! @brief Vector of entities.
             *  @details Vector of pointers to the entities managed by the
             *  Entitylayer.
             *  @attention It is strongly advised not to use the pointers
             *  within this vector for deletion of entities, as this can
             *  result in **stale pointers** elsewhere.
             */
            std::vector<GalaEngine::Entity*> entities;

            /*! @brief Attach an entity to the layer.
             *  @details Adds an Entity pointer to the **entities** vector for
             *  management by the EntityLayer.
             *  @param entity A pointer to the Entity you wish to attach. 
             */
            void AddEntity(GalaEngine::Entity *entity);
            /*! @brief Detach an entity from the layer.
             *  @details Removes an Entity pointer from the **entities** vector
             *  (if it exists), thus halting management of the Entity by the
             *  EntityLayer.
             *  @attention This does not delete the Entity in memory. For now,
             *  you must manually manage the memory of entities.
             */
            void RemoveEntity(const GalaEngine::Entity *entity);

            /*! @name Inherited Methods
             *  @details These functions are overridden from the Layer class,
             *  and define behaviour relevant to tile rendering.
             */
            /// @{
            void OnStart();                                 //!< No special behaviour.
            void OnUpdate();                                //!< Update entities.
            void OnDraw(const GalaEngine::Camera &camera);  //!< Draw entities to the Surface.
            void OnDestroy();                               //!< No special behaviour.
            /// @}

            /*! @brief Constructor
             *  @details Construct and create Surface (width x height), with
             *  specified clearColour, to which entities will be drawn on.
             *  @param width The width of the Surface.
             *  @param height The height of the Surface.
             *  @param clearColour What colour the Surface should be cleared with.
             */
            EntityLayer(const int width, const int height, const Colour clearColour);
            EntityLayer();
            ~EntityLayer();
    };
}