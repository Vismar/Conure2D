# Changelog

## Plans
- **Box2d** - include box2d functionality to the engine.
- **Debug info** - debug information that helps the development.

## WIP
- **Engine**
  - **EngineApp** - handles whole work of the engine application and all other systems. Works in 2 threads: one for render loop and the second one for the game logic.
  - **EngineInterface** - the point from which user can get any engine system and work with it in game logic. Provides access to:
    - `RenderSystemInterface` - interface to render system.
    - `SceneMapSystemInterface` - interface to scene map system.
    - `InputSystemInterface` - interface to input system.
    - `RenderLoopTimeSpan` - time span of the previous render loop.
    - `LogicLoopTimeSpan` - time span of the previous game logic loop.
- **Renderer**
  - Now render system has methods to change window settings via the interface.
  - Window now can change its resolution independent on its size.
  - **RenderSystemInterface** - interface that provides functionality to work with the system from the game logic.
- **Core**
  - **Scene**
    - **SceneObject** - new scene object can be marked as to be deleted later via call `DeleteLater()`.
    - **BaseScene** - now scene can be marked as to be deleted later via call `DeleteLater()`.
    - **SceneMap** - now when `RemoveScene()` is called, it will mark specified scene to be deleted later and upon update, that scene will be deleted.
    - **SceneMapSystemInterface** - interface that provides functionality to work with the system from the game logic.
- **Input**
  - The system was redesigned so it will work correctly in a multithreaded app. Mostly, it works in the same way as previously, but now it do not have any static methods or data, so the whole system is stored in `EngineApp` and can be accessed via special methods.
  - New functions were introduced:
    - `AnyButtonPressed()` - checks if any button was pressed during the last update.
    - `AnyButtonHeld()` - checks if any button was held down during the last update.
    - `AnyButtonReleased()` - checks if any button was released during the last update.
    - `LastJoystickUsed()` - checks if any joystick was active during the last update and returns its id.
  - **InputSystemInterface** - interface that provides functionality to work with the system from the game logic.
- **Utility**
  - **Containers**
    - **RingBuffer** - new fixed-size buffer  that works as if it were connected end-to-end.
  - **Time**
    - **Time** - container that stores time data and provides functionality to work with it.
    - **TimeSpan** - container that stores two points of data as a time span.
  - **Random**
    - **RandomGenerator** - new utility class which provides functionality to generate pseudo-random numbers via Mersenne Twister algorithm.

## [0.0.1] - 5th April,2018

### Added
- **Renderer**
  - The base system which obtains required data from a scene map and draws everything that is supposed to be drawn. As an addition handles all user input via input system.
  - **Components**
    - **SpriteRenderComponent** - simple renderable component that provides functionality to render basic sprites.
- **Core**
  - **Components**
    - **BaseComponent** - base class for all components that can be attached to any scene object.
    - **TransformComponent** - most important component that every scene object has. It stores transform data and provide functionality to operate on that data.
    - **RenderableComponent** - base class for all renderable components that are used by the renderer.
  - **Scene**
    - **SceneObject** - core and bones to which user supposed to add components that will make an object something unique.
    - **BaseScene** - a base scene that provides the core functionality of scenes.
    - **SceneMap** - the map which stores all scenes and provides required functionality to the renderer. Handles game logic loop that should be in the separate thread.
- **Input**
  - Direct access to state of buttons/axes of keyboard/mouse/joysticks.
  - Mapping named actions.
- **Utility**
  - **Math**
    - **AtomicVector2** - new threadsafe math container to store 2d vector data.
  - **Containers**
    - **AnyCallable** - a special container which can store any possible function and execute it.
  - **Event system**
    - **Dispatcher** - container which stores AnyCallable and provides functionality to add/remove callables that can be invoked by a single function call.
    - **EventManager** - the tool which provides functionality to create/remove/invoke named events.

[0.0.1]: https://github.com/Vismar/Conure2D/releases/tag/v0.0.1-alpha

https://nn.hh.ru/applicant/resumes/view?resume=b61adf89ff0208a8890039ed1f557236457464