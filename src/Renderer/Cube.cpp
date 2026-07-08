#include "Cube.hpp"

#include <glad/glad.h>

Cube::Cube(float size) {
  float h = size / 2.0f;

  // 36 vértices (12 triângulos), base em y = 0, topo em y = size.
  float vertices[] = {
    // Frente
    -h, 0.0f,  h,   h, 0.0f,  h,   h, size,  h,
    -h, 0.0f,  h,   h, size,  h,  -h, size,  h,
    // Trás
    -h, 0.0f, -h,   h, size, -h,   h, 0.0f, -h,
    -h, 0.0f, -h,  -h, size, -h,   h, size, -h,
    // Esquerda
    -h, 0.0f, -h,  -h, 0.0f,  h,  -h, size,  h,
    -h, 0.0f, -h,  -h, size,  h,  -h, size, -h,
    // Direita
     h, 0.0f, -h,   h, size,  h,   h, 0.0f,  h,
     h, 0.0f, -h,   h, size, -h,   h, size,  h,
    // Topo
    -h, size,  h,   h, size,  h,   h, size, -h,
    -h, size,  h,   h, size, -h,  -h, size, -h,
    // Base
    -h, 0.0f, -h,   h, 0.0f, -h,   h, 0.0f,  h,
    -h, 0.0f, -h,   h, 0.0f,  h,  -h, 0.0f,  h,
  };

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);

  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
}

Cube::~Cube() {
  glDeleteVertexArrays(1, &vao);
  glDeleteBuffers(1, &vbo);
}

void Cube::draw() const {
  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glBindVertexArray(0);
}