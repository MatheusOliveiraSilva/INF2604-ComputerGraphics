# Traçador de Raios Simples

Este é um traçador de raios simples implementado em C++ para a disciplina INF2604 - Fundamentos de Computação Gráfica.

## Características

- Implementação de um traçador de raios baseado no algoritmo clássico
- Suporte para objetos 3D básicos (esferas e planos)
- Modelo de iluminação de Phong (ambiente, difusa e especular)
- Suporte para sombras
- Geração de imagens em formato PPM

## Compilação

Para compilar o projeto usando CMake:

```bash
mkdir build
cd build
cmake ..
make
```

O executável será gerado na pasta `build/bin`.

## Execução

Execute o programa a partir do diretório raiz do projeto:

```bash
./build/bin/raytracer
```

A imagem será salva como `output.ppm` no diretório atual.

## Estrutura do Projeto

- `include/` - Arquivos de cabeçalho
  - `vec3.h` - Implementação de vetores 3D
  - `ray.h` - Classe para representar raios
  - `object.h` - Interface para objetos da cena
  - `sphere.h` - Implementação de esferas
  - `plane.h` - Implementação de planos
  - `material.h` - Representação de materiais
  - `light.h` - Representação de fontes de luz
  - `camera.h` - Configuração da câmera
  - `scene.h` - Gerenciamento da cena
  - `renderer.h` - Motor de renderização
- `src/` - Arquivos de código-fonte
  - `main.cpp` - Programa principal

## Exemplo de Saída

O programa gera uma imagem que mostra uma esfera vermelha sobre um plano cinza, com sombra projetada. 