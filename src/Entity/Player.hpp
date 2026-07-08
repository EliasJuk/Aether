#pragma once
#include <glm/glm.hpp>

// Guarda a posição atual e anda em linha reta até o ponto que foi clicado no chão.
class Player {
public:
  Player();

  void setMoveTarget(const glm::vec3& worldPoint);
  void update(float deltaTime);

  glm::vec3 getPosition() const { return position; }

private:
  glm::vec3 position;
  glm::vec3 moveTarget;
  bool isMoving;

  float moveSpeed;    // unidades por segundo
  float stopDistance; // distância mínima pra considerar "chegou"
};