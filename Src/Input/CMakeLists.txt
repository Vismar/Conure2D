cmake_minimum_required(VERSION 3.9)
project(Input)

#######################################################################################################################
# Output path
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/")

#######################################################################################################################
# Build static library
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

## Dependencies
add_dependencies(Input SFML)

## Prefix
set_target_properties(Input PROPERTIES PREFIX "")

## Postfix
if (CMAKE_BUILD_TYPE MATCHES Debug)
    set_target_properties(Input PROPERTIES DEBUG_POSTFIX "-d")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set_target_properties(Input PROPERTIES RELEASE_POSTFIX "-r")
endif (CMAKE_BUILD_TYPE MATCHES Debug)

#######################################################################################################################