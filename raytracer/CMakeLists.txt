cmake_minimum_required(VERSION 3.10)
project(Raytracer)

# Configuração do C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Modo de compilação
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Opções de compilação
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Diretórios de inclusão
include_directories(${CMAKE_SOURCE_DIR})

# Executável da Cornell Box
add_executable(cornell_box examples/cornell_box.cpp)

# Executável para cena com recursos extras
add_executable(enhanced_scene examples/enhanced_scene.cpp)

# Configurar diretório de saída dos binários
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# Criar pasta de saída para imagens
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/output) 