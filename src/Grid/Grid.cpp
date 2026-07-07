#include "Grid.hpp"

#include <glad/glad.h>
#include <vector>

Grid::Grid(int size) {
  std::vector<float> vertices;

  // Uma linha em X e uma em Z pra cada posição de -size até size.
  for (int i = -size; i <= size; i++) {
    vertices.push_back((float)-size);
    vertices.push_back(0.0f);
    vertices.push_back((float)i);

    vertices.push_back((float)size);
    vertices.push_back(0.0f);
    vertices.push_back((float)i);

    vertices.push_back((float)i);
    vertices.push_back(0.0f);
    vertices.push_back((float)-size);

    vertices.push_back((float)i);
    vertices.push_back(0.0f);
    vertices.push_back((float)size);
  }

  vertexCount = static_cast<int>(vertices.size() / 3);

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(
      GL_ARRAY_BUFFER,
      vertices.size() * sizeof(float),
      vertices.data(),
      GL_STATIC_DRAW
  );

  // Atributo 0: posição (x, y, z), sem espaço nenhum entre um vértice e outro.
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
}

Grid::~Grid() {
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
}

void Grid::draw() const {
  glBindVertexArray(vao);
  glDrawArrays(GL_LINES, 0, vertexCount);
  glBindVertexArray(0);
}