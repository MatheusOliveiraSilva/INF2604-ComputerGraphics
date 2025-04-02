#!/usr/bin/env python3
import os
import sys
import glob
from PIL import Image

def convert_ppm_to_png(ppm_file, output_dir=None):
    """Converte um arquivo PPM para PNG."""
    try:
        # Abre a imagem PPM
        img = Image.open(ppm_file)
        
        # Define o diretório de saída
        if output_dir is None:
            output_dir = os.path.dirname(ppm_file)
        
        # Define o nome do arquivo PNG
        png_file = os.path.join(
            output_dir, 
            os.path.splitext(os.path.basename(ppm_file))[0] + ".png"
        )
        
        # Salva como PNG
        img.save(png_file)
        print(f"Convertido: {ppm_file} -> {png_file}")
        
        return png_file
    except Exception as e:
        print(f"Erro ao converter {ppm_file}: {e}")
        return None

def main():
    # Diretório do projeto
    project_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    output_dir = os.path.join(project_dir, "output")
    
    # Verifica se há argumentos específicos
    if len(sys.argv) > 1:
        # Converte arquivos específicos
        for ppm_file in sys.argv[1:]:
            if os.path.exists(ppm_file):
                convert_ppm_to_png(ppm_file, output_dir)
            else:
                print(f"Arquivo não encontrado: {ppm_file}")
    else:
        # Converte todos os arquivos PPM no diretório output
        ppm_files = glob.glob(os.path.join(output_dir, "*.ppm"))
        
        if not ppm_files:
            print(f"Nenhum arquivo PPM encontrado em {output_dir}")
            return
        
        print(f"Convertendo {len(ppm_files)} arquivos PPM...")
        
        for ppm_file in ppm_files:
            convert_ppm_to_png(ppm_file, output_dir)
        
        print(f"Conversão concluída. Arquivos PNG salvos em {output_dir}")

if __name__ == "__main__":
    main() 