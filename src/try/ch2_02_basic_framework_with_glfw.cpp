/*
 * Basic framework for 'Vulkan Tutorial' book Chapter 2
 * - Drawing a triangle
 * 
 * Note:
 * C++ 17 standard
 * 
 * Wentao Sun
 * 2023-9-7
*/

#define GLFW_INCLUDE_VULKAN
#include <glfw/glfw3.h>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

class HelloTriangleApplication {
public:
    void run() {
        initVulkan();
        initWindow();
        mainLoop();
        cleanup();
    }

private:
    GLFWwindow *window = nullptr;
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;

    void initVulkan() {
    }

    void initWindow() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(WIDTH, HEIGHT, "Wentao Vulkan", nullptr, nullptr);
    }

    void mainLoop() {
        while(!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};

int main() {
    HelloTriangleApplication app;
    try {
        std::cout << "Hello, Vulkan!\n";
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}