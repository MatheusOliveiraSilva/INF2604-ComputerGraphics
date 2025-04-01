#!/bin/bash

# Script para compilar o Ray Tracer

echo "Compilando versão completa..."
g++ -std=c++17 -O3 \
    src/main.cpp \
    src/core/Vector3.cpp \
    src/geometry/Sphere.cpp \
    src/geometry/Box.cpp \
    src/geometry/Triangle.cpp \
    -o raytracer

echo "Compilando teste de triângulos..."
g++ -std=c++17 -O3 \
    src/triangle_test.cpp \
    src/core/Vector3.cpp \
    src/geometry/Triangle.cpp \
    -o triangle_test

echo "Compilando versão de teste básica..."
g++ -std=c++17 -O3 \
    src/basic_test.cpp \
    src/core/Vector3.cpp \
    -o basic_test

echo "Compilando versão simplificada..."
g++ -std=c++17 -O3 \
    src/simple_raytracer.cpp \
    src/core/Vector3.cpp \
    -o simple_raytracer

echo "Compilação concluída."
echo "Execute ./raytracer [samples] para a versão completa."
echo "Execute ./triangle_test para testar a funcionalidade de triângulos."
echo "Execute ./basic_test para gerar uma imagem gradiente simples."
echo "Execute ./simple_raytracer para gerar uma imagem com uma esfera." 