cmake_minimum_required(VERSION 3.0)

project(thinkreality_vulkan_native)

INCLUDE_DIRECTORIES(C:\\VulkanSDK\\1.3.250.1\\Include\\)
link_directories(C:\\VulkanSDK\\1.3.250.1\\Lib\\)

INCLUDE_DIRECTORIES(3rdParty/glm)
INCLUDE_DIRECTORIES(3rdParty/glfw-3.3.8)
INCLUDE_DIRECTORIES(3rdParty/glfw-3.3.8/include)
link_directories(3rdParty/glfw-3.3.8/lib)

INCLUDE_DIRECTORIES(3rdParty/Mali_OpenGL_ES_Emulator-v3.0.4-2/include)
link_directories(3rdParty/Mali_OpenGL_ES_Emulator-v3.0.4-2)

#Project 1 - vulkan_hello
add_executable(vulkan_hello ./src/vulkan_hello.cpp)
target_link_libraries(vulkan_hello vulkan-1 glfw3)

#Project 2 - vulkan_blank_window
add_executable(vulkan_blank_window ./src/vulkan_blank_wnd.cpp)
target_link_libraries(vulkan_blank_window  vulkan-1 glfw3)

#Project 3 - opengles_hello
add_executable(opengles_hello ./src/opengles_hello.cpp)
target_link_libraries(opengles_hello libEGL libGLESv2 glfw3)

#Project 4 - eglExample 
add_executable(eglExample ./src/eglExample.cpp)
#set_target_properties(eglExample PROPERTIES COMPILE_FLAGS "/Zc:wchar_t")
add_definitions(-DUNICODE -D_UNICODE)
target_link_libraries(eglExample libEGL libGLESv2 glfw3)

#Project 5 - swap chain sample
if ( CMAKE_SYSTEM_NAME MATCHES "Windows" )
    set( my_std_pre "/std:" )
else()
    set( my_std_pre "-std=" )
endif()

set( basic_cxx17 "c++17" )
set( str_cxx17 "${my_std_pre}${basic_cxx17}" )

include( CheckCXXCompilerFlag )
check_cxx_compiler_flag( "${str_cxx17}" _cpp_17_flag_supported )
if ( _cpp_17_flag_supported )
    set( CMAKE_CXX_STANDARD 17 )
endif()
add_executable(swapChain ./src/swap_chain/17_swap_chain_recreation.cpp)
#add_definitions(-DNDEBUG)
target_link_libraries(swapChain vulkan-1 glfw3)

#Project 6 - descriptor set
add_executable(descSet ./src/desc_set/23_descriptor_sets.cpp)
#add_definitions(-DNDEBUG)
target_link_libraries(descSet vulkan-1 glfw3)

#Include stb, tiny_load_obj
INCLUDE_DIRECTORIES(3rdParty/stb)
INCLUDE_DIRECTORIES(3rdParty/tinyobjloader)

#Project 6 - mipmap
add_executable(mipmap ./src/mipmap/29_mipmapping.cpp)
#add_definitions(-DNDEBUG)
target_link_libraries(mipmap vulkan-1 glfw3)

#Project 7 - load obj
add_executable(loadobj ./src/load_obj/28_model_loading.cpp)
#add_definitions(-DNDEBUG)
target_link_libraries(loadobj vulkan-1 glfw3)

#Tutorials
add_executable(tutorial_00_base ./src/tutorial/00_base_code.cpp)
target_link_libraries(tutorial_00_base vulkan-1 glfw3)

add_executable(tutorial_01_instance_creation ./src/tutorial/01_instance_creation.cpp)
target_link_libraries(tutorial_01_instance_creation vulkan-1 glfw3)

add_executable(tutorial_02_validation_layers ./src/tutorial/02_validation_layers.cpp)
target_link_libraries(tutorial_02_validation_layers vulkan-1 glfw3)

add_executable(tutorial_03_physical_device_selection ./src/tutorial/03_physical_device_selection.cpp)
target_link_libraries(tutorial_03_physical_device_selection vulkan-1 glfw3)

add_executable(tutorial_04_logical_device ./src/tutorial/04_logical_device.cpp)
target_link_libraries(tutorial_04_logical_device vulkan-1 glfw3)

add_executable(tutorial_05_window_surface ./src/tutorial/05_window_surface.cpp)
target_link_libraries(tutorial_05_window_surface vulkan-1 glfw3)

add_executable(tutorial_06_swap_chain_creation ./src/tutorial/06_swap_chain_creation.cpp)
target_link_libraries(tutorial_06_swap_chain_creation vulkan-1 glfw3)

add_executable(tutorial_07_image_views ./src/tutorial/07_image_views.cpp)
target_link_libraries(tutorial_07_image_views vulkan-1 glfw3)

add_executable(tutorial_08_graphics_pipeline ./src/tutorial/08_graphics_pipeline.cpp)
target_link_libraries(tutorial_08_graphics_pipeline vulkan-1 glfw3)

