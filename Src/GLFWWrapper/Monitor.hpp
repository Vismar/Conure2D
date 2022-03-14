#pragma once
#include <string_view>
#include <vector>
#include <tuple>
#include <GLFW/glfw3.h>
#include <GLFWWrapper/VideoMode.hpp>

namespace C2D::GLFWWrapper
{
    /*!
     * A wrapper class for the GLFWmonitor.
     */
    class Monitor final
    {
    public:
        /*!
         * Creates a wrapper around the provided GLFWmonitor.
         *
         * \param monitor Raw pointer to the GLFWmonitor for which a wrapper will be created.
         *
         * \attention If provided pointer if nullptr then this function will fail with assertion.
         */
        explicit Monitor(GLFWmonitor* monitor);

        /*!
         * Gets name of the monitor.
         *
         * \return The name of the monitor.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        [[nodiscard]]
        std::string_view GetName() const;

        /*!
         * Get the list of the video modes supported by the monitor.
         *
         * \return A list of the video modes supported by the monitor.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        [[nodiscard]]
        const std::vector<VideoMode>& GetVideoModes() const;

        /*!
         * Selects the specified video mode.
         *
         * \param videoModeNumber Index of the video mode within the list of the supported by monitor video modes.
         *
         * \attention Index should be less the number of supported video modes by the monitor.
         *            Otherwise this function will fail with assertion.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        void SelectVideoMode(size_t videoModeNumber);

        /*!
         * Gets the selected video mode.
         *
         * \return Currently selected video mode.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        [[nodiscard]]
        const VideoMode& GetSelectedVideoMode() const;

        /*!
         * Get the size, in millimetres, of the display area of the monitor.
         *
         * \return A tuple of two values (width and height).
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        [[nodiscard]]
        std::tuple<int32_t, int32_t> GetContentScale() const;

        /*!
         * Get a raw pointer to the monitor (GLFWmonitor*).
         *
         * \return A raw pointer to the GLFWmonitor.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        [[nodiscard]]
        GLFWmonitor* GetHandle() const;

    private:
        /*! Selected video mode. */
        size_t _selectedVideoMode = 0;
        /*! List of supported video modes by the monitor. */
        std::vector<VideoMode> _videoModes;
        /*! A raw pointer to the GLFWmonitor. */
        GLFWmonitor* _monitor = nullptr;
    };
}