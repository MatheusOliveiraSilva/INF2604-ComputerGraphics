#ifndef RECTANGULAR_LIGHT_H
#define RECTANGULAR_LIGHT_H

#include "Light.h"
#include <random>

class RectangularLight : public Light {
public:
    Vector3 corner;       // Canto inferior esquerdo da luz retangular
    Vector3 u;            // Vetor que define a direção e comprimento da largura
    Vector3 v;            // Vetor que define a direção e comprimento da altura
    Color intensity;      // Intensidade/cor da luz
    
    // Distribuidor de números aleatórios para amostragem
    mutable std::mt19937 gen;
    mutable std::uniform_real_distribution<float> dist;
    
    // Construtor padrão
    RectangularLight() : corner(0, 0, 0), u(1, 0, 0), v(0, 0, 1), intensity(1, 1, 1) {
        std::random_device rd;
        gen = std::mt19937(rd());
        dist = std::uniform_real_distribution<float>(0.0f, 1.0f);
    }
    
    // Construtor com todos os parâmetros
    RectangularLight(const Vector3& corner, const Vector3& u, const Vector3& v, const Color& intensity) 
        : corner(corner), u(u), v(v), intensity(intensity) {
        std::random_device rd;
        gen = std::mt19937(rd());
        dist = std::uniform_real_distribution<float>(0.0f, 1.0f);
    }
    
    // Método para criar uma luz retangular no teto da Cornell Box
    static RectangularLight* createRectInCornellBoxCeiling(float width, float height, const Color& intensity) {
        // Posição central da luz no teto
        Vector3 center(2.775f, 5.5f, 2.775f);
        // Canto inferior esquerdo
        Vector3 corner = center - Vector3(width/2, 0, height/2);
        // Vetores de direção
        Vector3 u(width, 0, 0);
        Vector3 v(0, 0, height);
        
        return new RectangularLight(corner, u, v, intensity);
    }
    
    // Gera um ponto aleatório na superfície da luz
    Vector3 samplePoint() const {
        float r1 = dist(gen);
        float r2 = dist(gen);
        return corner + r1 * u + r2 * v;
    }
    
    // Implementação dos métodos da interface Light
    // Retorna a direção da luz a partir de um ponto usando uma amostra aleatória na superfície
    virtual Vector3 getDirection(const Vector3& point) const override {
        Vector3 lightPos = samplePoint();
        return normalize(lightPos - point);
    }
    
    // Retorna a intensidade da luz em um ponto
    virtual Color getIntensity(const Vector3& point) const override {
        Vector3 lightPos = samplePoint();
        float distance = (lightPos - point).length();
        // Atenuação simples baseada na distância
        float attenuation = 1.0f / (1.0f + 0.09f * distance + 0.032f * distance * distance);
        return intensity * attenuation;
    }
    
    // Retorna a distância do ponto até a luz (usando um ponto amostrado)
    virtual float getDistance(const Vector3& point) const override {
        Vector3 lightPos = samplePoint();
        return (lightPos - point).length();
    }
};

#endif // RECTANGULAR_LIGHT_H 