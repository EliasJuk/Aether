#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

#include "Renderer/Shader.hpp"
#include "Renderer/Cube.hpp"
#include "Camera/Camera.hpp"
#include "Grid/Grid.hpp"
#include "Entity/Player.hpp"
#include "Input/Raycast.hpp"

const char* vertexShaderSource = R"(
#version 410 core

layout (location = 0) in vec3 aPosition;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

void main() {
    gl_Position = uProjection * uView * uModel * vec4(aPosition, 1.0);
}
)";

const char* fragmentShaderSource = R"(
#version 410 core

out vec4 FragColor;

uniform vec3 uColor;

void main() {
    FragColor = vec4(uColor, 1.0);
}
)";

int main() {
  if (!glfwInit()) {
    std::cerr << "Erro ao iniciar GLFW\n";
    return -1;
  }

  // ------------------------------------------------------------------------
  // Configura a versão do OpenGL que desejamos utilizar.
  //
  // Neste caso:
  // OpenGL 4.1
  // ------------------------------------------------------------------------
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

  // Utiliza o perfil Core.
  // O perfil Core remove funções antigas do OpenGL e força o uso
  // da API moderna baseada em shaders.
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


  // ------------------------------------------------------------------------
  // Cria a janela.
  //
  // Parâmetros:
  // largura
  // altura
  // título
  // monitor (nullptr = janela comum)
  // contexto compartilhado (nullptr = nenhum)
  // ------------------------------------------------------------------------
  GLFWwindow* window = glfwCreateWindow(
    1280,
    720,
    "Aether",
    nullptr,
    nullptr);

  if (!window) {
    std::cerr << "Erro ao criar janela\n";
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1); // Ativa VSync - sincroniza a taxa de atualização com o monitor.

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Erro ao carregar GLAD\n";
    glfwDestroyWindow(window);
    glfwTerminate();
    return -1;
  }

  glViewport(0, 0, 1280, 720);
  glEnable(GL_DEPTH_TEST);

  Shader shader(vertexShaderSource, fragmentShaderSource);
  Camera camera;
  Grid grid(20);
  Player player;
  Cube playerCube(1.0f);

  bool leftWasDown = false;
  double previousTime = glfwGetTime();

  while (!glfwWindowShouldClose(window)) {
    double currentTime = glfwGetTime();
    float deltaTime = (float)(currentTime - previousTime);
    previousTime = currentTime;

    glfwPollEvents(); // Atualiza eventos do sistema.

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    if (height == 0) height = 1;
    float aspectRatio = (float)width / (float)height;

    // Clique esquerdo: manda o player andar até o ponto clicado no chão.
    int leftState = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (leftState == GLFW_PRESS && !leftWasDown) {
      glm::vec3 groundPoint;
      if (Raycast::screenToGroundPoint(window, camera, width, height, groundPoint)) {
        player.setMoveTarget(groundPoint);
      }
    }
    leftWasDown = (leftState == GLFW_PRESS);

    player.update(deltaTime);
    camera.setTarget(player.getPosition()); // câmera sempre acompanha o player

    glClearColor(0.08f, 0.09f, 0.10f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();
    shader.setMat4("uView", camera.getViewMatrix());
    shader.setMat4("uProjection", camera.getProjectionMatrix(aspectRatio));

    // Chão
    shader.setMat4("uModel", glm::mat4(1.0f)); // matriz "identidade": sem mover, sem girar
    shader.setVec3("uColor", glm::vec3(0.35f, 0.35f, 0.35f));
    grid.draw();

    // Player: usa uModel de verdade agora, pra levar o cubo até a posição dele.
    glm::mat4 playerModel = glm::translate(glm::mat4(1.0f), player.getPosition());
    shader.setMat4("uModel", playerModel);
    shader.setVec3("uColor", glm::vec3(0.2f, 0.6f, 1.0f));
    playerCube.draw();

    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window); // Libera a memória utilizada pela janela.
  glfwTerminate(); // Finaliza o GLFW.

  return 0;
}