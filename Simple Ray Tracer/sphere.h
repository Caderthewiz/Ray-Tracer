#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "utility.h"

/* Math Breakdown
* 
* Sphere -> x^2 + y^2 + z^2 = r^2
* Arbitary Sphere Center -> (Cx, Cy, Cz)
* P = (x, y, z) point on the sphere
* (C - P) = radius
* P(t) = Q + td
* 
* => (Cx - x)^2 + (Cy - y)^2 + (Cz - z)^2 = r^2
* => (C - P) . (C - P) = r^2
* => (C - (Q + td)) . (C - (Q + td)) = r^2
* => t^2(d . d) - 2td . (C - Q) + (C - Q) . (C - Q) - r^2 = 0
* 
* a = d . d
* b = -2d . (C - Q)
* c = (C - Q) . (C - Q) - r^2
* 
* b = -2h
* h = d . (C - Q)
*/

class sphere : public hittable {
	public:
		sphere(const point3& center, double radius, shared_ptr<material> mat) : center(center), radius(std::fmax(0, radius)), mat(mat) {}

        //Intersection Alg
        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            vec3 oc = center - r.origin();
            auto a = r.direction().length_squared();
            auto h = dot(r.direction(), oc);
            auto c = oc.length_squared() - radius * radius;

            auto discriminant = h * h - a * c;
			if (discriminant < 0) // No intersection
                return false;

			//Checking if root is within the interval
            auto sqrtd = std::sqrt(discriminant);
            auto root = (h - sqrtd) / a;
            if (!ray_t.surrounds(root)) {
                root = (h + sqrtd) / a;
                if (!ray_t.surrounds(root))
                    return false;
            }

            rec.s = root;
            rec.p = r.at(rec.s);
			vec3 outward_normal = (rec.p - center) / radius; //Unit length
			rec.set_face_normal(r, outward_normal);
            rec.mat = mat;

            return true;
        }

	private:
		point3 center;
		double radius;
		shared_ptr<material> mat;
};

#endif