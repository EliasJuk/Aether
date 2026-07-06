# Aether

## ⚠️ Primeira vez rodando o projeto?

Antes de compilar, verifique se você já tem o **CMake** e o **vcpkg** instalados no seu sistema (em `C:\vcpkg`).

Se essa é a **primeira vez** que você baixa este projeto, ou se ainda não tem o ambiente configurado, rode primeiro:

```powershell
scripts/run-0-setup.bat
```

Esse script instala o CMake (se necessário), clona o vcpkg, faz o bootstrap e instala todas as dependências do projeto (GLFW, GLAD, GLM, ImGui).

**Só depois disso**, siga com o fluxo normal:

```powershell
scripts/run-1-build.bat      # configura o projeto com CMake
scripts/run-2-compile.bat    # compila
scripts/run-3-run.bat        # executa

```

Ou, para fazer tudo de uma vez:
```powershell
scripts/run-quick.bat
```

> 💡 Se você já tem o vcpkg instalado em `C:\vcpkg` (de outro projeto, por exemplo), pode pular o `run-0-setup.bat` e ir direto para o `run-1-build.bat`.