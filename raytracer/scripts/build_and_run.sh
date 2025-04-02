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

# Função para compilar e executar um exemplo
compile_and_run() {
    local example_name=$1
    local example_file=$2
    
    echo "Compilando o exemplo $example_name..."
    g++ -std=c++11 -O3 -I"$ROOT_DIR" "$ROOT_DIR/examples/$example_file" -o "$BUILD_DIR/$example_name"
    
    # Verificar se a compilação foi bem-sucedida
    if [ $? -eq 0 ]; then
        echo "Compilação concluída com sucesso!"
        
        # Executar o exemplo
        echo "Executando o raytracer para $example_name..."
        cd "$BUILD_DIR"
        ./$example_name
        
        # Mover a imagem para o diretório de saída
        if [ -f "$example_name.ppm" ]; then
            mv "$example_name.ppm" "$OUTPUT_DIR/"
            echo "Imagem salva em $OUTPUT_DIR/$example_name.ppm"
            
            # Converter para PNG se o ImageMagick estiver instalado
            if command -v convert >/dev/null 2>&1; then
                echo "Convertendo PPM para PNG..."
                convert "$OUTPUT_DIR/$example_name.ppm" "$OUTPUT_DIR/$example_name.png"
                echo "Imagem convertida para $OUTPUT_DIR/$example_name.png"
            else
                echo "ImageMagick não encontrado. A imagem foi salva apenas no formato PPM."
            fi
        else
            echo "Erro: A imagem $example_name.ppm não foi gerada!"
        fi
    else
        echo "Erro na compilação de $example_name!"
    fi
    
    echo "---------------------------------------------"
}

# Compilar e executar ambos os exemplos
compile_and_run "cornell_box" "cornell_box.cpp"
compile_and_run "enhanced_scene" "enhanced_scene.cpp"

echo "Processamento concluído!" 