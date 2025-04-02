#ifndef RECT_LIGHT_H
#define RECT_LIGHT_H

#include <vector>
#include <random>
#include <cmath>
#include "Light.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class RectLight : public Light {
public:
    Vector3 corner;      // Canto inferior esquerdo
    Vector3 u;           // Vetor ao longo da largura
    Vector3 v;           // Vetor ao longo da altura
    Color intensity;     // Intensidade/cor da luz
    int samplesU;        // Número de amostras na direção u
    int samplesV;        // Número de amostras na direção v
    
    std::vector<Vector3> samplePoints;  // Pontos de amostragem pré-calculados
    std::mt19937 rng;                   // Gerador de números aleatórios
    
    // Construtores
    RectLight() 
        : corner(0, 0, 0), u(1, 0, 0), v(0, 1, 0), 
          intensity(1, 1, 1), samplesU(1), samplesV(1) {
        initializeSamples();
    }
    
    RectLight(const Vector3& corner, const Vector3& u, const Vector3& v, 
             const Color& intensity, int samplesU = 4, int samplesV = 4)
        : corner(corner), u(u), v(v), 
          intensity(intensity), samplesU(samplesU), samplesV(samplesV) {
        initializeSamples();
    }
    
    // Inicializa os pontos de amostragem com distribuição uniforme
    void initializeSamples() {
        // Semear o gerador com um valor aleatório
        std::random_device rd;
        rng = std::mt19937(rd());
        
        // Distribuição uniforme [0,1]
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);
        
        // Criar pontos de amostragem
        samplePoints.clear();
        
        // Amostragem estratificada (divide o retângulo em células)
        for (int i = 0; i < samplesU; i++) {
            for (int j = 0; j < samplesV; j++) {
                // Posição base da célula
                float cellU = (float)i / samplesU;
                float cellV = (float)j / samplesV;
                
                // Posição aleatória dentro da célula
                float offsetU = dist(rng) / samplesU;
                float offsetV = dist(rng) / samplesV;
                
                // Posição final no retângulo
                float su = cellU + offsetU;
                float sv = cellV + offsetV;
                
                // Converter para posição 3D
                Vector3 samplePoint = corner + u * su + v * sv;
                samplePoints.push_back(samplePoint);
            }
        }
    }
    
    // Seleciona um ponto de amostra aleatório
    Vector3 getRandomSample() const {
        if (samplePoints.empty()) {
            return corner + u * 0.5f + v * 0.5f;  // Centro do retângulo se não houver amostras
        }
        
        std::uniform_int_distribution<int> dist(0, samplePoints.size() - 1);
        int index = dist(const_cast<std::mt19937&>(rng));
        return samplePoints[index];
    }
    
    // Implementação dos métodos da interface Light
    
    // Direção da luz (média de todas as amostras)
    virtual Vector3 getDirection(const Vector3& point) const override {
        // Usar um ponto aleatório da luz para a direção
        Vector3 lightPos = getRandomSample();
        return normalize(lightPos - point);
    }
    
    // Intensidade da luz (dividida pelo número de amostras)
    virtual Color getIntensity(const Vector3& point) const override {
        // Atenuar baseado na distância e área
        float area = u.cross(v).length();
        float distance = getDistance(point);
        float attenuation = area / (4.0f * M_PI * distance * distance);
        
        // Evitar atenuação excessiva
        attenuation = std::min(1.0f, attenuation);
        
        return intensity * attenuation;
    }
    
    // Distância da luz (usa a amostra aleatória)
    virtual float getDistance(const Vector3& point) const override {
        Vector3 lightPos = getRandomSample();
        return (lightPos - point).length();
    }
};

#endif // RECT_LIGHT_H 