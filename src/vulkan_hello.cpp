#define GLFW_INCLUDE_VULKAN
#include <include/GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
using namespace std;

//#pragma comment(lib, "vulkan-1.lib")
//#pragma comment(lib, "glfw3.lib")

int main() {
  glfwInit();
  
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  GLFWwindow* window = glfwCreateWindow(800, 600, "Hello Vulkan - ThinkReality", nullptr, nullptr);
  
  uint32_t extensionCount = 0;
  vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
  
  cout << extensionCount << " extensions supported" << endl;
  
  glm::mat4 matrix;
  glm::vec4 vec;
  auto test = matrix * vec;
  
  while(!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }
  
  glfwDestroyWindow(window);
  glfwTerminate();
  
  return 0;
}