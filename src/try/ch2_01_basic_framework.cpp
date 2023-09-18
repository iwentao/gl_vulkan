/*
 * Basic framework for 'Vulkan Tutorial' book Chapter 2
 * - Drawing a triangle
 * 
 * Note:
 * C++ 17 standard
 * 
 * Wentao Sun
 * 2023-9-1
*/

#include <vulkan/vulkan.h>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

class HelloTriangleApplication {
public:
    void run() {
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    void initVulkan() {
    }

    void mainLoop() {
    }

    void cleanup() {
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