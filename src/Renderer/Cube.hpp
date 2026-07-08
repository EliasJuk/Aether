#pragma once

// Cubo simples usado como placeholder visual do player, até termos um
// modelo 3D de verdade. A base fica em y = 0, "apoiado sobre o chão".
class Cube {
public:
  Cube(float size);
  ~Cube();

  void draw() const;

private:
  unsigned int vao;
  unsigned int vbo;
};