cmake_minimum_required(VERSION 3.9)
project(TestApp)

########################################################################################################################
# Output path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_BIN}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_LIB}")

########################################################################################################################
# Build executable
add_executable(TestApp
               main.cpp)

## Add dependencies
add_dependencies(TestApp GLFWWrapper VkWrapper GLFW-Lib Utility Tracer Render)
target_link_libraries(TestApp Utility Logger Tracer GLFW-Lib GLFWWrapper VkWrapper ${Vulkan_LIBRARY} Render)

## Prefix
set_target_properties(TestApp PROPERTIES PREFIX "")
########################################################################################################################