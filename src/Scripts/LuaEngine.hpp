#pragma once

#include <sol/sol.hpp>
#include <glm/glm.hpp>
#include <string>

// Ponte entre C++ e Lua: carrega scripts .lua e expõe pra eles funções
// C++ que podem ser chamadas de dentro do script (deal_damage, spawn_effect).
class LuaEngine {
public:
  LuaEngine();

  // Carrega e executa um arquivo .lua. Isso deixa as funções definidas
  // nele (tipo on_cast) disponíveis pra serem chamadas depois.
  bool loadScript(const std::string& path);

  // Chama a função on_cast(player, target) definida no script carregado,
  // passando as posições como tabelas Lua { x = ..., y = ..., z = ... }.
  void castFireball(const glm::vec3& playerPos, const glm::vec3& targetPos);

private:
  sol::state lua;
};