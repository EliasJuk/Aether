#pragma once

#include <string>
#include <glm/glm.hpp>

// Classe responsável por criar e usar um shader program do OpenGL.
class Shader {
  public:
    // Recebe o código fonte do vertex shader e do fragment shader.
    Shader(const char* vertexSource, const char* fragmentSource);

    // Libera o programa da GPU ao destruir o objeto.
    ~Shader();

    // Ativa este shader para os próximos desenhos.
    void use() const;

    // Envia valores uniform para o shader.
    void setMat4(const std::string& name, const glm::mat4& value) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;

    private:
    // Identificador do shader program no OpenGL.
    unsigned int id;

    // Compila um shader individual e retorna seu identificador.
    unsigned int compileShader(unsigned int type, const char* source);
};