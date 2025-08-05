#ifndef CONSTANT_MEDIUM_H
#define CONSTANT_MEDIUM_H

#include "hittable.h"
#include "material.h"
#include "texture.h"

class constant_medium : public hittable {
public:
    constant_medium(shared_ptr<hittable> boundary, double density, shared_ptr<texture> tex)
        : boundary(boundary), neg_inv_density(-1 / density),
        phase_function(make_shared<isotropic>(tex))
    {
    }

    constant_medium(shared_ptr<hittable> boundary, double density, const color& albedo)
        : boundary(boundary), neg_inv_density(-1 / density),
        phase_function(make_shared<isotropic>(albedo))
    {
    }

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        hit_record rec1, rec2;

        if (!boundary->hit(r, interval::universe, rec1))
            return false;

        if (!boundary->hit(r, interval(rec1.s + 0.0001, infinity), rec2))
            return false;

        if (rec1.s < ray_t.min) rec1.s = ray_t.min;
        if (rec2.s > ray_t.max) rec2.s = ray_t.max;

        if (rec1.s >= rec2.s)
            return false;

        if (rec1.s < 0)
            rec1.s = 0;

        auto ray_length = r.direction().length();
        auto distance_inside_boundary = (rec2.s - rec1.s) * ray_length;
        auto hit_distance = neg_inv_density * std::log(random_double());

        if (hit_distance > distance_inside_boundary)
            return false;

        rec.s = rec1.s + hit_distance / ray_length;
        rec.p = r.at(rec.s);

        rec.normal = vec3(1, 0, 0);
        rec.front_face = true;
        rec.mat = phase_function;

        return true;
    }

    aabb bounding_box() const override { return boundary->bounding_box(); }

private:
    shared_ptr<hittable> boundary;
    double neg_inv_density;
    shared_ptr<material> phase_function;
};

#endif