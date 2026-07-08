#pragma once

#include <glm/glm.hpp>

// Câmera orbital: sempre olha pra um alvo (o player) e gira ao redor dele
// com ângulo de inclinação fixo.
class Camera {
public:
  Camera();

  void setTarget(const glm::vec3& target);
  void rotate(float deltaYawDegrees);
  void zoom(float amount);

  glm::mat4 getViewMatrix() const;
  glm::mat4 getProjectionMatrix(float aspectRatio) const;

  glm::vec3 getPosition() const { return position; }

private:
  void updatePosition();

  glm::vec3 target;

  float yawDegrees;   // rotação horizontal ao redor do alvo
  float pitchDegrees; // inclinação fixa (ângulo isométrico)
  float distance;     // distância do alvo (zoom)

  float minDistance;
  float maxDistance;

  glm::vec3 position; // recalculada toda vez que target/yaw/pitch/distance mudam
};