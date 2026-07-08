#pragma once

// Desenha um círculo (contorno, não preenchido) de raio 1, no plano do chão.
// O tamanho final é ajustado depois via matriz de escala (uModel).
class Ring {
public:
  Ring(int segments = 32);
  ~Ring();

  void draw() const;

private:
  unsigned int vao;
  unsigned int vbo;
  int vertexCount;
};