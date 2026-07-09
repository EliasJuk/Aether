#include "LuaEngine.hpp"

#include <iostream>

LuaEngine::LuaEngine() {
  // Bibliotecas do Lua
  lua.open_libraries(sol::lib::base, sol::lib::math);

  // Lua callbacks: funções C++ registradas que scripts Lua podem invocar. 
  // Por enquanto apenas imprimem no console, pois o sistema de dano/efeitos
  // de verdade ainda não foi implementado.
  lua.set_function("deal_damage", [](sol::table target, int amount) {
    float x = target["x"];
    float y = target["y"];
    float z = target["z"];
    std::cout << "[Lua] Dano de " << amount
              << " em (" << x << ", " << y << ", " << z << ")\n";
  });

  lua.set_function("spawn_effect", [](const std::string& name, float x, float y, float z) {
    std::cout << "[Lua] Efeito '" << name
              << "' em (" << x << ", " << y << ", " << z << ")\n";
  });
}

bool LuaEngine::loadScript(const std::string& path) {
  sol::load_result result = lua.load_file(path);

  if (!result.valid()) {
    sol::error err = result;
    std::cerr << "[Lua] Erro ao carregar script: " << err.what() << "\n";
    return false;
  }

  result(); // executa o script, definindo on_cast dentro do estado Lua
  return true;
}

void LuaEngine::castFireball(const glm::vec3& playerPos, const glm::vec3& targetPos) {
  sol::function onCast = lua["on_cast"];

  if (!onCast.valid()) {
    std::cerr << "[Lua] Função on_cast não encontrada no script\n";
    return;
  }

  sol::table player = lua.create_table();
  player["x"] = playerPos.x;
  player["y"] = playerPos.y;
  player["z"] = playerPos.z;

  sol::table target = lua.create_table();
  target["x"] = targetPos.x;
  target["y"] = targetPos.y;
  target["z"] = targetPos.z;

  onCast(player, target);
}