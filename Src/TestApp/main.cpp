#include <GLFWWrapper/Window.hpp>
#include <GLFWWrapper/Monitor.hpp>
#include <GLFWWrapper/Context.hpp>

#include <VkWrapper/Application.hpp>
#include <Logger/Logger.hpp>

int main()
{
    Logger::ChangeLevel(Logger::Level::Info);

    GLFWWrapper::Context glfwContext;

    GLFWWrapper::Monitor primMonitor(glfwGetPrimaryMonitor());
    primMonitor.SelectVideoMode(primMonitor.GetVideoModes().size() - 1);

    GLFWWrapper::Window window;
    window.Create();//.SetTitle("Conure2D").SetSize(800, 600);

    VkWrapper::ApplicationConfiguration configuration =
    {
        window,
        "",
        {
            "./shader",
        }
    };
    VkWrapper::Application application(configuration);

    while (window.IsNotClosed())
    {
        glfwPollEvents();
        application.DrawFrame();
    }

    return 0;
}