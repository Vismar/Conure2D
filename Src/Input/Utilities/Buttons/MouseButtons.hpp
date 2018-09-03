#pragma once
#include <string>

namespace C2D
{
    /*!
     * \brief Special redefinition of mouse buttons from SFML to determine them as enum class.
     */
    enum class MouseButton
    {
        Left,     /*!< The left mouse button. */
        Right,    /*!< The right mouse button. */
        Middle,   /*!< The middle (wheel) mouse button. */
        XButton1, /*!< The first extra mouse button. */
        XButton2  /*!< The second extra mouse button. */
    };

    /*! Names for mouse buttons. */
    static std::string MouseButtonName[] =
    {
        "Left",
        "Right",
        "Middle",
        "XButton1",
        "XButton2"
    };
}