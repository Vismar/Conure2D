cmake_minimum_required(VERSION 3.9)
project(Input)

set(Src ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../Lib/")

include_directories(${Src}/)

add_library(Input
            ${Src}/Input/Devices/JoystickDevice.cpp
            ${Src}/Input/Devices/JoystickDevice.hpp
            ${Src}/Input/Devices/JoystickDeviceInterface.hpp
            ${Src}/Input/Devices/KeyboardDevice.cpp
            ${Src}/Input/Devices/KeyboardDevice.hpp
            ${Src}/Input/Devices/MouseDevice.cpp
            ${Src}/Input/Devices/MouseDevice.hpp
            ${Src}/Input/Devices/MouseDeviceInterface.hpp
            ${Src}/Input/Utilities/Buttons/JoystickAxes.hpp
            ${Src}/Input/Utilities/Buttons/JoystickButtons.hpp
            ${Src}/Input/Utilities/Buttons/KeyboardButtons.hpp
            ${Src}/Input/Utilities/Buttons/MouseButtons.hpp
            ${Src}/Input/Utilities/MappedInput/InputAction.cpp
            ${Src}/Input/Utilities/MappedInput/InputAction.hpp
            ${Src}/Input/Utilities/MappedInput/InputAxis.cpp
            ${Src}/Input/Utilities/MappedInput/InputAxis.hpp
            ${Src}/Input/Utilities/MappedInput/InputMap.cpp
            ${Src}/Input/Utilities/MappedInput/InputMap.hpp
            ${Src}/Input/Utilities/MappedInput/InputMapInterface.hpp
            ${Src}/Input/Utilities/ButtonStateHandler.cpp
            ${Src}/Input/Utilities/ButtonStateHandler.hpp
            ${Src}/Input/InputSystem.cpp
            ${Src}/Input/InputSystem.hpp
            ${Src}/Input/InputSystemHandlerInterface.hpp
            ${Src}/Input/InputSystemInterface.hpp)

# Prefix
set_target_properties(Input PROPERTIES PREFIX "")
# Postfix
if (CMAKE_BUILD_TYPE MATCHES Debug)
    set_target_properties(Input PROPERTIES DEBUG_POSTFIX "-d")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    set_target_properties(Input PROPERTIES RELEASE_POSTFIX "-r")
endif (CMAKE_BUILD_TYPE MATCHES Debug)