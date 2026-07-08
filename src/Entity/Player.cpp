#include "Player.hpp"

Player::Player()
  : position(0.0f, 0.0f, 0.0f)
  , moveTarget(0.0f, 0.0f, 0.0f)
  , isMoving(false)
  , moveSpeed(8.0f)
  , stopDistance(0.1f) {
}

void Player::setMoveTarget(const glm::vec3& worldPoint) {
  moveTarget = worldPoint;
  moveTarget.y = position.y; // mantém o player grudado no chão
  isMoving = true;
}

void Player::update(float deltaTime) {
  if (!isMoving) return;

  glm::vec3 direction = moveTarget - position;
  float distance = glm::length(direction);

  if (distance <= stopDistance) {
    isMoving = false;
    return;
  }

  direction /= distance; // normaliza (vira um vetor de tamanho 1, só a direção)
  position += direction * moveSpeed * deltaTime;
}