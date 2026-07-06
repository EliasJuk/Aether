#include "Shader.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Shader::Shader(const char* vertexSource, const char* fragmentSource) {
  // Compila os dois shaders e depois linka num único programa.
  unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
  unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

  id = glCreateProgram();

  glAttachShader(id, vertexShader);
  glAttachShader(id, fragmentShader);
  glLinkProgram(id);

  // O link pode falhar mesmo com os dois shaders compilados sem erro,
  // por exemplo se um "out" do vertex não bate com um "in" do fragment.
  int success;
  glGetProgramiv(id, GL_LINK_STATUS, &success);

  if (!success) {
    char infoLog[512];
    glGetProgramInfoLog(id, 512, nullptr, infoLog);
    std::cerr << "Erro ao linkar shader program:\n" << infoLog << std::endl;
  }

  // Depois de linkados, os shaders individuais não são mais necessários.
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

Shader::~Shader() {
  glDeleteProgram(id);
}

void Shader::use() const {
  glUseProgram(id);
}

void Shader::setMat4(const std::string& name, const glm::mat4& value) const {
  // Busca a location da variável pelo nome e envia a matriz.
  // value_ptr converte glm::mat4 pro formato de floats que o OpenGL espera.
  glUniformMatrix4fv(
    glGetUniformLocation(id, name.c_str()),
    1,        // quantidade de matrizes (1 = não é array)
    GL_FALSE, // GLM já usa o mesmo layout de memória do OpenGL, sem precisar transpor
    glm::value_ptr(value)
  );
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const {
  // Mesma ideia do setMat4, mas pra um vetor de 3 componentes (cor, posição, etc).
  glUniform3fv(
    glGetUniformLocation(id, name.c_str()),
    1,
    glm::value_ptr(value)
  );
}

unsigned int Shader::compileShader(unsigned int type, const char* source) {
  unsigned int shader = glCreateShader(type);

  glShaderSource(shader, 1, &source, nullptr);
  glCompileShader(shader);

  int success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  if (!success) {
    char infoLog[512];
    glGetShaderInfoLog(shader, 512, nullptr, infoLog);
    // Aponta a linha exata do erro no código GLSL, igual erro de compilador.
    std::cerr << "Erro ao compilar shader:\n" << infoLog << std::endl;
  }

  return shader;
}