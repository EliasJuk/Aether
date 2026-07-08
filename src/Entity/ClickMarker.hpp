#pragma once

#include <glm/glm.hpp>

// Indicador visual de clique: aparece no ponto clicado, expande e some.
class ClickMarker {
public:
  ClickMarker();

  void spawn(const glm::vec3& worldPoint);
  void update(float deltaTime);

  bool isActive() const { return active; }
  glm::vec3 getPosition() const { return position; }

  float getScale() const;
  float getFade() const; // 0 = recém-nascido, 1 = totalmente sumido

private:
  glm::vec3 position;
  bool active;

  float elapsed;
  float duration;

  float startScale;
  float endScale;
};