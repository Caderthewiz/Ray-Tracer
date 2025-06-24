#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "vec3.h"
#include "math_util.h"

using color = vec3;

void write_color(std::ostream& out, color& pixel_color) {
	double r = pixel_color.x();
	double g = pixel_color.y();
	double b = pixel_color.z();

	//Tranlation
	static const interval intensity(0.000, 0.999);
	int rbyte = int(256 * intensity.clamp(r));
	int gbyte = int(256 * intensity.clamp(g));
	int bbyte = int(256 * intensity.clamp(b));

	//Write
	out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif