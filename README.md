# INF2604 - Computação Gráfica

Este repositório contém implementações para o curso de Computação Gráfica, incluindo um raytracer em C++.

## Raytracer

O diretório `raytracer/` contém um rastreador de raios completo capaz de renderizar a Cornell Box clássica e outras cenas 3D.

### Como usar

O projeto agora inclui um Makefile que simplifica o processo de compilação e execução:

```bash
# Navegar até o diretório do raytracer
cd raytracer

# Compilar e executar a Cornell Box (800x600 com 25 amostras por pixel)
make basic

# Limpar os arquivos de compilação
make clean

# Limpar apenas as imagens geradas
make clean-images
```

### Saída

As imagens geradas são salvas no diretório `raytracer/output/` nos formatos PPM e PNG (se o ImageMagick estiver instalado).

### Configurações

Para modificar as configurações da imagem (resolução, amostras por pixel, etc.), edite o arquivo `raytracer/examples/cornell_box.cpp`.

## Relatório Técnico Completo

### 1. Estrutura do Projeto e Primeira Execução
O repositório contém dois módulos principais:
1. **`raytracer/`** – motor de renderização em C++.
2. **Material de apoio** (arquivos de enunciado e exemplos de imagens).  
A estrutura do diretório `raytracer/` é a seguinte:
```
raytracer/
 ├── include/              # Cabeçalhos (core, geometry, light, material, transform)
 ├── examples/             # Cenas de demonstração (Cornell Box, luz retangular, reflexivos)
 ├── build/                # Binários gerados (criado em tempo de compilação)
 ├── output/               # Imagens renderizadas (PPM/PNG)
 ├── Makefile              # Alvos de compilação/execução
 └── CMakeLists.txt        # Alternativa de build via CMake
```
Para reproduzir os experimentos pela primeira vez:
```bash
# Na raiz do repositório
cd raytracer    # entrar no módulo principal
make basic      # compila Cornell Box com luz pontual (800×600 – 25 spp)
```
O `make` cria automaticamente `raytracer/build/` (executáveis) e `raytracer/output/` (imagens).

### 2. Diretório de Saída
Todas as imagens geradas são gravadas em:
```
raytracer/output/
```
Ex.: `cornell_box_800x600_25samples.png`, `cornell_box_rectlight.png`, `reflective_scene.png`.

### 3. Comandos Bash para Executar as Cenas
| Cena | Alvo Make | Arquivo Fonte |
|------|-----------|---------------|
| Cornell Box (luz pontual) | `make basic` | `examples/cornell_box.cpp` |
| Cornell Box (luz retangular) | `make rectlight` | `examples/rectangular_light_scene.cpp` |
| Esfera reflexiva | `make reflective` | `examples/reflective_scene.cpp` |
Todos os alvos convertem automaticamente o `.ppm` em `.png` se o *ImageMagick* estiver presente.

### 4. Componentes Implementados e Fundamentos Teóricos
1. **Gerador de Raios (`core/Camera.h`)** – Constrói raios primários por pixel:  
   \(\vec r(u,v)=\vec{origem}+\vec d(u,v)\), onde \(u,v\) são coordenadas normalizadas.
2. **Antialiasing** – Amostragem estratificada: o pixel \([0,1]^2\) é subdividido em \(\sqrt{N}\times\sqrt{N}\) subcélulas; cada amostra gera deslocamentos \(r_1,r_2\sim U(0,1)\). Implementado em `core/Renderer.h`.
3. **Interseção** – Rotinas de interseção raio‑esfera e raio‑AABB (`geometry/Sphere.h`, `geometry/Box.h`).
4. **Iluminação Direta** – Modelo Phong:  
   • Difuso: \(L_d = k_d (\mathbf L\cdot\mathbf N)I\)  
   • Especular: \(L_s = k_s (\mathbf R\cdot\mathbf V)^{\alpha}I\).  
   Implementação em `material/Material.h`.
5. **Sombras** – Para cada luz é lançado um *shadow‑ray*; se qualquer objeto intersecta antes da luz, o ponto está sombreado (`geometry/Scene.h::isShadowed`).
6. **Materiais Reflexivos** – `material/ReflectiveMaterial.h` calcula o vetor refletido \(\mathbf R=\mathbf V-2(\mathbf V\cdot\mathbf N)\mathbf N\) e traça o raio secundário recursivamente.
7. **Luz Pontual** – `light/PointLight.h` provê direção, intensidade e distância constantes.
8. **Luz Retangular** – `light/RectangularLight.h` amostra um ponto aleatório na superfície:  
   \(P = C + r_1\,\mathbf u + r_2\,\mathbf v, \; r_i\sim U(0,1)\).  
   Isso gera penumbra realista.
9. **Exposição e *Gamma* ** – Após a média das amostras o RGB é ajustado:  
   \(C' = (1-e^{-\text{expo}\,C^{1/\gamma}})\).

### 5. Mapeamento de Arquivos Relevantes
| Componente | Arquivos |
|------------|----------|
| Câmera & geração de raios | `core/Camera.h` |
| Renderização & sampling | `core/Renderer.h` |
| Sombras | `geometry/Scene.h` |
| Materiais (Phong) | `material/Material.h` |
| Reflexão | `material/ReflectiveMaterial.h` |
| Luz pontual | `light/PointLight.h` |
| Luz retangular | `light/RectangularLight.h` |
| Exemplos de cena | `examples/*.cpp` |

### 6. Atendimento aos 7 Pontos Básicos do Enunciado
| Requisito Básico | Onde Está Implementado | Evidência |
|------------------|------------------------|-----------|
| Instanciação de esferas e caixas | `examples/cornell_box.cpp`, `examples/reflective_scene.cpp`, `geometry/*` | Blocos e esferas na Cornell Box |
| Fonte(s) de luz pontual | `examples/cornell_box.cpp`, `light/PointLight.h` | Luz central \(+ auxiliares\) |
| Iluminação Phong | `material/Material.h` | Cálculo difuso + especular |
| Geração de sombras | `Scene::isShadowed` | Shadow‑rays por luz |
| Múltiplas amostras por pixel | `Renderer::render` | `samplesPerPixel` configurável (25/100) |
| Cálculo direto (sem GI) | `Renderer::calculateDirectLight` | Soma luz ambiente + fontes |
| Arquitetura modular | Pastas `core`, `geometry`, `light`, `material` | Organização clara |

Total: **7.0 pts concluídos**.

### 7. Comparação de Imagens
* **`cornell_box_800x600_25samples.png`** – Cornell Box clássica com **luz pontual**. Sombras duras e discretas; 25 spp gera leve ruído.
* **`cornell_box_rectlight.png`** – Mesma cena com **luz retangular 1 m × 1 m** no teto (amostragem de área). Penumbra visível nas bordas das sombras e ruído ligeiramente maior pela variação estocástica.
As diferenças principais decorrem do tamanho da fonte: luz pontual → sombras nítidas; luz de área → sombras suaves.

### 8. Cena `reflective_scene.png`
Esta imagem demonstra **objetos reflexivos**:
- **Esfera espelhada** (material reflexivo 90 %) no centro (`examples/reflective_scene.cpp`).
- Duas esferas difusas azul e amarela à frente (X = ±3, Z = 4).  
- Chão lambertiano e iluminação por duas luzes pontuais (teto e frontal).
O reflexo é obtido via recursão em `ReflectiveMaterial::calculateReflection` até profundidade 5. Anti‑aliasing de 100 amostras suaviza a imagem.
