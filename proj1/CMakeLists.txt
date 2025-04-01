cmake_minimum_required(VERSION 3.10)
project(RayTracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Opções de otimização
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Incluir todos os arquivos fonte
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
)

# Incluir todos os cabeçalhos
include_directories(src)

# Criar o executável
add_executable(raytracer ${SOURCES})

# Adicionar threads (pode ser necessário para paralelização futura)
find_package(Threads REQUIRED)
target_link_libraries(raytracer PRIVATE Threads::Threads)

# Mensagem de informação
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}") 