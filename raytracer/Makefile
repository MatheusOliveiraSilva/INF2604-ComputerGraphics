# Makefile para o projeto de raytracer
# Configurações
CXX = g++
CXXFLAGS = -std=c++11 -O3
INC_DIR = -I.
SRC_DIR = examples
BUILD_DIR = build
OUTPUT_DIR = output

# Scenes and sample counts for generation
SCENES = cornell_box rectangular_light_scene reflective_floor
SAMPLES = 1 5 25 100

# Alvos principais
.PHONY: all basic reflective rectlight reflectivefloor clean generate_samples

# Alvo padrão
all: basic

# Cria diretórios necessários
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

# Alvo 'basic': compila e executa o cornell_box (800x600, 25 samples)
basic: $(BUILD_DIR) $(OUTPUT_DIR)
	@echo "Compilando Cornell Box..."
	$(CXX) $(CXXFLAGS) $(INC_DIR) $(SRC_DIR)/cornell_box.cpp -o $(BUILD_DIR)/cornell_box
	@echo "Executando o raytracer para Cornell Box..."
	cd $(BUILD_DIR) && ./cornell_box
	@echo "Movendo a imagem para o diretório de saída..."
	mv $(BUILD_DIR)/cornell_box_reference.ppm $(OUTPUT_DIR)/cornell_box_800x600_25samples.ppm
	@echo "Imagem salva como $(OUTPUT_DIR)/cornell_box_800x600_25samples.ppm"
	@if command -v convert >/dev/null 2>&1; then \
		echo "Convertendo PPM para PNG..."; \
		convert $(OUTPUT_DIR)/cornell_box_800x600_25samples.ppm $(OUTPUT_DIR)/cornell_box_800x600_25samples.png; \
		echo "Imagem convertida para $(OUTPUT_DIR)/cornell_box_800x600_25samples.png"; \
	else \
		echo "ImageMagick não encontrado. A imagem foi salva apenas no formato PPM."; \
	fi

# Alvo 'reflective': compila e executa a cena com a esfera reflexiva
reflective: $(BUILD_DIR) $(OUTPUT_DIR)
	@echo "Compilando cena com superfície reflexiva..."
	$(CXX) $(CXXFLAGS) $(INC_DIR) $(SRC_DIR)/reflective_scene.cpp -o $(BUILD_DIR)/reflective_scene
	@echo "Executando o raytracer para cena reflexiva..."
	cd $(BUILD_DIR) && ./reflective_scene
	@echo "Movendo a imagem para o diretório de saída..."
	mv $(BUILD_DIR)/reflective_scene.ppm $(OUTPUT_DIR)/reflective_scene.ppm
	@echo "Imagem salva como $(OUTPUT_DIR)/reflective_scene.ppm"
	@if command -v convert >/dev/null 2>&1; then \
		echo "Convertendo PPM para PNG..."; \
		convert $(OUTPUT_DIR)/reflective_scene.ppm $(OUTPUT_DIR)/reflective_scene.png; \
		echo "Imagem convertida para $(OUTPUT_DIR)/reflective_scene.png"; \
	else \
		echo "ImageMagick não encontrado. A imagem foi salva apenas no formato PPM."; \
	fi

# Alvo 'rectlight': compila e executa a Cornell Box com luz retangular
rectlight: $(BUILD_DIR) $(OUTPUT_DIR)
	@echo "Compilando Cornell Box com luz retangular..."
	$(CXX) $(CXXFLAGS) $(INC_DIR) $(SRC_DIR)/rectangular_light_scene.cpp -o $(BUILD_DIR)/rectangular_light_scene
	@echo "Executando o raytracer para Cornell Box com luz retangular..."
	cd $(BUILD_DIR) && ./rectangular_light_scene
	@echo "Movendo a imagem para o diretório de saída..."
	mv $(BUILD_DIR)/rectangular_light_scene.ppm $(OUTPUT_DIR)/cornell_box_rectlight.ppm
	@echo "Imagem salva como $(OUTPUT_DIR)/cornell_box_rectlight.ppm"
	@if command -v convert >/dev/null 2>&1; then \
		echo "Convertendo PPM para PNG..."; \
		convert $(OUTPUT_DIR)/cornell_box_rectlight.ppm $(OUTPUT_DIR)/cornell_box_rectlight.png; \
		echo "Imagem convertida para $(OUTPUT_DIR)/cornell_box_rectlight.png"; \
	else \
		echo "ImageMagick não encontrado. A imagem foi salva apenas no formato PPM."; \
	fi

# Alvo 'reflectivefloor': compila e executa a cena com piso reflexivo
reflectivefloor: $(BUILD_DIR) $(OUTPUT_DIR)
	@echo "Compilando cena com piso reflexivo..."
	$(CXX) $(CXXFLAGS) $(INC_DIR) $(SRC_DIR)/reflective_floor.cpp -o $(BUILD_DIR)/reflective_floor
	@echo "Executando o raytracer para cena com piso reflexivo..."
	cd $(BUILD_DIR) && ./reflective_floor
	@echo "Movendo a imagem para o diretório de saída..."
	mv $(BUILD_DIR)/reflective_floor_scene.ppm $(OUTPUT_DIR)/reflective_floor_scene.ppm
	@echo "Imagem salva como $(OUTPUT_DIR)/reflective_floor_scene.ppm"
	@if command -v convert >/dev/null 2>&1; then \
		echo "Convertendo PPM para PNG..."; \
		convert $(OUTPUT_DIR)/reflective_floor_scene.ppm $(OUTPUT_DIR)/reflective_floor_scene.png; \
		echo "Imagem convertida para $(OUTPUT_DIR)/reflective_floor_scene.png"; \
	else \
		echo "ImageMagick não encontrado. A imagem foi salva apenas no formato PPM."; \
	fi

# Alvo 'generate_samples': gera imagens com diferentes números de amostras para cenas selecionadas
# Calls the generate_scene_samples.sh script for each scene.
generate_samples: $(BUILD_DIR) $(OUTPUT_DIR)
	@echo "Gerando imagens com diferentes amostras via script..."
	@for scene in $(SCENES); do \
		echo "--- Running generation script for scene: $${scene} ---"; \
		./generate_scene_samples.sh $${scene}; \
		echo "--- Finished generation script for scene: $${scene} ---"; \
	done
	@echo "Geração de imagens concluída."

# Limpeza
clean:
	rm -rf $(BUILD_DIR)
	@echo "Diretório build limpo."

# Limpa apenas as imagens de saída
clean-images:
	rm -f $(OUTPUT_DIR)/*.ppm $(OUTPUT_DIR)/*.png
	@echo "Imagens removidas." 