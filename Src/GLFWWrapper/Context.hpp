#pragma once

namespace GLFWWrapper
{
    /*!
     * A wrapper class for GLFW context.
     */
    class Context final
    {
    public:
        /*!
         * Creates and initializes the GLFW context.
         *
         * \attention Should be used only once.
         * \attention If initialization of the GLFW context failed, this function will fail with assertion.
         */
        Context();

        /*!
         * Destroys the GLFW context.
         */
        ~Context();
    };
}