
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include <stdexcept>

class HelloTriangleApplication {
public:
    void run() {
        init();
        mainLoop();
        cleanup(); 
    }

private:
    void init() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        window = glfwCreateWindow(Width, Height, "Vulkan Window", nullptr, nullptr);

        std::uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::cout << extensionCount << " extensions supported" << std::endl;
    }


    void mainLoop() {
        while (!::glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }


    void cleanup() {
        if (window) {
            glfwDestroyWindow(window);
        }

        glfwTerminate();
    }

private:
    const int Width = 800, Height = 600;

    GLFWwindow *window = nullptr;
};


int main(int argc, char **argv) {
    HelloTriangleApplication app;

    try {
        app.run();
    } catch (const std::exception &exp) {
        std::cerr << exp.what() << std::endl;

        return EXIT_FAILURE;       
    }

    return EXIT_SUCCESS;
}
