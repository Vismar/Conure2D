#pragma once
#include "Renderer/RenderSystem.hpp"
#include "Core/Scene/SceneMap.hpp"
#include "Input/InputSystem.hpp"
#include "Utility/Time/TimeSpan.hpp"
#include "Utility/LogSystem/LogSystem.hpp"

namespace Engine
{
    /*!
     * \brief Main point of the engine.
     * 
     * Stores and initializes every single system that presents in the engine. 
     * Provides functionality to work with that systems and engine itself.
     */
    class EngineApp
    {
    public:
        EngineApp(const EngineApp& other) = delete;
        EngineApp(EngineApp&& other) = delete;
        EngineApp& operator=(const EngineApp& other) = delete;
        EngineApp& operator=(EngineApp&& other) = delete;
        ~EngineApp() = default;

        /*!
         * \brief Default constructor that initializes systems
         */
        EngineApp();

        /*!
         * \brief Instantiate static engine app variable.
         * \return Reference to the engine app.
         */
        static EngineApp& Instance();

        /*!
         * \brief Runs every system of the engine.
         */
        void Run();
        
        /*!
         * \brief Ends every system of the engine that were launched.
         */
        void End();

        /*!
         * \brief Returns render system.
         * \return Reference to the render system.
         */
        Renderer::RenderSystem& GetRenderSystem() const;

        /*!
         * \brief Returns scene map.
         * \return Reference to the scene map.
         */
        Core::SceneMap& GetSceneMap() const;

        /*!
         * \brief Returns input system.
         * \return Reference to the input system.
         */
        Input::InputSystem& GetInputSystem() const;

        /*!
         * \brief Grabs render loop time span.
         * \return Const reference to the time span of the render loop.
         */
        const Utility::TimeSpan& GetRenderLoopTimeSpan() const;

        /*!
         * \brief Grabs logic loop time span.
         * \return Const reference to the time span of the logic loop.
         */
        const Utility::TimeSpan& GetLogicLoopTimeSpan() const;

        /*!
         * \brief Returns log system.
         * \return Reference to the log system.
         */
        Utility::LogSystem& GetLogSystem() const;

    private:
        /*!
         * \brief Logic loop that runs in separate thread.
         */
        void _LogicLoop();

        /*! Time span of the render loop. */
        Utility::TimeSpan _renderLoopTimeSpan;
        /*! Unique pointer to the render system. */
        std::unique_ptr<Renderer::RenderSystem> _renderSystem;
        /*! Atomic flag for logic thread. */
        std::atomic<bool> _logicThreadIsWorking;
        /*! Time span of the logic loop. */
        Utility::TimeSpan _logicLoopTimeSpan;
        /*! Unique pointer to the scene map system. */
        std::unique_ptr<Core::SceneMap> _sceneMap;
        /*! Unique pointer to the input system.*/
        std::unique_ptr<Input::InputSystem> _inputSystem;
        /*! Unique pointer to the log system. */
        std::unique_ptr<Utility::LogSystem> _logSystem;
    };
}
