# Mínima versão requerida do CMake
cmake_minimum_required(VERSION 3.10)

# Nome do projeto e versão
project(Example VERSION 1.0)

# Adiciona o executável
add_executable(Example
    src/main.cpp
    src/Game.cpp
    src/GameObject.cpp
    src/Player.cpp
    src/Box.cpp
    src/Scenario1.cpp
    src/Camera.cpp
    src/SpriteDef.cpp
    src/Animation.cpp
    src/BasicShot.cpp
    src/Met.cpp
    src/ContactsHandler.cpp
    src/enemies/Enemy.cpp
    imgui/imgui.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui_sfml/imgui-SFML.cpp
)

# Adiciona o caminho para os arquivos de cabeçalho
target_include_directories(Example PRIVATE include PRIVATE include/enemies PRIVATE imgui PRIVATE imgui/backends PRIVATE imgui_sfml PRIVATE assets)

# Adiciona as bibliotecas SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

target_link_libraries(Example PRIVATE sfml-graphics sfml-window sfml-system box2d GL dl SDL2)
