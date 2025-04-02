#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <iostream>
#include <fstream>
#include <limits>
#include <cstdlib>  // Para rand()
#include <functional> // Para std::function
#include <random>   // Para gerador de números aleatórios de melhor qualidade
#include <algorithm> // Para std::clamp
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
        : width(width), height(height), samplesPerPixel(samplesPerPixel), maxDepth(maxDepth) {
        // Inicializar gerador de números aleatórios
        std::random_device rd;
        gen = std::mt19937(rd());
        dist = std::uniform_real_distribution<float>(0.0f, 1.0f);
    }
    
    // Renderiza a cena e retorna uma matriz de pixels
    std::vector<std::vector<Color>> render(const Scene& scene, const Camera& camera) {
        std::vector<std::vector<Color>> pixels(height, std::vector<Color>(width));
        
        // Progresso
        int totalPixels = width * height;
        int pixelsProcessed = 0;
        int lastPercentage = 0;
        
        #pragma omp parallel for collapse(2) schedule(dynamic, 1)
        for (int j = 0; j < height; j++) {
            for (int i = 0; i < width; i++) {
                Color pixelColor(0, 0, 0);
                
                // Múltiplas amostras por pixel para antialiasing com distribuição melhorada
                for (int s = 0; s < samplesPerPixel; s++) {
                    // Utilizando distribuição estratificada para melhor cobertura do pixel
                    int sqrtSamples = std::sqrt(samplesPerPixel);
                    int sx = s % sqrtSamples;
                    int sy = s / sqrtSamples;
                    
                    float u = float(i + (sx + randomFloat()) / sqrtSamples) / float(width);
                    float v = float(j + (sy + randomFloat()) / sqrtSamples) / float(height);
                    
                    Ray ray = camera.getRay(u, v);
                    pixelColor += traceRay(ray, scene, 0);
                }
                
                // Média das amostras
                pixelColor = pixelColor / float(samplesPerPixel);
                
                // Correção gamma (usando pow para ser mais preciso)
                pixelColor = Color(
                    std::pow(pixelColor.r, 1.0f/2.2f),
                    std::pow(pixelColor.g, 1.0f/2.2f),
                    std::pow(pixelColor.b, 1.0f/2.2f)
                );
                
                // Ajustar exposição para ter um resultado mais próximo da referência
                float exposure = 1.2f;
                pixelColor = Color(
                    1.0f - std::exp(-pixelColor.r * exposure),
                    1.0f - std::exp(-pixelColor.g * exposure),
                    1.0f - std::exp(-pixelColor.b * exposure)
                );
                
                pixels[height - j - 1][i] = pixelColor; // Inverter eixo Y para origem no canto inferior esquerdo
                
                // Atualizar progresso
                #pragma omp atomic
                pixelsProcessed++;
                
                if (pixelsProcessed * 100 / totalPixels > lastPercentage) {
                    #pragma omp critical
                    {
                        int currentPercentage = pixelsProcessed * 100 / totalPixels;
                        if (currentPercentage > lastPercentage) {
                            lastPercentage = currentPercentage;
                            std::cerr << "\rRendering: " << lastPercentage << "% " << std::flush;
                        }
                    }
                }
            }
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
    std::mt19937 gen;                            // Gerador de números aleatórios
    std::uniform_real_distribution<float> dist;  // Distribuição uniforme

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
        
        // Sem interseção - cor de fundo (preto)
        return Color(0.0f, 0.0f, 0.0f);
    }
    
    // Calcula a iluminação direta em um ponto
    Color calculateDirectLight(const Ray& ray, const Scene& scene, const HitRecord& record) {
        // Iluminação ambiente
        Color color = scene.ambientLight.intensity * record.material->ambient;
        
        // Para cada fonte de luz
        for (const auto& light : scene.lights) {
            // Verificar sombra
            bool inShadow = scene.isShadowed(record.point, light);
            
            // Se não estiver na sombra
            if (!inShadow) {
                Vector3 lightDir = light->getDirection(record.point);
                Color lightIntensity = light->getIntensity(record.point);
                
                // Calcular fator de atenuação baseado na distância
                float distance = light->getDistance(record.point);
                
                // Parâmetros ajustados para corresponder melhor à iluminação suave da referência
                float attenuation = 1.0f / (1.0f + 0.09f * distance + 0.032f * distance * distance);
                
                // Ajustar intensidade da luz conforme a atenuação
                Color adjustedIntensity = lightIntensity * attenuation;
                
                // Adicionar iluminação usando o modelo Phong
                color += record.material->shade(ray, record, lightDir, adjustedIntensity);
            }
        }
        
        return color;
    }
    
    // Número aleatório entre 0 e 1 com melhor distribuição
    float randomFloat() {
        return dist(gen);
    }
};

#endif