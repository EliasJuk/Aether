cmake_minimum_required(VERSION 3.20)
project(Aether)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 CONFIG REQUIRED)   # janela, input, contexto OpenGL
find_package(glad CONFIG REQUIRED)    # carrega as funções da GPU em runtime
find_package(glm CONFIG REQUIRED)     # matemática (vetores, matrizes) no estilo GLSL

add_executable(
  Aether
  src/main.cpp
  src/Renderer/Shader.cpp
)

target_link_libraries(
  Aether
  PRIVATE
    glfw
    glad::glad
    glm::glm
)