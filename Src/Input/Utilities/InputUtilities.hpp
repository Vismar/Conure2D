#pragma once

namespace Input
{
    /*!
     * \brief Simple enumeration to describe key state.
     */
    enum class KeyState
    {
        NotTouched, /*!< Key was not touched during the update time. */
        Pressed,    /*!< Key was pressed during the update time. */
        HeldDown,   /*!< Key was held down during the update time. */
        Released    /*!< Key was released during the update time. */
    };
}