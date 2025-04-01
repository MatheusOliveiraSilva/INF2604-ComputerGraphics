#include <iostream>
#include "core/Vector3.h"
#include "core/Color.h"
#include "core/Image.h"

int main() {
    // Criar uma imagem pequena para teste
    int width = 200;
    int height = 100;
    Image image(width, height);
    
    // Gerar uma imagem gradiente
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double r = static_cast<double>(x) / (width - 1);
            double g = static_cast<double>(y) / (height - 1);
            double b = 0.2;
            
            image.set_pixel(x, y, Color(r, g, b));
        }
    }
    
    // Salvar a imagem
    image.save_ppm("test_output.ppm");
    std::cout << "Imagem de teste salva como test_output.ppm" << std::endl;
    
    return 0;
} 