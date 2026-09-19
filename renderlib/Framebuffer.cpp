#include "Framebuffer.h"
#include "png++/png.hpp"

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


            //vec3 color = fb[flipped_j*width + 1]
            vec3 color = fb[j*width + i];

            png::byte r = static_cast<png::byte>(color.x() * 255.0);
            png::byte g = static_cast<png::byte>(color.y() * 255.0); 
            png::byte b = static_cast<png::byte>(color.z() * 255.0);

            imData[j][i] = png::rgb_pixel(r, g, b);
        }    
    }

    imData.write(filename);
}