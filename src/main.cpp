// GLAD carrega as funções do OpenGL disponíveis na placa de vídeo.
// Sem ele não conseguimos utilizar o OpenGL moderno.
#include <glad/glad.h>
// GLFW é responsável por criar a janela, criar o contexto OpenGL e
// receber entrada do teclado, mouse e outras informações do sistema.
#include <GLFW/glfw3.h>

// Biblioteca padrão para imprimir mensagens no terminal.
#include <iostream>

#include "Renderer/Shader.hpp"
#include "Camera/Camera.hpp"
#include "Grid/Grid.hpp"

const char* vertexShaderSource = R"(
#version 410 core

layout (location = 0) in vec3 aPosition;

uniform mat4 uView;
uniform mat4 uProjection;

void main() {
    gl_Position = uProjection * uView * vec4(aPosition, 1.0);
}
)";

const char* fragmentShaderSource = R"(
#version 410 core

out vec4 FragColor;

uniform vec3 uColor;

void main() {
    FragColor = vec4(uColor, 1.0);
}
)";

int main() {


  if (!glfwInit()) {
  // ------------------------------------------------------------------------
  // Inicializa a biblioteca GLFW.
  //
  // Essa chamada prepara tudo o que o GLFW precisa para funcionar.
  // Se ela falhar, não podemos criar uma janela.
  // ------------------------------------------------------------------------
    std::cerr << "Erro ao iniciar GLFW\n";
    return -1;
  }

  // ------------------------------------------------------------------------
  // Configura a versão do OpenGL que desejamos utilizar.
  //
  // Neste caso:
  // OpenGL 4.1
  // ------------------------------------------------------------------------
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

  // Utiliza o perfil Core.
  //
  // O perfil Core remove funções antigas do OpenGL e força o uso
  // da API moderna baseada em shaders.
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // ------------------------------------------------------------------------
  // Cria a janela.
  //
  // Parâmetros:
  // largura
  // altura
  // título
  // monitor (nullptr = janela comum)
  // contexto compartilhado (nullptr = nenhum)
  // ------------------------------------------------------------------------
  GLFWwindow* window = glfwCreateWindow(
    1280, 
    720, 
    "Aether", 
    nullptr, 
    nullptr
  );

  // Se não conseguiu criar a janela...
  if (!window) {
    std::cerr << "Erro ao criar janela\n";
    // Libera todos os recursos do GLFW.
    glfwTerminate();
    return -1;
  }

  // ------------------------------------------------------------------------
  // Toda chamada do OpenGL precisa saber em qual janela irá desenhar.
  //
  // Esta linha torna a janela recém criada o contexto atual.
  // ------------------------------------------------------------------------

  glfwMakeContextCurrent(window);

  // ------------------------------------------------------------------------
  // Ativa VSync.
  //
  // Valor 1:
  // sincroniza a taxa de atualização do programa com o monitor.
  //
  // Isso evita "screen tearing".
  // ------------------------------------------------------------------------
  glfwSwapInterval(1);

  // ------------------------------------------------------------------------
  // Inicializa o GLAD.
  //
  // O GLAD procura todas as funções do OpenGL disponíveis
  // na placa de vídeo.
  // ------------------------------------------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Erro ao carregar GLAD\n";
    glfwDestroyWindow(window);
    glfwTerminate();
    return -1;
  }

  // ------------------------------------------------------------------------
  // Define qual região da janela o OpenGL poderá utilizar para desenhar.
  //
  // Neste caso:
  // x = 0
  // y = 0
  // largura = 1280
  // altura = 720
  // ------------------------------------------------------------------------
  glViewport(0, 0, 1280, 720);
  glEnable(GL_DEPTH_TEST); // sem isso, objetos mais distantes podem desenhar por cima dos mais próximos

  Shader shader(vertexShaderSource, fragmentShaderSource);
  Camera camera;
  Grid grid(20);

  // ============================= GAME LOOP ================================
  //
  // Enquanto a janela permanecer aberta, este bloco ficará em execução
  //
  // ========================================================================
  while (!glfwWindowShouldClose(window)) {    
    // ----------------------------------------------------------------------
    // Atualiza eventos do sistema.
    //
    // Aqui o GLFW verifica:
    // - teclado
    // - mouse
    // - movimentação da janela
    // - redimensionamento
    // - botão fechar
    // --------------------------------------------------------------------
    glfwPollEvents();

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    if (height == 0) height = 1; // evita divisão por zero se a janela for minimizada
    float aspectRatio = (float)width / (float)height;

    // Define a cor utilizada para limpar a tela.
    //
    // RGBA
    // R = vermelho
    // G = verde
    // B = azul
    // A = transparência
    glClearColor(0.08f, 0.09f, 0.10f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();
    shader.setMat4("uView", camera.getViewMatrix());
    shader.setMat4("uProjection", camera.getProjectionMatrix(aspectRatio));
    shader.setVec3("uColor", glm::vec3(0.35f, 0.35f, 0.35f));

    grid.draw();

    // --------------------------------------------------------------------
    // Troca o buffer invisível pelo buffer visível.
    //
    // Enquanto desenhamos o próximo frame em segundo plano,
    // o monitor continua exibindo o frame anterior.
    //
    // Essa técnica chama-se Double Buffering.
    // --------------------------------------------------------------------
    glfwSwapBuffers(window);
  }


  // ========================================================================
  // FINALIZAÇÃO
  // ========================================================================

  // Libera a memória utilizada pela janela.  
  glfwDestroyWindow(window);

  // Finaliza o GLFW.
  glfwTerminate();

  return 0;
}