cmake_minimum_required(VERSION 3.0.2)
project(belosgl)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Set C++ Standard to version 14
set(CMAKE_CXX_STANDARD 14)

# Set OpenGL Preference for CMake 3.10 and below
set(OpenGL_GL_PREFERENCE LEGACY)

# Require SDL2 GL
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
find_package(ASSIMP REQUIRED)

add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GLEW)

# Include directories
include_directories(${SDL2_INCLUDE_DIRS})

# Set source directory
file(GLOB_RECURSE source_files src/*)
add_library(belosgl STATIC ${source_files})

# Example : solarsystem
file(GLOB_RECURSE source_files_solarsystem example/solarsystem/src/*)
add_executable(solarsystem ${source_files_solarsystem})
set_target_properties(solarsystem PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/solarsystem")
target_link_libraries (solarsystem belosgl ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${SDL2_LIBRARIES} ${GLM_LIBRARIES} ${ASSIMP_LIBRARIES})
target_include_directories(solarsystem PRIVATE src)
add_custom_target(copy_shader_files_solarsystem ${CMAKE_COMMAND} -D SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}/example/solarsystem/res -D DESTINATION_DIR=${CMAKE_CURRENT_BINARY_DIR}/solarsystem -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/CopyFile.cmake COMMENT "Copying shaders file" VERBATIM)
add_dependencies(solarsystem copy_shader_files_solarsystem)


# Example : noel
file(GLOB_RECURSE source_files_noel example/noel/src/*)
add_executable(noel ${source_files_noel})
set_target_properties(noel PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/noel")
target_link_libraries (noel belosgl ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${SDL2_LIBRARIES} ${GLM_LIBRARIES} ${ASSIMP_LIBRARIES})
target_include_directories(noel PRIVATE src)
add_custom_target(copy_shader_files_noel ${CMAKE_COMMAND} -D SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}/example/noel/res -D DESTINATION_DIR=${CMAKE_CURRENT_BINARY_DIR}/noel -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/CopyFile.cmake COMMENT "Copying shaders file" VERBATIM)
add_dependencies(noel copy_shader_files_noel)

# Example : tangram
file(GLOB_RECURSE source_files_tangram example/tangram/src/*)
add_executable(tangram ${source_files_tangram})
set_target_properties(tangram PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tangram")
target_link_libraries (tangram belosgl ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${SDL2_LIBRARIES} ${GLM_LIBRARIES} ${ASSIMP_LIBRARIES})
target_include_directories(tangram PRIVATE src)
add_custom_target(copy_shader_files_tangram ${CMAKE_COMMAND} -D SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}/example/tangram/res -D DESTINATION_DIR=${CMAKE_CURRENT_BINARY_DIR}/tangram -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/CopyFile.cmake COMMENT "Copying shaders file" VERBATIM)
add_dependencies(tangram copy_shader_files_tangram)
