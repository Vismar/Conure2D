# WARNING
Currently, this project is under the overhaul, so it can`t be usable for a quit time.
- **GLFW**
  
  Instead of SFML this engine is being rewritten using GLFW for window and input management.
- **Vulkan**

  As render API was chosen Vulkan.

# Conure2D
[![Build Status](https://travis-ci.com/Vismar/Conure2D.svg?branch=master)](https://travis-ci.com/Vismar/Conure2D)

### 2D game engine
Conure2D is a pet project of a multithreaded game engine that based on SFML 2.5.0 with use of modern C++ standards.

* **Multithreaded**
  Game logic, rendering, and I/O has its own thread to work.
* **Entity component system**
  Every object on scene is represented as bare bone thing that can be modified real-time via adding or removing components of 2 types (data and logic).

### Changelog and features
Features are not yet fleshed out because project is on a really early stage of development. But you can check the whole [Changelog] in the root folder or on [Releases] page.

[Releases]: https://github.com/Vismar/Conure2D/releases
[Changelog]: https://github.com/Vismar/Conure2D/blob/master/CHANGELOG.md