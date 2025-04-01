#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <fstream>
#include <string>
#include "Color.h"

class Image {
public:
    Image(int width, int height)
        : width(width), height(height), data(width * height) {}

    void set_pixel(int x, int y, const Color& color) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            data[y * width + x] = color;
        }
    }

    Color get_pixel(int x, int y) const {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            return data[y * width + x];
        }
        return Color(0, 0, 0);
    }

    void save_ppm(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file) {
            return;
        }

        file << "P3\n" << width << " " << height << "\n255\n";
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                get_pixel(x, y).write_color(file);
            }
        }
        file.close();
    }

    int get_width() const { return width; }
    int get_height() const { return height; }

private:
    int width;
    int height;
    std::vector<Color> data;
};

#endif 