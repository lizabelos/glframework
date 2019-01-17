cmake_minimum_required(VERSION 3.0.2)
project(Solar_System)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Set C++ Standard to version 14
set (CMAKE_CXX_STANDARD 14)

# Require SDL2 GL
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(ASSIMP REQUIRED)

# Include directories
include_directories(${SDL2_INCLUDE_DIRS})

# Set source directory
file(GLOB_RECURSE source_files src/*)

# Ressources
add_custom_target(copy_shader_files ${CMAKE_COMMAND} -D SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}/res -D DESTINATION_DIR=${CMAKE_CURRENT_BINARY_DIR} -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/CopyFile.cmake COMMENT "Copying shaders file" VERBATIM)

# Executable
add_executable(solarsystem ${source_files})
target_link_libraries (solarsystem ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${SDL2_LIBRARIES} ${GLM_LIBRARIES} ${ASSIMP_LIBRARIES})
add_dependencies(solarsystem copy_shader_files)