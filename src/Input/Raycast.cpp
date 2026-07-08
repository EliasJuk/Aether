#include "Raycast.hpp"
#include "../Camera/Camera.hpp"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_inverse.hpp>
#include <cmath>

namespace Raycast {
  bool screenToGroundPoint(
      GLFWwindow* window,
      const Camera& camera,
      int screenWidth,
      int screenHeight,
      glm::vec3& outPoint) {
    double mouseX, mouseY;
    glfwGetCursorPos(window, &mouseX, &mouseY);

    // Converte a posição do mouse (em pixels) pra coordenadas de -1 a 1
    float ndcX = (2.0f * (float)mouseX) / (float)screenWidth - 1.0f;
    float ndcY = 1.0f - (2.0f * (float)mouseY) / (float)screenHeight;

    float aspectRatio = (float)screenWidth / (float)screenHeight;

    glm::mat4 projection = camera.getProjectionMatrix(aspectRatio);
    glm::mat4 view = camera.getViewMatrix();

    // Transforma coordenadas de tela (2D) em coordenadas do mundo 3D
    // Unprojection: caminho inverso do vertex shader (tela -> mundo,
    // em vez de mundo -> tela). Por isso usamos as matrizes inversas:
    // multiplicar pela inversa "desfaz" a transformação original.
    glm::mat4 invProjection = glm::inverse(projection);
    glm::mat4 invView = glm::inverse(view);

    glm::vec4 rayClipNear(ndcX, ndcY, -1.0f, 1.0f);
    glm::vec4 rayClipFar(ndcX, ndcY, 1.0f, 1.0f);

    glm::vec4 rayEyeNear = invProjection * rayClipNear;
    glm::vec4 rayEyeFar = invProjection * rayClipFar;

    rayEyeNear /= rayEyeNear.w;
    rayEyeFar /= rayEyeFar.w;

    glm::vec3 rayWorldNear = glm::vec3(invView * rayEyeNear);
    glm::vec3 rayWorldFar = glm::vec3(invView * rayEyeFar);

    glm::vec3 rayDirection = glm::normalize(rayWorldFar - rayWorldNear);

    // Onde essa "linha imaginária" cruza o chão (y = 0)?
    if (fabs(rayDirection.y) < 0.0001f) {
      return false; // raio praticamente paralelo ao chão, sem cruzamento
    }

    float t = -rayWorldNear.y / rayDirection.y;

    if (t < 0.0f) {
      return false; // o cruzamento ficaria atrás da câmera
    }

    outPoint = rayWorldNear + rayDirection * t;
    return true;
  }
}