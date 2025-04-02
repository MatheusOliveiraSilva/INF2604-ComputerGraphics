#!/usr/bin/env python3
import os
import subprocess
import time
import sys
from datetime import datetime

# Diretório do projeto
PROJECT_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BIN_DIR = os.path.join(PROJECT_DIR, "build")
OUTPUT_DIR = os.path.join(PROJECT_DIR, "output")
EXECUTABLE = os.path.join(BIN_DIR, "raytracer")

# Cria diretório de saída se não existir
os.makedirs(OUTPUT_DIR, exist_ok=True)

def run_test(samples, width=800, height=600, prefix="test"):
    """Executa o raytracer com o número especificado de amostras por pixel."""
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    output_file = os.path.join(OUTPUT_DIR, f"{prefix}_{samples}spp_{timestamp}.ppm")
    
    print(f"Renderizando com {samples} amostras por pixel...")
    start_time = time.time()
    
    # Executa o raytracer
    try:
        subprocess.run([EXECUTABLE, output_file, str(samples)], check=True)
    except subprocess.CalledProcessError as e:
        print(f"Erro ao executar o raytracer: {e}")
        return
    except FileNotFoundError:
        print(f"Executável não encontrado: {EXECUTABLE}")
        print("Certifique-se de compilar o projeto antes de executar os testes.")
        return
    
    elapsed_time = time.time() - start_time
    print(f"Tempo de renderização: {elapsed_time:.2f} segundos")
    print(f"Imagem salva em: {output_file}")
    print("-" * 50)
    
    return output_file, elapsed_time

def main():
    # Verifica se o executável existe
    if not os.path.exists(EXECUTABLE):
        print(f"Executável não encontrado: {EXECUTABLE}")
        print("Compilando o projeto...")
        
        # Cria diretório de build se não existir
        os.makedirs(os.path.join(PROJECT_DIR, "build"), exist_ok=True)
        
        # Configura e compila o projeto
        try:
            subprocess.run(["cmake", ".."], cwd=os.path.join(PROJECT_DIR, "build"), check=True)
            subprocess.run(["make"], cwd=os.path.join(PROJECT_DIR, "build"), check=True)
        except subprocess.CalledProcessError as e:
            print(f"Erro ao compilar o projeto: {e}")
            return
        
        if not os.path.exists(EXECUTABLE):
            print("Falha ao compilar o projeto.")
            return
    
    # Testes com diferentes números de amostras
    samples_list = [1, 4, 16, 64] if len(sys.argv) <= 1 else [int(sys.argv[1])]
    results = []
    
    for samples in samples_list:
        result = run_test(samples)
        if result:
            results.append((samples, *result))
    
    # Resumo dos resultados
    if results:
        print("\nResumo dos resultados:")
        print("Amostras | Tempo (s) | Arquivo")
        print("-" * 50)
        for samples, output_file, elapsed_time in results:
            print(f"{samples:8d} | {elapsed_time:9.2f} | {os.path.basename(output_file)}")

if __name__ == "__main__":
    main()