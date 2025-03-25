cmake_minimum_required(VERSION 3.10)
project(TraçadoDeRaioSimples)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adiciona o diretório include
include_directories(include)

# Adiciona o executável
add_executable(raytracer src/main.cpp)

# Define local de saída dos binários
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) 