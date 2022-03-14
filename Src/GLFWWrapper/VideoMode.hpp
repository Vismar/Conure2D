#pragma once
#include <GLFW/glfw3.h>
#include <string>

namespace C2D::GLFWWrapper
{
    /*!
     * A wrapper class for GLFWvidmode.
     */
    class VideoMode final
    {
    public:
        /*!
         * Creates a VideoMode from the provided GLFWvimode.
         *
         * \param videoMode GLFWvidmode for which wrapper will be created.
         */
        explicit VideoMode(const GLFWvidmode& videoMode);

        /*!
         * Gets width of the video mode.
         *
         * \return The width of the video mode in screen coordinated.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        [[nodiscard]]
        int32_t GetWidth() const;

        /*!
         * Gets height of the video mode.
         *
         * \return The height of the video mode in screen coordinated.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        [[nodiscard]]
        int32_t GetHeight() const;

        /*!
         * Gets bit depth of the red channel of the video mode.
         *
         * \return The bit depth of the red channel of the video mode.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        [[nodiscard]]
        int32_t GetRedBits() const;

        /*!
         * Gets bit depth of the green channel of the video mode.
         *
         * \return The bit depth of the green channel of the video mode.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        [[nodiscard]]
        int32_t GetGreenBits() const;

        /*!
         * Gets bit depth of the blue channel of the video mode.
         *
         * \return The bit depth of the blue channel of the video mode.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        [[nodiscard]]
        int32_t GetBlueBits() const;

        /*!
         * Get refresh rate of the video mode.
         *
         * \return The refresh rate, in Hz, of the video mode.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        [[nodiscard]]
        int32_t GetRefreshRate() const;

        [[nodiscard]]
        std::string AsString() const;

        /*!
         * Compares this video mode and specified.
         *
         * \param right A video mode to compare with.
         *
         * \return True if video modes are equal to each other. Otherwise - false.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        bool operator==(const VideoMode& right) const;

    private:
        /*! A reference to the GLFWvidmode. */
        const GLFWvidmode& _videoMode;
    };
}