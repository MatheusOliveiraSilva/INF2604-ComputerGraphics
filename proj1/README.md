# Ray Tracer

Implementação de um algoritmo de traçado de raios para a disciplina INF2608 - Fundamentos da Computação Gráfica.

## Recursos Implementados

### Funcionalidades Básicas
- Renderização de cenas 3D usando o algoritmo de traçado de raios
- Iluminação direta com modelo Phong
- Suporte para múltiplas fontes de luz pontual
- Geração de sombras
- Suporte para múltiplas amostras por pixel (anti-aliasing)
- Instanciação de esferas e caixas

### Extensões
- Aplicação de transformações de modelagem (translação, rotação, escala)
- Instanciação de objetos reflexivos
- [Outras extensões a implementar]

## Compilação e Execução

### Requisitos
- CMake 3.10 ou superior
- Compilador C++17 compatível (GCC, Clang, MSVC)

### Instruções de Compilação

```bash
# Criar diretório de build
mkdir -p build
cd build

# Configurar com CMake
cmake ..

# Compilar
make
```

### Executando o Ray Tracer

```bash
# Na pasta build
./raytracer [samples_per_pixel]
```

Onde `samples_per_pixel` é um número inteiro opcional que define quantas amostras serão usadas por pixel para anti-aliasing. O padrão é 4.

Exemplo:
```bash
./raytracer 16  # Renderiza com 16 amostras por pixel
```

A imagem renderizada será salva como um arquivo PPM na pasta atual com o nome `output_Xspp.ppm`, onde X é o número de amostras por pixel.

## Estrutura do Projeto

- `src/core/`: Classes básicas (Vector3, Ray, Color, Image)
- `src/geometry/`: Formas geométricas (Object, Sphere, Box, TransformedObject)
- `src/scene/`: Gerenciamento de cena (Scene, Camera, Material)
- `src/lighting/`: Iluminação (Light, PointLight)
- `src/utils/`: Utilitários (Sampler, Transform)

## Modificando a Cena

Para modificar a cena renderizada, edite o arquivo `src/main.cpp` e recompile o projeto. 