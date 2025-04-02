#!/bin/bash

# Diretório raiz do projeto
ROOT_DIR=$(dirname "$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)")

# Verificar se o diretório build existe, caso contrário, criar
BUILD_DIR="$ROOT_DIR/build"
if [ ! -d "$BUILD_DIR" ]; then
    mkdir -p "$BUILD_DIR"
fi

# Diretório para imagens de saída
OUTPUT_DIR="$ROOT_DIR/output"
if [ ! -d "$OUTPUT_DIR" ]; then
    mkdir -p "$OUTPUT_DIR"
fi

# Nome do exemplo
EXAMPLE_NAME="enhanced_scene"

echo "Compilando cena avançada com materiais reflexivos e luz retangular..."
g++ -std=c++11 -O3 -I"$ROOT_DIR" "$ROOT_DIR/examples/$EXAMPLE_NAME.cpp" -o "$BUILD_DIR/$EXAMPLE_NAME"

# Verificar se a compilação foi bem-sucedida
if [ $? -eq 0 ]; then
    echo "Compilação concluída com sucesso!"
    
    # Executar o exemplo
    echo "Executando o raytracer para cena avançada..."
    cd "$BUILD_DIR"
    ./$EXAMPLE_NAME
    
    # Mover a imagem para o diretório de saída
    if [ -f "$EXAMPLE_NAME.ppm" ]; then
        mv "$EXAMPLE_NAME.ppm" "$OUTPUT_DIR/"
        echo "Imagem salva em $OUTPUT_DIR/$EXAMPLE_NAME.ppm"
        
        # Converter para PNG se o ImageMagick estiver instalado
        if command -v convert >/dev/null 2>&1; then
            echo "Convertendo PPM para PNG..."
            convert "$OUTPUT_DIR/$EXAMPLE_NAME.ppm" "$OUTPUT_DIR/$EXAMPLE_NAME.png"
            echo "Imagem convertida para $OUTPUT_DIR/$EXAMPLE_NAME.png"
            
            # Abrir a imagem (opcional)
            if command -v open >/dev/null 2>&1; then  # Para macOS
                open "$OUTPUT_DIR/$EXAMPLE_NAME.png"
            elif command -v display >/dev/null 2>&1; then  # Para Linux com ImageMagick
                display "$OUTPUT_DIR/$EXAMPLE_NAME.png"
            fi
        else
            echo "ImageMagick não encontrado. A imagem foi salva apenas no formato PPM."
        fi
    else
        echo "Erro: A imagem não foi gerada!"
    fi
else
    echo "Erro na compilação!"
fi 