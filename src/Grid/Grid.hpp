#pragma once

// Desenha linhas formando um grid no chão (y = 0), só como referência
// visual enquanto não temos um terreno de verdade.
class Grid {
public:
  Grid(int size);
  ~Grid();

  void draw() const;

private:
  unsigned int vao;
  unsigned int vbo;

  int vertexCount;
};