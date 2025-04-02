#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <iostream>
#include <fstream>
#include <limits>
#include <cstdlib>  // Para rand()
#include <functional> // Para std::function
#include "Camera.h"
#include "Color.h"
#include "../geometry/Scene.h"
#include "../material/ReflectiveMaterial.h"

class Renderer {
public:
    int width;              // Largura da imagem em pixels
    int height;             // Altura da imagem em pixels
    int samplesPerPixel;    // Número de amostras por pixel
    int maxDepth;           // Profundidade máxima de raios recursivos
    
    // Construtor
    Renderer(int width, int height, int samplesPerPixel = 1, int maxDepth = 5)
        : width(width), height(height), samplesPerPixel(samplesPerPixel), maxDepth(maxDepth) {}
    
    // Renderiza a cena e retorna uma matriz de pixels
    std::vector<std::vector<Color>> render(const Scene& scene, const Camera& camera) {
        std::vector<std::vector<Color>> pixels(height, std::vector<Color>(width));
        
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                Color pixelColor(0, 0, 0);
                
                // Múltiplas amostras por pixel para antialiasing
                for (int s = 0; s < samplesPerPixel; s++) {
                    float u = float(i + randomFloat()) / float(width);
                    float v = float(j + randomFloat()) / float(height);
                    Ray ray = camera.getRay(u, v);
                    pixelColor += traceRay(ray, scene, 0);
                }
                
                // Média das amostras
                pixelColor = pixelColor / float(samplesPerPixel);
                
                // Correção gamma (aproximação simples com raiz quadrada)
                pixelColor = Color(sqrt(pixelColor.r), sqrt(pixelColor.g), sqrt(pixelColor.b));
                
                pixels[height - j - 1][i] = pixelColor; // Inverter eixo Y para origem no canto inferior esquerdo
            }
            
            // Exibir progresso
            std::cerr << "\rRendering: " << static_cast<int>(100.0f * j / height) << "% " << std::flush;
        }
        
        std::cerr << "\rRendering: 100% \n";
        return pixels;
    }
    
    // Salva a imagem em formato PPM
    void saveToPPM(const std::vector<std::vector<Color>>& pixels, const std::string& filename) {
        std::ofstream file(filename, std::ios::out);
        
        // Cabeçalho do arquivo PPM
        file << "P3\n" << width << " " << height << "\n255\n";
        
        // Pixels
        for (const auto& row : pixels) {
            for (const auto& pixel : row) {
                file << static_cast<int>(pixel.getR255()) << ' '
                     << static_cast<int>(pixel.getG255()) << ' '
                     << static_cast<int>(pixel.getB255()) << '\n';
            }
        }
        
        file.close();
    }
    
private:
    // Traça um raio na cena com recursão para reflexões
    Color traceRay(const Ray& ray, const Scene& scene, int depth) {
        if (depth >= maxDepth) return Color(0, 0, 0);
        
        HitRecord record;
        
        // Verificar interseção com a cena
        if (scene.hit(ray, 0.001f, std::numeric_limits<float>::infinity(), record)) {
            // Calcular iluminação direta (Phong)
            Color directColor = calculateDirectLight(ray, scene, record);
            
            // Verificar se é um material reflexivo
            ReflectiveMaterial* reflMat = dynamic_cast<ReflectiveMaterial*>(record.material);
            if (reflMat != nullptr) {
                // Calcular reflexão
                Color reflectedColor = reflMat->calculateReflection(
                    ray, record, depth,
                    [this, &scene](const Ray& r, int d) { return this->traceRay(r, scene, d); }
                );
                
                // Combinar cor direta com reflexão
                return directColor * (1.0f - reflMat->reflectivity) + reflectedColor * reflMat->reflectivity;
            }
            
            // Material não reflexivo - retornar apenas cor direta
            return directColor;
        }
        
        // Sem interseção - cor de fundo (gradiente simples)
        Vector3 unitDirection = normalize(ray.direction);
        float t = 0.5f * (unitDirection.y + 1.0f);
        return Color(1.0f, 1.0f, 1.0f) * (1.0f - t) + Color(0.5f, 0.7f, 1.0f) * t;
    }
    
    // Calcula a iluminação direta em um ponto
    Color calculateDirectLight(const Ray& ray, const Scene& scene, const HitRecord& record) {
        // Iluminação ambiente
        Color color = scene.ambientLight.intensity * record.material->ambient;
        
        // Para cada fonte de luz
        for (const auto& light : scene.lights) {
            // Verificar sombra
            bool inShadow = scene.isShadowed(record.point, light);
            
            // Se não estiver na sombra, ou estiver com sombra parcial
            if (!inShadow) {
                Vector3 lightDir = light->getDirection(record.point);
                Color lightIntensity = light->getIntensity(record.point);
                
                // Calcular fator de atenuação baseado na distância
                float distance = light->getDistance(record.point);
                float attenuation = 1.0f / (1.0f + 0.01f * distance + 0.001f * distance * distance);
                
                // Ajustar intensidade da luz conforme a atenuação
                Color adjustedIntensity = lightIntensity * attenuation;
                
                // Adicionar iluminação usando o modelo Phong
                color += record.material->shade(ray, record, lightDir, adjustedIntensity);
            }
        }
        
        return color;
    }
    
    // Número aleatório entre 0 e 1
    float randomFloat() {
        return rand() / (RAND_MAX + 1.0f);
    }
};

#endif