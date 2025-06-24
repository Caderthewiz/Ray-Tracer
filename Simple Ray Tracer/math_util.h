#ifndef MATH_UTIL_H
#define MATH_UTIL_H

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>

using std::make_shared;
using std::shared_ptr;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) {
	return degrees * pi / 180.0;
}

inline double random_double() {
	return rand() / (RAND_MAX + 1.0);
}

//Common Headers
#include "color.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"

#endif