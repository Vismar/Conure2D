#pragma once
#include "Core/Components/TransformComponent.hpp"
#include <typeindex>

namespace Core
{
    /*!
     * \brief Core scene object.
     * 
     * - Stores components as a map. 
     * - Guarantees that transform component always exist. 
     * - Stores pointers to all child objects in an array.
     * - Stores a pointer to it parent (may be nullptr if object do not actually has a parent).
     * 
     * Scene object - core and bones to which user supposed to add components that will make an object something unique.
     */
    class SceneObject final : public std::enable_shared_from_this<SceneObject>, public Utility::EventManager
    {
    public:
        SceneObject(const SceneObject& other) = delete;
        SceneObject(SceneObject&& other) = delete;
        SceneObject& operator=(const SceneObject& other) = delete;
        SceneObject& operator=(SceneObject&& other) = delete;
        ~SceneObject() = default;

        /*!
         * \brief Default constructor.
         * 
         * Automatically sets object id, default name and adds TransformComponent.
         */
        SceneObject();

        /*!
         * \brief Returns object id.
         * \return Id that is unique to that concrete object.
         */
        uint64_t GetId() const;

        /*!
         * \brief Returns object name.
         * \return Const reference to the object's name.
         */
        const std::string& GetName() const;

        /*!
         * \brief Sets specified string as an object name.
         * \param newName - new name that will be applied to the object.
         */
        void SetName(const std::string& newName);

        /*!
         * \brief Sets specified name as an object name
         * \param newName - double reference that will be moved to inner name variable and applied to the object.
         */
        void SetName(std::string&& newName);

        /*!
         * \brief Returns transform component of the object.
         * \return Weak pointer to the transform component of the object.
         */
        std::weak_ptr<TransformComponent> GetTransformComponent() const;

        /*!
         * \brief Adds requested component to the object.
         * \tparam Component - Type of component that will be added.
         * \return True if component was added.
         *         If such component was already added to the component map, false value will be returned.
         */
        template <class Component>
        bool AddComponent();

        /*!
         * \brief Returns component of the object.
         * \tparam Component - Type of component that was requested.
         * \return Weak pointer to the specified component of the object. 
         *         If such component was mot found in component map, empty pointer will be returned.
         */
        template <class Component>
        std::weak_ptr<Component> GetComponent() const;

        /*!
         * \brief Removes requested component from the object.
         * \tparam Component - Type of component that will be removed.
         */
        template <class Component>
        void RemoveComponent();

        /*!
         * \brief Returns parent of the object.
         * \return Weak pointer to the parent object.
         *         If object do not have a parent, empty pointer will be returned.
         */
        std::weak_ptr<SceneObject> GetParent() const;

        /*!
         * \brief Sets a specified object as a parent to the object.
         * \param newParent - shared pointer to the new parent object.
         */
        void SetParent(const std::shared_ptr<SceneObject>& newParent);
        
        /*!
         * \brief Removes child from the children list by specified id.
         * \param childId - id of a child that should be removed from the children list.
         */
        void RemoveChild(const uint64_t childId);

        /*!
         * \brief Returns list of children.
         * \return Reference to the array of children.
         */
        std::vector<std::shared_ptr<SceneObject>>& GetChildrenList();

    private:
        /*!
         * \brief Add specified object to the children list.
         * \param newChild - shared pointer to the object that will added to the children list.
         * \return True if an object was added. If such object was already in the list, false will be returned.
         */
        bool _AddChild(const std::shared_ptr<SceneObject>& newChild);

        /*!
         * \brief Initializes scene object.
         *
         * - Adds TransformComponent.
         */
        void _Initialize();

        /*!
         * \brief Updates object components// and all children.
         * 
         * "Update()" function will be called for every component that was added to the object.
         * //Then the same function will be called for every child in the children list.
         */
        void _Update();

        /*!
         * \brief LateUpdates object components// and all children.
         *
         * "LateUpdate()" function will be called for every component that was added to the object.
         * //Then the same function will be called for every child in the children list. \n
         * P.S. LateUpdate() called only after "Update()" of all objects in the scene.
         */
        void _LateUpdate();

        /*! Simple alias that was created just for a shorter name. */
        using ChildConstIterator = std::vector<std::shared_ptr<SceneObject>>::const_iterator;
        
        /*!
         * \brief Finds a child from the children list by specified object id.
         * \param childId - id of a child.
         * \return Iterator to the found child.
         *         If child was not found, iterator to the end() of the container will be returned.
         */
        ChildConstIterator _FindChild(const uint64_t childId) const;

        /*! Unique id of the object. */
        const uint64_t _objectId;
        /*! Name of the object. */
        std::string _name;
        /*! Map of components. Only one instance of a component should exist in the map. */
        std::unordered_map<std::type_index, std::shared_ptr<BaseComponent>> _componentMap;
        /*! Weak pointer to a parent scene object. */
        std::weak_ptr<SceneObject> _parent;
        /*! Array of shared pointers to the children of this object. */
        std::vector<std::shared_ptr<SceneObject>> _children;
        /*! Global static counter that is used to generate unique ids for scene objects upon it creation. */
        static std::atomic_uint64_t _globalIdCounter;

        friend class BaseScene;
    };

#include "SceneObject.inl"
}