# Raytracer 3D

Implementação de um raytracer 3D para o projeto da disciplina INF2604-ComputerGraphics.

## Requisitos

- CMake 3.10+
- Compilador C++17

## Como compilar

```bash
mkdir build
cd build
cmake ..
make
```

## Como executar

```bash
./bin/raytracer [cena] [saída] [amostras]
```

Exemplo:
```bash
./bin/raytracer ../examples/basic_scene.json ../output/basic_scene.ppm 4
```

## Funcionalidades

- Renderização de esferas e caixas
- Iluminação com modelo Phong
- Suporte a múltiplas luzes pontuais
- Geração de sombras
- Anti-aliasing com múltiplas amostras por pixel 