#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>
#include <algorithm>

using color = vec3;

inline void write_color(std::ostream& out, const color& pixel_color) {
    auto r = std::clamp(pixel_color.x(), 0.0, 1.0);
    auto g = std::clamp(pixel_color.y(), 0.0, 1.0);
    auto b = std::clamp(pixel_color.z(), 0.0, 1.0);

    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif