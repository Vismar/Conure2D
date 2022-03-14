#pragma once
#include "Render/Temp/RenderSystem.hpp"
#include "Core/Scene/SceneMap.hpp"
#include "Input/InputSystem.hpp"

namespace C2D
{
    /*!
     * \brief Main point of the engine.
     * 
     * Stores and initializes every single system that presents in the engine. 
     * Provides functionality to work with that systems and engine itself.
     */
    class [[deprecated("Will be reimplemented")]] EngineApp
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
        void End() const;

        /*!
         * \brief Returns render system.
         * \return Reference to the render system.
         */
        RenderSystem& GetRenderSystem() const;

        /*!
         * \brief Returns scene map.
         * \return Reference to the scene map.
         */
        SceneMap& GetSceneMap() const;

        /*!
         * \brief Returns input system.
         * \return Reference to the input system.
         */
        InputSystem& GetInputSystem() const;

        /*!
         * \brief Grabs render loop time span.
         * \return Const reference to the time span of the render loop.
         */
        //const TimeSpan& GetRenderLoopTimeSpan() const;

        /*!
         * \brief Grabs logic loop time span.
         * \return Const reference to the time span of the logic loop.
         */
        //const TimeSpan& GetLogicLoopTimeSpan() const;

        /*!
         * \brief Returns IO system.
         * \return Reference to the IO system.
         */
        //IOSystem& GetIOSystem() const;

        /*!
         * \brief Returns log system.
         * \return Reference to the log system.
         */
        //LogSystem& GetLogSystem() const;

    private:
        /*!
         * \brief Logic loop that runs in separate thread.
         */
        void _LogicLoop();

        /*! Unique pointer to the IO system. */
        //std::unique_ptr<IOSystem> _ioSystem;
        /*! Unique pointer to the log system. */
        //std::unique_ptr<LogSystem> _logSystem;
        /*! Time span of the render loop. */
        //TimeSpan _renderLoopTimeSpan;
        /*! Unique pointer to the render system. */
        std::unique_ptr<RenderSystem> _renderSystem;
        /*! Atomic flag for logic thread. */
        std::atomic<bool> _logicThreadIsWorking;
        /*! Time span of the logic loop. */
        //TimeSpan _logicLoopTimeSpan;
        /*! Unique pointer to the scene map system. */
        std::unique_ptr<SceneMap> _sceneMap;
        /*! Unique pointer to the input system.*/
        std::unique_ptr<InputSystem> _inputSystem;
    };
}
