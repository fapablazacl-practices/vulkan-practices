
project (poc-vulkan)

# GLFW
set (GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set (GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set (GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("dep/glfw")

# glm
include_directories ("dep/glm")

set (target poc-vulkan)
set (sources Main.cpp)

add_executable (${target} ${sources})
target_link_libraries (${target} glfw)
