#pragma once
#include <tuple>
#include <string_view>
#include <functional>
#include <GLFW/glfw3.h>

namespace C2D::GLFWWrapper
{
    class Monitor;

    /*!
     * A wrapper class for GLFWWindow.
     */
    class Window final
    {
    public:
        /*!
         * Simplification of the type that is used as callback for frame buffer resize event.
         */
        using WindowFramebufferResizedCallback = std::function<void()>;

        /*!
         * State of the window.
         */
        enum class State
        {
            Destroyed,  /*!< State of the window when it is not created. */
            Normal,     /*!< State of the window when it is normal (not hidden, not minimized, not fullscreen, with borders). */
            Minimized,  /*!< State of the window when it is minimized. */
            Maximized,  /*!< State of the window when it is maximized (fullscreen with borders). */
            Hidden,     /*!< State of the window when it is hidden. */
            Fullscreen, /*!< State of the window when it is fullscreen. */
            Borderless  /*!< State of the window when it is borderless. */
        };

        /*!
         * Destructor. Calls Window::Destroy().
         */
        ~Window();

        /*!
         * Creates a new window.
         *
         * \param width Width of the window that will be created.
         * \param height Height of the window that will be created.
         * \param title Title of the window that will be created.
         *
         * \return A reference to the created window.
         *
         * \attention If window is already created then function will fail with assertion.
         * \attention If window was not created in the end of the function then it will fail with assertion.
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        Window& Create(int width = 800, int height = 600, std::string_view title = "Conure2D");

        /*!
         * Destroys the window and frees its memory.
         *
         * \attention If window is already destroyed then function will fail with the assertion.
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        void Destroy();

        /*!
         * Checks if the window is not closed.
         *
         * \return True if window exists and was not closed. Otherwise - false.
         *
         * \threadSafety Thread-safe. Can be called from any thread.
         */
        [[nodiscard]]
        bool IsNotClosed() const;

        /*!
         * Sets title to the window that will be displayed.
         *
         * \param title A string that will be used as a title.
         *
         * \return A referencer to the window.
         *
         * \attention If window is not created then function will fail with assertion.
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        Window& SetTitle(std::string_view title);

        /*!
         * Checks if the window is resizable.
         *
         * \return True if the window is resizable. Otherwise - false.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        [[nodiscard]]
        bool IsResizable() const;

        /*!
         * Makes the window resizable (or not).
         *
         * \param resizable Flag that defines resizability of the window.
         *
         * \return A reference to the window.
         *
         * \attention You can't change this property without recreating the window.
         *            If you want to change this property then destroy the window, set property to your desired value,
         *            and create it again.
         *            If window already created then this function will fail with assertion.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        Window& SetResizable(bool resizable);

        /*!
         * Checks if the window is decorated (has a border, a close widget, etc.).
         *
         * \return True if the window is decorated. Otherwise - false.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        [[nodiscard]]
        bool IsDecorated() const;

        /*!
         * Makes the window decorated (or not).
         *
         * \param decorated Flag that defines if the window is decorated or not.
         *
         * \return A reference to the window.
         *
         * \attention You can't change this property without recreating the window.
         *            If you want to change this property then destroy the window, set property to your desired value,
         *            and create it again.
         *            If window already created then this function will fail with assertion.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        Window& SetDecorated(bool decorated);

        /*!
         * Gets the size of the window.
         *
         * \return A tuple of two values (width and height).
         *
         * \attention If window is not created then function will fail with assertion.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        [[nodiscard]]
        std::tuple<int32_t, int32_t> GetSize() const;

        /*!
         * Sets the size of the window
         *
         * \param width The new width of the window.
         * \param height The new height of the window.
         *
         * \return A reference to the window.
         *
         * \attention If window is not created then function will fail with assertion.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        Window& SetSize(int32_t width, int32_t height);

        /*!
         * Sets the size limits for the window.
         *
         * \param mindWidth The minimal width of the window.
         * \param minHeight The minimal height of the window.
         * \param maxWidth The maximum width of the window.
         * \param maxHeight The maximum height of the window.
         *
         * \return A reference to the window.
         *
         * \attention If window is not created then function will fail with assertion.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        Window& SetSizeLimits(int32_t mindWidth, int32_t minHeight, int32_t maxWidth, int32_t maxHeight);

        /*!
         * Sets the aspect ration for the window.
         *
         * \param numer The numerator of the desired aspect ratio.
         * \param denom The denominator of the desired aspect ratio.
         *
         * \return A reference to the window.
         *
         * \attention If window is not created then function will fail with assertion.
         * \attention Calling this method with default values disables aspect ratio limit.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        Window& SetAspectRatio(int32_t numer = GLFW_DONT_CARE, int32_t denom = GLFW_DONT_CARE);

        /*!
         * Gets the position of the window.
         *
         * \return A tuple of two values (x and y coordinates).
         *
         * \attention If window is not created then function will fail with assertion.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        [[nodiscard]]
        std::tuple<int32_t, int32_t> GetPosition() const;

        /*!
         * Sets a new position for the window.
         *
         * \param xPos X coordinate of a new position.
         * \param yPos Y coordinate of a new position
         *
         * \return A reference to the window.
         *
         * \attention If window is not created then function will fail with assertion.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        Window& SetPosition(int32_t xPos, int32_t yPos);

        /*!
         * Gets the opacity of the window.
         *
         * \return The opacity value between 0.0f and 1.0f where 0 is fully transparent and 1 is fully opaque.
         *
         * \attention If window is not created then function will fail with assertion.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        [[nodiscard]]
        float GetOpacity() const;

        /*!
         * Sets the opacity of the window.
         *
         * \param opacity A new opacity value for the window.
         *
         * \return A reference to the window.
         *
         * \attention If window is not created then function will fail with assertion.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        Window& SetOpacity(float opacity);

        /*!
         * Gets the frame buffer size of the window in pixels.
         *
         * \return A tuple of two values (width and height).
         *
         * \attention If window is not created then function will fail with assertion.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        [[nodiscard]]
        std::tuple<int32_t, int32_t> GetFrameBufferSize() const;

        /*!
         * Gets the content scale of the window.
         * The content scale is the ratio between the current DPI and the platform's default DPI.
         *
         * \return A tuple of two values (x and y scale).
         *
         * \attention If window is not created then function will fail with assertion.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        [[nodiscard]]
        std::tuple<float, float> GetContentScale() const;

        /*!
         * Gets the coordinates of each corner of the window.
         *
         * \return A tuple of four values (left, top, right, bottom).
         *
         * \attention If window is not created then function will fail with assertion.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        [[nodiscard]]
        std::tuple<int32_t, int32_t, int32_t, int32_t> GetFrameCoordinates() const;

        /*!
         * Request the user's attention on the window.
         *
         * \return A reference to the window.
         *
         * \attention If window is not created then function will fail with assertion.
         *
         * \warning Not thread-safe. Must be called only from the main thread.
         */
        Window& RequestAttention();

