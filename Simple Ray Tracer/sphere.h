#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "utility.h"

/* Math Breakdowns
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
* 
* Texture Cords to Spheres
* u = phi / 2pi
* v = theta / pi
* y = -cos(theta)
* x = - cos(phi) * sin(theta)
* z = sin(phi) * sin(theta)
* 
* phi = atan2(z, x) + pi [0, 2pi]
* theta = arccos(-y)
*/

class sphere : public hittable {
	public:
        //Stationary
        sphere(const point3& static_center, double radius, shared_ptr<material> mat) : center(static_center, vec3(0, 0, 0)), radius(std::fmax(0, radius)), mat(mat)
        {
			auto rvec = vec3(radius, radius, radius);
			bbox = aabb(static_center - rvec, static_center + rvec);
        }

        //Moving
        sphere(const point3& center1, const point3& center2, double radius, shared_ptr<material> mat) : center(center1, center2 - center1), radius(std::fmax(0, radius)), mat(mat)
        {
			auto rvec = vec3(radius, radius, radius);
			aabb box1(center.at(0) - rvec, center.at(0) + rvec);
            aabb box2(center.at(1) - rvec, center.at(1) + rvec);
            bbox = aabb(box1, box2);
        }

        //Intersection Alg
        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            point3 current_center = center.at(r.time());
            vec3 oc = current_center - r.origin();
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
			vec3 outward_normal = (rec.p - current_center) / radius; //Unit length
			rec.set_face_normal(r, outward_normal);
            get_sphere_uv(outward_normal, rec.u, rec.v);
            rec.mat = mat;

            return true;
        }

        aabb bounding_box() const override { return bbox; }

	private:
		ray center;
		double radius;
		shared_ptr<material> mat;
        aabb bbox;

        static void get_sphere_uv(const point3& p, double& u, double& v) {
            auto theta = std::acos(-p.y());
            auto phi = std::atan2(-p.z(), p.x()) + pi;

			u = phi / (2 * pi);
			v = theta / pi;
        }
};

#endif