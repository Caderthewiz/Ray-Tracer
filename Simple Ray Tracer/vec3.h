#ifndef VEC3_H
#define VEC3_H

#include "utility.h"

class vec3 {
	public:
		double elements[3];

		vec3() : elements{ 0, 0, 0 } {}
		vec3(double x, double y, double z) : elements{ x, y, z } {}

		double x() const { return elements[0]; }
		double y() const { return elements[1]; }
		double z() const { return elements[2]; }

		//Operator Overloading
		vec3 operator-() const { return vec3(-elements[0], -elements[1], -elements[2]); }
		double operator[](int i) const { return elements[i]; }
		double& operator[](int i) { return elements[i]; }

		vec3& operator+=(const vec3& v) {
			elements[0] += v.elements[0];
			elements[1] += v.elements[1];
			elements[2] += v.elements[2];
			return *this;
		}

		vec3& operator*=(double s) {
			elements[0] *= s;
			elements[1] *= s;
			elements[2] *= s;
			return *this;
		}

		vec3& operator/=(double s) {
			return *this *= 1/s;
		}


		double length() const {
			return std::sqrt(length_squared());
		}

		double length_squared() const {
			return elements[0] * elements[0] + elements[1] * elements[1] + elements[2] * elements[2];
		}

		bool near_zero() const {
			auto s = 1e-8;
			return (fabs(elements[0]) < s) && (fabs(elements[1]) < s) && (fabs(elements[2]) < s);
		}

		static vec3 random() {
			return vec3(random_double(), random_double(), random_double());
		}

		static vec3 random(double min, double max) {
			return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
		}
};

using point3 = vec3; //Alias to represent point as vec

//Vec Utilitiy Funcitons

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
	return out << v.elements[0] << ' ' << v.elements[1] << ' ' << v.elements[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
	return vec3(u.elements[0] + v.elements[0], u.elements[1] + v.elements[1], u.elements[2] + v.elements[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v) {
	return vec3(u.elements[0] - v.elements[0], u.elements[1] - v.elements[1], u.elements[2] - v.elements[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v) {
	return vec3(u.elements[0] * v.elements[0], u.elements[1] * v.elements[1], u.elements[2] * v.elements[2]);
}

inline vec3 operator*(double s, const vec3& v) {
	return vec3(s * v.elements[0], s * v.elements[1], s * v.elements[2]);
}

inline vec3 operator*(const vec3& v, double s) {
	return s * v;
}

inline vec3 operator/(const vec3& v, double s) {
	return (1 / s) * v;
}

inline double dot(const vec3& u, const vec3& v) {
	return u.elements[0] * v.elements[0] + u.elements[1] * v.elements[1] + u.elements[2] * v.elements[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
	return vec3(u.elements[1] * v.elements[2] - u.elements[2] * v.elements[1],
				 u.elements[2] * v.elements[0] - u.elements[0] * v.elements[2],
				 u.elements[0] * v.elements[1] - u.elements[1] * v.elements[0]);
}

inline vec3 unit_vector(const vec3& v) {
	return v / v.length();
}

inline vec3 random_in_unit_disk() {
	while (true) {
		auto p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
		if (p.length_squared() < 1)
			return p;
	}
}

//Generates a random unit vector
inline vec3 random_unit_vector() {
	while (true)
	{
		auto p = vec3::random(-1, 1);
		auto lensq = p.length_squared();
		if (1e-160 < lensq && lensq <= 1) //Prevents underflow to zero
			return p / sqrt(lensq);
	}
}

//Ensures the random vector is on the hemisphere defined by the normal 
inline vec3 random_on_hemisphere(const vec3& normal) {
	vec3 on_unit_sphere = random_unit_vector();
	if (dot(on_unit_sphere, normal) > 0.0)
		return on_unit_sphere;
	else
		return -on_unit_sphere;
}

inline vec3 reflect(const vec3& v, const vec3& n) {
	return v - 2 * dot(v, n) * n;
}

/* Refraction using Snell's law
* 
* eta * sin(theta) = eta' * sin(theta')
* => sin(theta') = (eta / eta') * sin(theta)
* 
* R'_perp = (eta / eta') * (R + |R|cos(theta) * n)
* R'_para = -sqrt(1 - |R'_perp|^2) * n
* 
* a . b = |a| * |b| * cos(theta)
* 
* => R'_perp = (eta / eta') * (R + (-R . n) * n)
*/
inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
	auto cos_theta = std::fmin(dot(-uv, n), 1.0);
	vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
	vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
	return r_out_perp + r_out_parallel;
}

inline vec3 random_cosine_direction() {
	auto r1 = random_double();
	auto r2 = random_double();

	auto phi = 2 * pi * r1;
	auto x = std::cos(phi) * std::sqrt(r2);
	auto y = std::sin(phi) * std::sqrt(r2);
	auto z = std::sqrt(1 - r2);
	
	return vec3(x, y, z);
}

#endif