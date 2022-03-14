#include <Render/RenderSystem.hpp>

#include <GLFWWrapper/Window.hpp>
#include <GLFWWrapper/Monitor.hpp>
#include <GLFWWrapper/Context.hpp>

#include <Render/TriangleRenderer.hpp>
//#include <VkWrapper/Application.hpp>

#include <thread>
#include <chrono>

#include <Logger/Logger.hpp>

int main()
{
    Logger::ChangeLevel(Logger::Level::Info);

    C2D::GLFWWrapper::Context glfwContext;

    C2D::GLFWWrapper::Monitor primMonitor(glfwGetPrimaryMonitor());
    primMonitor.SelectVideoMode(primMonitor.GetVideoModes().size() - 1);

    std::unique_ptr<C2D::GLFWWrapper::Window> window = std::make_unique<C2D::GLFWWrapper::Window>();
    window->Create();
    //GLFWWrapper::Window window;
    //window.Create();//.SetTitle("Conure2D").SetSize(800, 600);

    //C2D::VkWrapper::ApplicationConfiguration configuration =
    //{
    //    window,
    //    "",
    //    {
    //        "./shader",
    //    }
    //};
    //C2D::VkWrapper::Application application(configuration);

    std::vector<std::string> shaders = {"./shader"};
    std::unique_ptr<C2D::RenderSystem> renderSystem = std::make_unique<C2D::RenderSystem>(std::ref(window),
                                                                                          shaders);

    std::unique_ptr<C2D::TriangleRenderer> triangleRenderer =
            std::make_unique<C2D::TriangleRenderer>(renderSystem->CreateRenderMediator("./shader"));

    while (window->IsNotClosed())
    {
        glfwPollEvents();
        renderSystem->DrawFrame();
        //application.DrawFrame();
    }

    renderSystem->ResetCommandPool();
    triangleRenderer.reset();
    renderSystem.reset();

    return 0;
}