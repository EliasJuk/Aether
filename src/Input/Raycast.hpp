#pragma once

#include <glm/glm.hpp>

struct GLFWwindow;
class Camera;

namespace Raycast {
  // Converte a posição do mouse na tela num ponto no chão (plano y = 0).
  // Retorna false se não houver interseção válida.
  bool screenToGroundPoint(
    GLFWwindow* window,
    const Camera& camera,
    int screenWidth,
    int screenHeight,
    glm::vec3& outPoint
  );
}