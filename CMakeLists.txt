cmake_minimum_required(VERSION 3.20)
project(Aether)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 CONFIG REQUIRED)   # janela, input, contexto OpenGL
find_package(glad CONFIG REQUIRED)    # carrega as funções da GPU em runtime
find_package(glm CONFIG REQUIRED)     # matemática (vetores, matrizes) no estilo GLSL
find_package(imgui CONFIG REQUIRED)

# Implementar LUA ao projeto para os Scrips
find_package(Lua REQUIRED)            # interpretador Lua
find_package(sol2 CONFIG REQUIRED)    # wrapper C++ que facilita conversar com o Lua


add_executable(Aether
  src/main.cpp

  src/Renderer/Shader.cpp
  src/Renderer/Cube.cpp
  src/Renderer/Ring.cpp
  
  src/Camera/Camera.cpp

  src/Grid/Grid.cpp

  src/Entity/Player.cpp 
  src/Entity/ClickMarker.cpp

  src/Input/Raycast.cpp

  src/Scripts/LuaEngine.cpp
)

target_link_libraries(
  Aether
  PRIVATE
    glfw
    glad::glad
    glm::glm
    ${LUA_LIBRARIES}
    sol2::sol2
)

target_include_directories(Aether PRIVATE ${LUA_INCLUDE_DIR})

# Grava o caminho absoluto da raiz do projeto dentro do executável, pra
# scripts .lua (e outros assets)
target_compile_definitions(Aether PRIVATE PROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}")
