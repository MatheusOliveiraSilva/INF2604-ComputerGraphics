#ifndef SAMPLER_H
#define SAMPLER_H

#include <vector>
#include <random>
#include <cmath>
#include "../core/Vector3.h"

class Sampler {
public:
    // Gera amostras uniformes no intervalo [0,1) x [0,1)
    static std::vector<Point3> uniform_samples(int num_samples) {
        std::vector<Point3> samples;
        samples.reserve(num_samples); // Reservar espaço antecipadamente
        
        // Para um único sample, retorne o centro do pixel
        if (num_samples <= 1) {
            samples.push_back(Point3(0.5, 0.5, 0));
            return samples;
        }
        
        // Para 4 amostras, retorna uma grade 2x2 (padrão comum)
        if (num_samples == 4) {
            samples.push_back(Point3(0.25, 0.25, 0));
            samples.push_back(Point3(0.75, 0.25, 0));
            samples.push_back(Point3(0.25, 0.75, 0));
            samples.push_back(Point3(0.75, 0.75, 0));
            return samples;
        }
        
        // Determinar o tamanho da grade aproximada
        int grid_size = static_cast<int>(std::sqrt(num_samples));
        double step = 1.0 / grid_size;
        
        // Gerar amostras em formato de grade
        for (int i = 0; i < grid_size && samples.size() < static_cast<size_t>(num_samples); i++) {
            for (int j = 0; j < grid_size && samples.size() < static_cast<size_t>(num_samples); j++) {
                double x = (i + 0.5) * step;
                double y = (j + 0.5) * step;
                samples.push_back(Point3(x, y, 0));
            }
        }
        
        // Se ainda precisamos de mais amostras, adicione no centro
        while (samples.size() < static_cast<size_t>(num_samples)) {
            samples.push_back(Point3(0.5, 0.5, 0));
        }
        
        return samples;
    }
    
    // Gera amostras com jitter para melhor distribuição
    static std::vector<Point3> jittered_samples(int num_samples) {
        std::vector<Point3> samples;
        
        // Para um único sample, retorne o centro do pixel
        if (num_samples == 1) {
            samples.push_back(Point3(0.5, 0.5, 0));
            return samples;
        }
        
        // Determinar a aproximação para grid mais próxima
        int grid_size = static_cast<int>(std::sqrt(num_samples));
        double step = 1.0 / grid_size;
        
        // Configurar gerador aleatório
        static std::uniform_real_distribution<double> dist(0, step);
        static std::mt19937 generator;
        
        // Gerar amostras em grade com jitter
        for (int i = 0; i < grid_size; i++) {
            for (int j = 0; j < grid_size; j++) {
                double x = i * step + dist(generator);
                double y = j * step + dist(generator);
                samples.push_back(Point3(x, y, 0));
            }
        }
        
        // Se ainda precisamos de mais amostras, adicione aleatoriamente
        static std::uniform_real_distribution<double> full_dist(0, 1);
        
        while (samples.size() < static_cast<size_t>(num_samples)) {
            samples.push_back(Point3(full_dist(generator), full_dist(generator), 0));
        }
        
        return samples;
    }
};

#endif 