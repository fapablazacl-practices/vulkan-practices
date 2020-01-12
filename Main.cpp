
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


    void createInstance() {
        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "XE";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions = nullptr;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        // validation layers
        createInfo.enabledLayerCount = 0;

        if (VkResult result = vkCreateInstance(&createInfo, nullptr, &instance); result != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance. error code: " + std::to_string(result));
        }
    }


    void mainLoop() {
        while (!::glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }


    void cleanup() {
        if (instance) {
            vkDestroyInstance(instance, nullptr);
            instance = nullptr;
        }

        if (window) {
            glfwDestroyWindow(window);
            window = nullptr;
        }

        glfwTerminate();
    }

private:
    const int Width = 800, Height = 600;
    GLFWwindow *window = nullptr;
    VkInstance instance = nullptr;
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
