#pragma once
#include <string>

namespace Input
{
    /*!
     * \brief Special redefinition of joystick buttons from SFML to determine them as enum class.
     */
    enum class JoystickButton
    {
        Button0 = 0, /*!< The button #0. */
        Button1,     /*!< The button #1. */
        Button2,     /*!< The button #2. */
        Button3,     /*!< The button #3. */
        Button4,     /*!< The button #4. */
        Button5,     /*!< The button #5. */
        Button6,     /*!< The button #6. */
        Button7,     /*!< The button #7. */
        Button8,     /*!< The button #8. */
        Button9,     /*!< The button #9. */
        Button10,    /*!< The button #10. */
        Button11,    /*!< The button #11. */
        Button12,    /*!< The button #12. */
        Button13,    /*!< The button #13. */
        Button14,    /*!< The button #14. */
        Button15,    /*!< The button #15. */
        Button16,    /*!< The button #16. */
        Button17,    /*!< The button #17. */
        Button18,    /*!< The button #18. */
        Button19,    /*!< The button #19. */
        Button20,    /*!< The button #20. */
        Button21,    /*!< The button #21. */
        Button22,    /*!< The button #22. */
        Button23,    /*!< The button #23. */
        Button24,    /*!< The button #24. */
        Button25,    /*!< The button #25. */
        Button26,    /*!< The button #26. */
        Button27,    /*!< The button #27. */
        Button28,    /*!< The button #28. */
        Button29,    /*!< The button #29. */
        Button30,    /*!< The button #30. */
        Button31     /*!< The button #31. */
    };

    /*! Names for joystick buttons. */
    static std::string JoystickButtonName[] =
    {
        "Button0",
        "Button1",
        "Button2",
        "Button3",
        "Button4",
        "Button5",
        "Button6",
        "Button7",
        "Button8",
        "Button9",
        "Button10",
        "Button11",
        "Button12",
        "Button13",
        "Button14",
        "Button15",
        "Button16",
        "Button17",
        "Button18",
        "Button19",
        "Button20",
        "Button21",
        "Button22",
        "Button23",
        "Button24",
        "Button25",
        "Button26",
        "Button27",
        "Button28",
        "Button29",
        "Button30",
        "Button31"
    };
}