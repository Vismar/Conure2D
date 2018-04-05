# Changelog

## Unreleased
- **Input system**
  - The system should be redesigned so it will work correctly in a multithreaded app.
- **Time**
  - Render loop time
  - Game logic loop time

## [0.0.1] - 5th April,2018

### Added
- **Utility**
  - **Math**
    - **AtomicVector2** - new threadsafe math container to store 2d vector data.
  - **Containers**
    - **AnyCallable** - a special container which can store any possible function and execute it.
  - **Event system**
    - **Dispatcher** - container which stores AnyCallable and provides functionality to add/remove callables that can be invoked by a single function call.
    - **EventManager** - the tool which provides functionality to create/remove/invoke named events.
- **Input system**
  - Direct access to state of buttons/axes of keyboard/mouse/joysticks.
  - Mapping named actions.
- **Core**
  - **Components**
    - **BaseComponent** - base class for all components that can be attached to any scene object.
    - **TransformComponent** - most important component that every scene object has. It stores transform data and provide functionality to operate on that data.
    - **RenderableComponent** - base class for all renderable components that are used by the renderer.
  - **Scene**
    - **SceneObject** - core and bones to which user supposed to add components that will make an object something unique.
    - **BaseScene** - a base scene that provides the core functionality of scenes.
    - **SceneMap** - the map which stores all scenes and provides required functionality to the renderer. Handles game logic loop that should be in the separate thread.
- **Renderer**
  - The base system which obtains required data from a scene map and draws everything that is supposed to be drawn. As an addition handles all user input via input system.
  - **Components**
    - **SpriteRenderComponent** - simple renderable component that provides functionality to render basic sprites.