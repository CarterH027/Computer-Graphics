#include "Framebuffer.h"
#include "png++/png.hpp"

#include <algorithm>

Framebuffer::Framebuffer() : width(100), height(100), fb(width * height) {}

Framebuffer::Framebuffer(int width, int height) : width(width), height(height), fb(width * height) {}

void Framebuffer::clearToColor(const color &c){
    for (auto idx = 0; idx < fb.size(); idx++) {
        setPixelColor(idx, c);
    }
}

void Framebuffer::clearToGradient(const color &c1, const color &c2) {
    for (auto x = 0; x < width; x++) {
        for (auto y = 0; y < height; y++) {
            auto t = double(y) / (height); 

            color c = (1-t) * c1 + t *c2;

            setPixelColor(x, y, c);
        }
    }
}

void Framebuffer::setPixelColor(int i, int j, const color &c){
    fb[j * width + i] = c;
}

void Framebuffer::setPixelColor(int idx, const color &c){
    fb[idx] = c; 
}

void Framebuffer::exportToPNG(const std::string &filename){
    png::image<png::rgb_pixel> imData(width,height);

    for (int j = 0; j < height ; j++) {
        for (int i = 0; i < width; i++){
            int flipped_j = (height-1) -j;


            //vec3 color = fb[flipped_j*width + 1];
            vec3 color = fb[j*width + i];

            double clamped_r = std::clamp(color.x(), 0.0, 1.0);
            double clamped_g = std::clamp(color.y(), 0.0, 1.0);
            double clamped_b = std::clamp(color.z(), 0.0, 1.0);


            png::byte r = static_cast<png::byte>(clamped_r * 255.0);
            png::byte g = static_cast<png::byte>(clamped_g * 255.0); 
            png::byte b = static_cast<png::byte>(clamped_b * 255.0);

            imData[flipped_j][i] = png::rgb_pixel(r, g, b);
        }    
    }

    imData.write(filename);
}