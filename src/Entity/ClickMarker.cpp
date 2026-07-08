#include "ClickMarker.hpp"

ClickMarker::ClickMarker()
  : position(0.0f, 0.0f, 0.0f)
  , active(false)
  , elapsed(0.0f)
  , duration(0.4f)
  , startScale(0.3f)
  , endScale(1.2f) {
}

void ClickMarker::spawn(const glm::vec3& worldPoint) {
  position = worldPoint;
  position.y += 0.01f; // evita conflito com as linhas do grid no mesmo plano
  active = true;
  elapsed = 0.0f;
}

void ClickMarker::update(float deltaTime) {
  if (!active) return;

  elapsed += deltaTime;
  if (elapsed >= duration) active = false;
}

float ClickMarker::getScale() const {
  float t = elapsed / duration;
  if (t > 1.0f) t = 1.0f;
  return startScale + (endScale - startScale) * t;
}

float ClickMarker::getFade() const {
  float t = elapsed / duration;
  if (t > 1.0f) t = 1.0f;
  return t;
}