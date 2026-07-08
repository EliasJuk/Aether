#include "Camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

Camera::Camera()
    : target(0.0f, 0.0f, 0.0f)
    , yawDegrees(45.0f)
    , pitchDegrees(35.0f) // ângulo comum em jogos isométricos
    , distance(20.0f)
    , minDistance(6.0f)
    , maxDistance(50.0f) 
    {
      updatePosition();
    }

void Camera::setTarget(const glm::vec3& newTarget) {
  target = newTarget;
  updatePosition();
}

void Camera::rotate(float deltaYawDegrees) {
  yawDegrees += deltaYawDegrees;
  updatePosition();
}

void Camera::zoom(float amount) {
  distance -= amount;

  if (distance < minDistance) distance = minDistance;
  if (distance > maxDistance) distance = maxDistance;

  updatePosition();
}

void Camera::updatePosition() {
  float yawRad = glm::radians(yawDegrees);
  float pitchRad = glm::radians(pitchDegrees);

  float horizontalDistance = distance * cosf(pitchRad);
  float height = distance * sinf(pitchRad);

  position = target + glm::vec3(
      horizontalDistance * cosf(yawRad),
      height,
      horizontalDistance * sinf(yawRad)
  );
}

glm::mat4 Camera::getViewMatrix() const {
  return glm::lookAt(
    position,
    target,
    glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) const {
  return glm::perspective(
    glm::radians(45.0f), 
    aspectRatio, 
    0.1f, 
    1000.0f);
}