cmake_minimum_required(VERSION 3.10)
project(Input)

set(CMAKE_CXX_STANDARD 17)
set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${dir}../../../Lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${dir}../../../Lib")

include_directories(../)

add_library(Input
            Devices/JoystickDevice.cpp
            Devices/JoystickDevice.hpp
            Devices/JoystickDeviceInterface.hpp
            Devices/KeyboardDevice.cpp
            Devices/KeyboardDevice.hpp
            Devices/MouseDevice.cpp
            Devices/MouseDevice.hpp
            Devices/MouseDeviceInterface.hpp
            Utilities/Buttons/JoystickAxes.hpp
            Utilities/Buttons/JoystickButtons.hpp
            Utilities/Buttons/KeyboardButtons.hpp
            Utilities/Buttons/MouseButtons.hpp
            Utilities/MappedInput/InputAction.cpp
            Utilities/MappedInput/InputAction.hpp
            Utilities/MappedInput/InputAxis.cpp
            Utilities/MappedInput/InputAxis.hpp
            Utilities/MappedInput/InputMap.cpp
            Utilities/MappedInput/InputMap.hpp
            Utilities/MappedInput/InputMapInterface.hpp
            Utilities/ButtonStateHandler.cpp
            Utilities/ButtonStateHandler.hpp
            InputSystem.cpp
            InputSystem.hpp
            InputSystemHandlerInterface.hpp
            InputSystemInterface.hpp)
