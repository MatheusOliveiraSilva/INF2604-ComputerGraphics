# Raytracer 3D

Este é um raytracer desenvolvido em C++ para renderizar cenas 3D com iluminação usando o modelo Phong.

## Funcionalidades Implementadas

### Funcionalidades Básicas (7.0 pontos)
- Renderização de cenas 3D com o algoritmo de ray tracing
- Formas geométricas: Esferas e Caixas
- Iluminação direta com modelo Phong
- Sombras
- Anti-aliasing com múltiplas amostras por pixel

### Funcionalidades Extras (3.0 pontos)
- Transformações de modelagem: translação e rotação (1.0 ponto)
- Objetos reflexivos com suporte para recursão de raios (1.0 ponto)
- Luz retangular com distribuição de amostras (1.0 ponto)

## Estrutura do Projeto

```
raytracer/
├── include/              # Arquivos de cabeçalho
│   ├── core/             # Componentes principais
│   ├── geometry/         # Formas geométricas
│   ├── light/            # Fontes de luz
│   ├── material/         # Materiais
│   └── transform/        # Transformações
├── examples/             # Exemplos de cenas
│   ├── cornell_box.cpp   # Exemplo básico da Cornell Box
│   └── enhanced_scene.cpp # Exemplo com funcionalidades extras
├── scripts/              # Scripts de utilidade
├── output/               # Imagens renderizadas
├── CMakeLists.txt        # Configuração do CMake
└── README.md             # Este arquivo
```

## Compilação e Execução

### Usando CMake

```bash
# No diretório raiz do projeto
mkdir build
cd build
cmake ..
make
```

Em seguida, execute os exemplos:

```bash
# Exemplo básico da Cornell Box
./bin/cornell_box

# Exemplo com funcionalidades extras
./bin/enhanced_scene
```

As imagens em formato PPM serão geradas no diretório `output/`.

### Usando o Script de Construção

Você também pode usar o script fornecido para compilar e executar todos os exemplos:

```bash
# No diretório raiz do projeto
chmod +x scripts/build_and_run.sh
./scripts/build_and_run.sh
```

## Visualização da Imagem

As imagens são salvas no formato PPM. Para visualizá-las, você pode:

1. Usar algum visualizador que suporte PPM diretamente
2. Converter para PNG/JPG usando ImageMagick (o script tenta fazer isso automaticamente)

```bash
convert output/cornell_box.ppm output/cornell_box.png
convert output/enhanced_scene.ppm output/enhanced_scene.png
```

## Detalhes das Funcionalidades Extras

### 1. Transformações de Modelagem
- Implementadas com as classes `Translate` e `Rotate`
- Permitem aplicar transformações geométricas nos objetos da cena
- Suporte para rotação em torno de um eixo arbitrário
- Exemplo de uso na Cornell Box com blocos rotacionados

### 2. Objetos Reflexivos
- Implementados com a classe `ReflectiveMaterial`
- Suporte para materiais com superfícies especulares
- Reflexão recursiva com profundidade configrável
- Demonstrado na cena aprimorada com uma esfera reflexiva

### 3. Luz Retangular
- Implementada com a classe `RectLight`
- Distribuição uniforme de pontos de amostragem na superfície retangular
- Melhor realismo nas sombras e iluminação
- Demonstrado na cena aprimorada, substituindo a luz pontual

## Expandindo o Raytracer

Este raytracer foi projetado para ser facilmente expandido. Algumas expansões possíveis:

1. Adicionar materiais reflexivos
2. Implementar refração para objetos transparentes
3. Adicionar fontes de luz retangulares
4. Adicionar suporte para malhas de triângulos 