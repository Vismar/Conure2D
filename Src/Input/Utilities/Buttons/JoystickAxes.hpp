#pragma once
#include <string>

namespace C2D
{
    /*!
     * \brief Special redefinition of joystick axes from SFML to determine them as enum class.
     */
    enum class JoystickAxis
    {
        X = 0, /*!< The X axis. */
        Y,     /*!< The Y axis. */
        Z,     /*!< The Z axis. */
        R,     /*!< The R axis. */
        U,     /*!< The U axis. */
        V,     /*!< The V axis. */
        PovX,  /*!< The PovX axis. */
        PovY   /*!< The PovY axis. */
    };
    
    /*! Names for joystick axes. */
    static std::string JoystickAxisName[] =
    {
        "X",
        "Y",
        "Z",
        "R",
        "U",
        "V",
        "PovX",
        "PovY"
    };
}