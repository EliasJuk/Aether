@echo off
setlocal EnableDelayedExpansion

REM ---------------------------------------
REM Configurar cores ANSI
REM ---------------------------------------
for /F %%a in ('echo prompt $E ^| cmd') do set "ESC=%%a"
set "GREEN=%ESC%[92m"
set "CYAN=%ESC%[96m"
set "YELLOW=%ESC%[93m"
set "RESET=%ESC%[0m"

echo %CYAN%========================================%RESET%
echo %CYAN%===============  Aether  ===============%RESET%
echo %CYAN%========================================%RESET%
echo.

set VCPKG_DIR=C:\vcpkg

REM ---------------------------------------
REM 1. Verificar/instalar o CMake
REM ---------------------------------------
where cmake >nul 2>nul
if %errorlevel% neq 0 (
  echo %YELLOW%[1/5]%RESET% CMake nao encontrado. Instalando via winget...
  winget install Kitware.CMake
  set "PATH=%PATH%;C:\Program Files\CMake\bin"
  echo.
) else (
  echo %GREEN%[1/5]%RESET% CMake ja instalado. OK.
)
echo.

REM ---------------------------------------
REM 2. Clonar o vcpkg (se nao existir)
REM ---------------------------------------
if not exist "%VCPKG_DIR%\" (
  echo %YELLOW%[2/5]%RESET% Clonando vcpkg em %VCPKG_DIR%...
  git clone https://github.com/microsoft/vcpkg.git "%VCPKG_DIR%"
) else (
  echo %GREEN%[2/5]%RESET% vcpkg ja existe em %VCPKG_DIR%. Pulando clone.
)
echo.

REM ---------------------------------------
REM 3. Bootstrap do vcpkg
REM ---------------------------------------
if not exist "%VCPKG_DIR%\vcpkg.exe" (
  echo %YELLOW%[3/5]%RESET% Rodando bootstrap do vcpkg...
  call "%VCPKG_DIR%\bootstrap-vcpkg.bat"
) else (
  echo %GREEN%[3/5]%RESET% vcpkg ja compilado. Pulando bootstrap.
)
echo.

REM ---------------------------------------
REM 4. Instalar os pacotes do projeto
REM ---------------------------------------
echo %YELLOW%[4/5]%RESET% Instalando dependencias (glfw3, glad, glm, imgui)...
"%VCPKG_DIR%\vcpkg" install glfw3:x64-windows glad:x64-windows glm:x64-windows imgui[glfw-binding,opengl3-binding]:x64-windows
echo.

REM ---------------------------------------
REM 5. Integrar com Visual Studio
REM ---------------------------------------
echo %YELLOW%[5/5]%RESET% Integrando vcpkg com Visual Studio...
"%VCPKG_DIR%\vcpkg" integrate install
echo.

echo %CYAN%========================================%RESET%
echo %GREEN%  Setup concluido!%RESET%
echo %CYAN%========================================%RESET%
echo.
echo %YELLOW%Proximo passo:%RESET% rode o script %CYAN%run-build-compile.bat%RESET% do projeto.
echo.
pause