        /*!
         * Minimizes the window. If window is a fullscreen window, then this function does nothing.
         *
         * \return A reference to the window.
         *
         * \attention If window is not created then function will fail with assertion.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        Window& Minimize();

        /*!
         * Restores the window if it was minimized or maximized.
         * If the window is already restored, then this function does nothing.
         * If the window is a full screen window, the resolution chosen for
         * the window is restored on the selected monitor.
         *
         * \return A reference to the window.
         *
         * \attention If window is not created then function will fail with assertion.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        Window& Restore();

        /*!
         * Maximizes the window. If the window is a fullscreen window, then this function does nothing.
         *
         * \return A reference to the window.
         *
         * \attention If window is not created then function will fail with assertion.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        Window& Maximize();

        /*!
         * Hides the window. If the window is a fullscreen window, then this function does nothing.
         *
         * \return A reference to the window.
         *
         * \attention If window is not created then function will fail with assertion.
         *
         * \warning Not thread-safe. Must be called only from the main thread.
         */
        Window& Hide();

        /*!
         * Shows the window. If window is not hidden, then this function does nothing.
         *
         * \return A reference to the window.
         *
         * \attention If window is not created then function will fail with assertion.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        Window& Show();

        /*!
         * Focuses the window. If the window is hidden or minimized, then this function does nothing.
         *
         * \return A reference to the window.
         *
         * \attention If window is not created then function will fail with assertion.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        Window& Focus();

        /*!
         * Checks if the window is focused.
         *
         * \return True if the window is focused. Otherwise - false.
         *
         * \attention If window is not created then function will fail with assertion.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        [[nodiscard]]
        bool IsFocused() const;

        /*!
         * Makes the window a fullscreen window on the specified monitor.
         *
         * \param monitor A monitor on which the window should be a fullscreen window.
         *
         * \return A reference to the window.
         *
         * \attention If window is not created then function will fail with assertion.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        Window& SetFullScreenOnMonitor(const Monitor& monitor);

        /*!
         * Makes the window windowed.
         * If the window is a fullscreen window or it is borderless then this function does nothing.
         *
         * \return A reference to the window.
         *
         * \attention If window is not created then function will fail with assertion.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        Window& SetWindowed();

        /*!
         * Recreates the window as a borderless window on the specified monitor.
         *
         * \param monitor
         *
         * \return A reference to the window.
         *
         * \attention If window was not created in the end of the function then it will fail with assertion.
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        Window& SetBorderlessWindowedOnMonitor(const Monitor& monitor);

        /*!
         *
         * \return
         *
         * \threadSafety Not thread-safe. Must be called only from the main thread.
         */
        [[nodiscard]]
        State GetState() const;

        /*!
         * Gets the current state of the window.
         *
         * \return The current state of the window.
         */
        [[nodiscard]]
        GLFWwindow* GetHandle() const;

        /*!
         * Adds a callback that will be called upon resize of the frame buffer.
         *
         * \param callback A function that will added as a callback.
         */
        void AddFramebufferResizedCallback(WindowFramebufferResizedCallback callback);

    private:
        /*!
         * A callback function that is assigned to GLFW upon creation of the window.
         * Calls \ref OnFramebufferResized().
         *
         * \param window Raw pointer to the GLFWWindow.
         * \param width New width of the window.
         * \param height New height of the window.
         */
        static void OnFramebufferResizeCallback(GLFWwindow* window, int width, int height);

        /*!
         * calls every callback in the \ref _framebufferResizedCallbacks list.
         *
         * \param width New width of the window.
         * \param height New height of the window.
         */
        void OnFramebufferResized(int width, int height) const;

        /*! List of callbacks. Each one of them is called when frame buffer resized even is received. */
        std::vector<WindowFramebufferResizedCallback> _framebufferResizedCallbacks;

        /*! Current state of the window. */
        State _state = State::Destroyed;
        /*! Simple flags that shows if the window is resizable or not. */
        int32_t _resizable = GLFW_TRUE;
        /*! Simple flags that shows if the window is decorated or not. */
        int32_t _decorated = GLFW_TRUE;
        /*! Raw pointer to the GLFWWindow. */
        GLFWwindow* _window = nullptr;
    };
}