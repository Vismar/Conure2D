#pragma once
#include <string>

namespace Input
{
    /*!
    * \brief Special redefinition of keyboard buttons from SFML to determine them as enum class.
    */
    enum class KeyboardButton
    {
        A = 0,     /*!< The A button. */
        B,         /*!< The B button. */
        C,         /*!< The C button. */
        D,         /*!< The D button. */
        E,         /*!< The E button. */
        F,         /*!< The F button. */
        G,         /*!< The G button. */
        H,         /*!< The H button. */
        I,         /*!< The I button. */
        J,         /*!< The J button. */
        K,         /*!< The K button. */
        L,         /*!< The L button. */
        M,         /*!< The M button. */
        N,         /*!< The N button. */
        O,         /*!< The O button. */
        P,         /*!< The P button. */
        Q,         /*!< The Q button. */
        R,         /*!< The R button. */
        S,         /*!< The S button. */
        T,         /*!< The T button. */
        U,         /*!< The U button. */
        V,         /*!< The V button. */
        W,         /*!< The W button. */
        X,         /*!< The X button. */
        Y,         /*!< The Y button. */
        Z,         /*!< The Z button. */
        Num0,      /*!< The 0 button. */
        Num1,      /*!< The 1 button. */
        Num2,      /*!< The 2 button. */
        Num3,      /*!< The 3 button. */
        Num4,      /*!< The 4 button. */
        Num5,      /*!< The 5 button. */
        Num6,      /*!< The 6 button. */
        Num7,      /*!< The 7 button. */
        Num8,      /*!< The 8 button. */
        Num9,      /*!< The 9 button. */
        Escape,    /*!< The Escape button. */
        LControl,  /*!< The left Control button. */
        LShift,    /*!< The left Shift button. */
        LAlt,      /*!< The left Alt button. */
        LSystem,   /*!< The left OS specific button: window (Windows and Linux), apple (MacOS X), ... */
        RControl,  /*!< The right Control button. */
        RShift,    /*!< The right Shift button. */
        RAlt,      /*!< The right Alt button. */
        RSystem,   /*!< The right OS specific button: window (Windows and Linux), apple (MacOS X), ... */
        Menu,      /*!< The Menu button. */
        LBracket,  /*!< The [ button. */
        RBracket,  /*!< The ] button. */
        Semicolon, /*!< The ; button. */
        Comma,     /*!< The , button. */
        Period,    /*!< The . button. */
        Quote,     /*!< The ' button. */
        Slash,     /*!< The / button. */
        Backslash, /*!< The \ button. */
        Tilde,     /*!< The ~ button. */
        Equal,     /*!< The = button. */
        Hyphen,    /*!< The - button. */
        Space,     /*!< The Space button. */
        Enter,     /*!< The Enter/Return button. */
        Backspace, /*!< The Backspace button. */
        Tab,       /*!< The Tabulation button. */
        PageUp,    /*!< The Page up button. */
        PageDown,  /*!< The Page down button. */
        End,       /*!< The End button. */
        Home,      /*!< The Home button. */
        Insert,    /*!< The Insert button. */
        Delete,    /*!< The Delete button. */
        Add,       /*!< The + button. */
        Subtract,  /*!< The - button. */
        Multiply,  /*!< The * button. */
        Divide,    /*!< The / button. */
        Left,      /*!< Left arrow. */
        Right,     /*!< Right arrow. */
        Up,        /*!< Up arrow. */
        Down,      /*!< Down arrow. */
        Numpad0,   /*!< The numpad 0 button. */
        Numpad1,   /*!< The numpad 1 button. */
        Numpad2,   /*!< The numpad 2 button. */
        Numpad3,   /*!< The numpad 3 button. */
        Numpad4,   /*!< The numpad 4 button. */
        Numpad5,   /*!< The numpad 5 button. */
        Numpad6,   /*!< The numpad 6 button. */
        Numpad7,   /*!< The numpad 7 button. */
        Numpad8,   /*!< The numpad 8 button. */
        Numpad9,   /*!< The numpad 9 button. */
        F1,        /*!< The F1 button. */
        F2,        /*!< The F2 button. */
        F3,        /*!< The F3 button. */
        F4,        /*!< The F4 button. */
        F5,        /*!< The F5 button. */
        F6,        /*!< The F6 button. */
        F7,        /*!< The F7 button. */
        F8,        /*!< The F8 button. */
        F9,        /*!< The F9 button. */
        F10,       /*!< The F10 button. */
        F11,       /*!< The F11 button. */
        F12,       /*!< The F12 button. */
        F13,       /*!< The F13 button. */
        F14,       /*!< The F14 button. */
        F15,       /*!< The F15 button. */
        Pause      /*!< The Pause button. */
    };

    /*! Names for keyboard buttons. */
    static std::string KeyboardButtonName[] =
    {
        "A",
        "B",
        "C",
        "D",
        "E",
        "F",
        "G",
        "H",
        "I",
        "J",
        "K",
        "L",
        "M",
        "N",
        "O",
        "P",
        "Q",
        "R",
        "S",
        "T",
        "U",
        "V",
        "W",
        "X",
        "Y",
        "Z",
        "Num0",
        "Num1",
        "Num2",
        "Num3",
        "Num4",
        "Num5",
        "Num6",
        "Num7",
        "Num8",
        "Num9",
        "Escape",
        "LControl",
        "LShift",
        "LAlt",
        "LSystem",
        "RControl",
        "RShift",
        "RAlt",
        "RSystem",
        "Menu",
        "LBracket",
        "RBracket",
        "Semicolon",
        "Comma",
        "Period",
        "Quote",
        "Slash",
        "Backslash",
        "Tilde",
        "Equal",
        "Hyphen",
        "Space",
        "Enter",
        "Backspace",
        "Tab",
        "PageUp",
        "PageDown",
        "End",
        "Home",
        "Insert",
        "Delete",
        "Add",
        "Subtract",
        "Multiply",
        "Divide",
        "Left",
        "Right",
        "Up",
        "Down",
        "Numpad0",
        "Numpad1",
        "Numpad2",
        "Numpad3",
        "Numpad4",
        "Numpad5",
        "Numpad6",
        "Numpad7",
        "Numpad8",
        "Numpad9",
        "F1",
        "F2",
        "F3",
        "F4",
        "F5",
        "F6",
        "F7",
        "F8",
        "F9",
        "F10",
        "F11",
        "F12",
        "F13",
        "F14",
        "F15",
        "Pause"
    };
}