# INF2604 - Computação Gráfica

Este repositório contém implementações para o curso de Computação Gráfica, incluindo um raytracer em C++.

## Raytracer

O diretório `raytracer/` contém um rastreador de raios completo capaz de renderizar a Cornell Box clássica e outras cenas 3D.

### Como usar

O projeto agora inclui um Makefile que simplifica o processo de compilação e execução:

```bash
# Navegar até o diretório do raytracer
cd raytracer

# Compilar e executar a Cornell Box (800x600 com 25 amostras por pixel)
make basic

# Limpar os arquivos de compilação
make clean

# Limpar apenas as imagens geradas
make clean-images
```

### Saída

As imagens geradas são salvas no diretório `raytracer/output/` nos formatos PPM e PNG (se o ImageMagick estiver instalado).

### Configurações

Para modificar as configurações da imagem (resolução, amostras por pixel, etc.), edite o arquivo `raytracer/examples/cornell_box.cpp`.
