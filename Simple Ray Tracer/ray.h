#ifndef RAY_H
#define RAY_H

#include "vec3.h"

//Ray (Vector) = P(t) = A + t*b

class ray {
	public:
		ray() {}
		ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

		const point3& origin() const { return orig; }
		const vec3& direction() const { return dir; }

		point3 at(double s) const { // s -> scalar value
			return orig + s * dir;
		}
	
	private:
		point3 orig; //A
		vec3 dir; //b
};

#endif