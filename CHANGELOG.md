# Changelog

## Plans
- **Debug info** - debug information that helps the development.
- **Editor** - ui toolchain.

## WIP

### Added
- **CMake**
  - [ ] Engine component covered.
  - [ ] Render component covered.
  - [ ] Core component covered.
  - [ ] Input component covered.
  - [*] Utility component covered.
- **Core**
  - **Scene**
    - **BaseScene** - now BaseScene stores name of itself. Also BaseScene now derived from new interface BaseSceneInterface which is used only by inner systems so user still should use BaseScene class.
  - **Components**
    - Now here is 2 kind of components:
      - **DataComponent** - should be used only to store data. Nothing more, nothing less.
      - **LogicComponent** - should be used to create logic because it provides special methods that is called by scene in update cycle.
- **Utility**
  - **LockFreeLinkedQueue** - lock-free linked queue which designed to guarantee push/pop operations to be executed simultaneously without any synchronization via mutexes or similar things.
  - **LogSystem** - system that provides functionality to log work of an engine and applications based on it.
  - **IOSystem** - system that currently provides functionality only to write data to text files.
  - **Time**
    - New functions were introduced:
      - `ToString()` - new method to convert stored time to formated string.

### Fixed
- **Overall**
  - Now code can be built on linux! Missing headers was added here and there, some other tweaks, etc.
- **Utility**
  - **AnyCallable** - now method `GetHandler()` returns value type instead of reference type. It was an issue because if you tried to access that handler if AnyCallable that stored that handler was removed (for example if any_cast was bad) then app crashes.

## [0.0.2] - 9th May,2018

### Added
- **Engine**
  - **EngineApp** - handles whole work of the engine application and all other systems. Works in 2 threads: one for render loop and the second one for the game logic.
  - **EngineInterface** - the point from which user can get any engine system and work with it in game logic. Provides access to:
    - `RenderSystemInterface` - interface to render system.
    - `SceneMapSystemInterface` - interface to scene map system.
    - `InputSystemInterface` - interface to input system.
    - `RenderLoopTimeSpan` - time span of the previous render loop.
    - `LogicLoopTimeSpan` - time span of the previous game logic loop.
- **Render**
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
    - `Set/Get JoystickThreshold()` - the way to filter the joystick move events to nullify technical imperfection.
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
- **Render**
  - The base system which obtains required data from a scene map and draws everything that is supposed to be drawn. As an addition handles all user input via input system.
  - **Components**
    - **SpriteRenderComponent** - simple renderable component that provides functionality to render basic sprites.
- **Core**
  - **Components**
    - **BaseComponent** - base class for all components that can be attached to any scene object.
    - **TransformComponent** - most important component that every scene object has. It stores transform data and provide functionality to operate on that data.
    - **RenderableComponent** - base class for all renderable components that are used by the render.
  - **Scene**
    - **SceneObject** - core and bones to which user supposed to add components that will make an object something unique.
    - **BaseScene** - a base scene that provides the core functionality of scenes.
    - **SceneMap** - the map which stores all scenes and provides required functionality to the render. Handles game logic loop that should be in the separate thread.
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
[0.0.2]: https://github.com/Vismar/Conure2D/releases/tag/v0.0.2-alpha