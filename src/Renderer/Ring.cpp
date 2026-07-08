#include "Ring.hpp"

#include <glad/glad.h>
#include <vector>
#include <cmath>

Ring::Ring(int segments) {
  std::vector<float> vertices;

  // Gera pontos ao redor de um círculo de raio 1.
  for (int i = 0; i < segments; i++) {
    float angle = (float)i / (float)segments * 2.0f * 3.14159265f;
    vertices.push_back(cosf(angle));
    vertices.push_back(0.0f);
    vertices.push_back(sinf(angle));
  }

  vertexCount = segments;

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
}

Ring::~Ring() {
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
}

void Ring::draw() const {
  glBindVertexArray(vao);
  // GL_LINE_LOOP conecta o último ponto de volta ao primeiro, fechando o círculo.
  glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
  glBindVertexArray(0);
}