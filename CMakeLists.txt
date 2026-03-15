cmake_minimum_required(VERSION 3.10)

project(BrickBox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#####################################
# OpenGL stuff
#####################################
find_package(glfw3 3.4 REQUIRED)
cmake_pkg_config(IMPORT epoxy)

add_executable(BrickBox src/main.cpp
        src/renderer/glfw/Window.cpp
        src/renderer/glfw/GLFWLifecycle.cpp
        src/renderer/InitialRenderLoop.cpp
        src/renderer/AbstractRenderer.cpp
        src/renderer/opengl/Resource.cpp
        src/renderer/opengl/Shader.cpp
        src/renderer/opengl/Program.cpp
        src/renderer/opengl/Buffer.cpp
        src/renderer/opengl/VertexArray.cpp
        src/renderer/opengl/programs/TestProgram.h
        src/renderer/opengl/Texture.cpp
        src/renderer/AtlasStitcher.cpp
        include/nlohmann/json.hpp
        src/Filesystem.cpp
        src/renderer/assets/BlockModel.cpp
        src/assets/STBImage.cpp
        src/renderer/assets/RenderableAssets.cpp
        src/renderer/assets/RenderableAssets.h
        src/renderer/assets/TextureRef.h
        src/assets/BlockModelLoader.cpp
        src/assets/BlockModelLoader.h
)

target_include_directories(BrickBox PRIVATE include)
target_link_libraries(BrickBox glfw PkgConfig::epoxy)