add_executable(tutorial_09_shader_modules ./src/tutorial/09_shader_modules.cpp)
target_link_libraries(tutorial_09_shader_modules vulkan-1 glfw3)

add_executable(tutorial_10_fixed_functions ./src/tutorial/10_fixed_functions.cpp)
target_link_libraries(tutorial_10_fixed_functions vulkan-1 glfw3)

add_executable(tutorial_11_render_passes ./src/tutorial/11_render_passes.cpp)
target_link_libraries(tutorial_11_render_passes vulkan-1 glfw3)

add_executable(tutorial_12_graphics_pipeline_complete ./src/tutorial/12_graphics_pipeline_complete.cpp)
target_link_libraries(tutorial_12_graphics_pipeline_complete vulkan-1 glfw3)

add_executable(tutorial_13_framebuffers ./src/tutorial/13_framebuffers.cpp)
target_link_libraries(tutorial_13_framebuffers vulkan-1 glfw3)

add_executable(tutorial_14_command_buffers ./src/tutorial/14_command_buffers.cpp)
target_link_libraries(tutorial_14_command_buffers vulkan-1 glfw3)

# Hello triangle
add_executable(tutorial_15_hello_triangle ./src/tutorial/15_hello_triangle.cpp)
target_link_libraries(tutorial_15_hello_triangle vulkan-1 glfw3)

add_executable(tutorial_16_frames_in_flight ./src/tutorial/16_frames_in_flight.cpp)
target_link_libraries(tutorial_16_frames_in_flight vulkan-1 glfw3)

add_executable(tutorial_17_swap_chain_recreation ./src/tutorial/17_swap_chain_recreation.cpp)
target_link_libraries(tutorial_17_swap_chain_recreation vulkan-1 glfw3)

add_executable(tutorial_18_vertex_input ./src/tutorial/18_vertex_input.cpp)
target_link_libraries(tutorial_18_vertex_input vulkan-1 glfw3)

add_executable(tutorial_19_vertex_buffer ./src/tutorial/19_vertex_buffer.cpp)
target_link_libraries(tutorial_19_vertex_buffer vulkan-1 glfw3)

add_executable(tutorial_20_staging_buffer ./src/tutorial/20_staging_buffer.cpp)
target_link_libraries(tutorial_20_staging_buffer vulkan-1 glfw3)

add_executable(tutorial_21_index_buffer ./src/tutorial/21_index_buffer.cpp)
target_link_libraries(tutorial_21_index_buffer vulkan-1 glfw3)

add_executable(tutorial_22_descriptor_layout ./src/tutorial/22_descriptor_layout.cpp)
target_link_libraries(tutorial_22_descriptor_layout vulkan-1 glfw3)

add_executable(tutorial_23_descriptor_sets ./src/tutorial/23_descriptor_sets.cpp)
target_link_libraries(tutorial_23_descriptor_sets vulkan-1 glfw3)

add_executable(tutorial_24_texture_image ./src/tutorial/24_texture_image.cpp)
target_link_libraries(tutorial_24_texture_image vulkan-1 glfw3)

add_executable(tutorial_25_sampler ./src/tutorial/25_sampler.cpp)
target_link_libraries(tutorial_25_sampler vulkan-1 glfw3)

add_executable(tutorial_26_texture_mapping ./src/tutorial/26_texture_mapping.cpp)
target_link_libraries(tutorial_26_texture_mapping vulkan-1 glfw3)

add_executable(tutorial_27_depth_buffering ./src/tutorial/27_depth_buffering.cpp)
target_link_libraries(tutorial_27_depth_buffering vulkan-1 glfw3)

add_executable(tutorial_28_model_loading ./src/tutorial/28_model_loading.cpp)
target_link_libraries(tutorial_28_model_loading vulkan-1 glfw3)

add_executable(tutorial_29_mipmapping ./src/tutorial/29_mipmapping.cpp)
target_link_libraries(tutorial_29_mipmapping vulkan-1 glfw3)

add_executable(tutorial_30_multisampling ./src/tutorial/30_multisampling.cpp)
target_link_libraries(tutorial_30_multisampling vulkan-1 glfw3)

add_executable(tutorial_31_compute_shader ./src/tutorial/31_compute_shader.cpp)
target_link_libraries(tutorial_31_compute_shader vulkan-1 glfw3)

#===========================================================
# Try from scratch, Sep. 2023

add_executable(ch2_01_basic_framework ./src/try/ch2_01_basic_framework.cpp)
target_link_libraries(ch2_01_basic_framework vulkan-1 glfw3)

add_executable(ch2_02_basic_framework_with_glfw ./src/try/ch2_02_basic_framework_with_glfw.cpp)
target_link_libraries(ch2_02_basic_framework_with_glfw vulkan-1 glfw3)
