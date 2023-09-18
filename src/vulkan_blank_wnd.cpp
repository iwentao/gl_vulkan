#define GLFW_INCLUDE_VULKAN
#include <include/GLFW/glfw3.h>

#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<const char*> instance_layers;
  vector<const char*> instance_extensions;
  vector<const char*> device_extensions;
  
  //instance_layers.push_back("VK_LAYER_LUNARG_standard_validation");
  instance_layers.push_back("VK_LAYER_KHRONOS_validation");
  instance_extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
  device_extensions.push_back(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
  
  glfwInit();
  if(GLFW_FALSE == glfwVulkanSupported()) {
    cout << "Vulkan not supported. Terminate!\n";
    glfwTerminate();
    return -1;
  }

  uint32_t instance_layer_count = 0;
  vkEnumerateInstanceLayerProperties(&instance_layer_count, nullptr);
  char** instance_layer_buffer = new char* [instance_layer_count];
  vector<VkLayerProperties> layer_bulk(instance_layer_count);
  vkEnumerateInstanceLayerProperties(&instance_layer_count, layer_bulk.data());
  
  uint32_t instance_extension_count = 0;
  const char** instance_extension_buffer = glfwGetRequiredInstanceExtensions(&instance_extension_count);
  for(uint32_t i = 0; i < instance_extension_count; ++i)
    instance_extensions.push_back(instance_extension_buffer[i]);
  
  VkApplicationInfo application_info {};
  application_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  application_info.apiVersion = VK_MAKE_VERSION(1, 0, 2);
  application_info.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
  application_info.engineVersion = VK_MAKE_VERSION(0, 0, 1);
  application_info.pApplicationName = "ThinkReality Vulkan Window";
  application_info.pEngineName = "ThinkReality Vulkan Window";

  VkInstanceCreateInfo instance_create_info {};
  instance_create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  instance_create_info.pApplicationInfo = &application_info;
  instance_create_info.enabledLayerCount = instance_layers.size();
  instance_create_info.ppEnabledLayerNames = instance_layers.data();
  instance_create_info.enabledExtensionCount = instance_extensions.size();
  instance_create_info.ppEnabledExtensionNames = instance_extensions.data();

  VkInstance instance;
  VkResult ret = vkCreateInstance(&instance_create_info, nullptr, &instance);
  if (VK_SUCCESS != ret)
  {
      cout << "ret = " << ret << endl;
      cout << "Create VULKAN instance failed. Terminate!";
      glfwTerminate();
      return -1;
  }

  uint32_t GPU_count;
  vkEnumeratePhysicalDevices(instance, &GPU_count, nullptr);
  vector<VkPhysicalDevice> GPUs(GPU_count);
  vkEnumeratePhysicalDevices(instance, &GPU_count, GPUs.data());

  uint32_t queue_family_count;
  vkGetPhysicalDeviceQueueFamilyProperties(GPUs[0], &queue_family_count, nullptr);
  vector<VkQueueFamilyProperties> family_properties(queue_family_count);
  vkGetPhysicalDeviceQueueFamilyProperties(GPUs[0], &queue_family_count, family_properties.data());

  uint32_t graphics_queue_family = UINT32_MAX;
  for(uint32_t i = 0; i < queue_family_count; ++i)
    if(family_properties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
      graphics_queue_family = i;
  
  if(graphics_queue_family == UINT32_MAX) {
    cout << "Graphics queue family not valid. Terminate!\n";
    glfwTerminate();
    return -1;
  }

  const float priorites[] { 1.0f };
  VkDeviceQueueCreateInfo queue_create_info {};
  queue_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  queue_create_info.queueCount = 1;
  queue_create_info.queueFamilyIndex = graphics_queue_family;
  queue_create_info.pQueuePriorities = priorites;

  VkDeviceCreateInfo device_create_info {};
  device_create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  device_create_info.queueCreateInfoCount = 1;
  device_create_info.pQueueCreateInfos = &queue_create_info;
  device_create_info.enabledExtensionCount = device_extensions.size();
  device_create_info.ppEnabledExtensionNames = device_extensions.data();

  VkDevice device = VK_NULL_HANDLE;
  vkCreateDevice(GPUs[0], &device_create_info, nullptr, &device);

  int width = 800;
  int height = 600;
  glfwWindowHint (GLFW_CLIENT_API, GLFW_NO_API);
  auto window = glfwCreateWindow(width, height, application_info.pApplicationName, nullptr, nullptr);
  glfwGetFramebufferSize(window, &width, &height);

  VkSurfaceKHR surface;
  ret = glfwCreateWindowSurface(instance, window, nullptr, &surface);
  if(VK_SUCCESS != ret) {
    cout << "Create Vulkan window surface failed. Terminate!\n";
    glfwTerminate();
    return -1;
  }

  while(!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }

  vkDestroySurfaceKHR(instance, surface, nullptr);
  glfwDestroyWindow(window);
  vkDestroyDevice(device, nullptr);
  vkDestroyInstance(instance, nullptr);

  glfwTerminate();

  return 0;
}