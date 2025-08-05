#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable.h"
#include "texture.h"

class material {
	public:
		virtual ~material() = default; //Deconstructor

		virtual color emitted(double u, double v, const point3& p) const {
			return color(0, 0, 0);
		}

		virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
			return false;
		}
};

//Diffuse Material
class lambertian : public material {
	public:
		lambertian(const color& albedo) : tex(make_shared<solid_color>(albedo)) {}
		lambertian(shared_ptr<texture> tex) : tex(tex) {}

		//Lambertian Scattering

		bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
			auto scatter_direction = rec.normal + random_unit_vector(); //Scatter in a random direction based on the normal

			//Catch degenerate scatter direction
			if (scatter_direction.near_zero()) {
				scatter_direction = rec.normal;
			}

			scattered = ray(rec.p, scatter_direction, r_in.time());
			attenuation = tex->value(rec.u, rec.v, rec.p);
			return true;
		}

	private:
		shared_ptr<texture> tex;
};

//Metal Material
class metal : public material {
	public:
		metal(const color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

		bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
			vec3 reflected = reflect(r_in.direction(), rec.normal); //Reflect the incoming ray based on the normal
			reflected = unit_vector(reflected) + (fuzz * random_unit_vector()); //Fuzz the reflection
			scattered = ray(rec.p, reflected, r_in.time());
			attenuation = albedo;
			return (dot(scattered.direction(), rec.normal) > 0);
		}

	private:
		color albedo;
		double fuzz;
};

//Dielectric Material (Glass)
class dielectric : public material {
	public:
		dielectric(double refraction_index) : refraction_index(refraction_index) {}

		bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override {
			attenuation = color(1.0, 1.0, 1.0);
			double ri = rec.front_face ? (1.0 / refraction_index) : refraction_index;

			vec3 unit_direction = unit_vector(r_in.direction());

			//Total Internal Reflection Check
			double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
			double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

			bool cannot_refract = ri * sin_theta > 1.0;
			vec3 direction;

			if (cannot_refract || reflectance(cos_theta, ri) > random_double())
				direction = reflect(unit_direction, rec.normal);
			else
				direction = refract(unit_direction, rec.normal, ri);

			scattered = ray(rec.p, direction, r_in.time());
			return true;
		}

	private:
		double refraction_index;

		//Schlick's approximation for reflectance
		static double reflectance(double cosine, double ref_idx) {
			double r0 = (1 - ref_idx) / (1 + ref_idx);
			r0 = r0 * r0;
			return r0 + (1 - r0) * std::pow((1 - cosine), 5);
		}
};

class diffuse_light : public material {
	public:
		diffuse_light(shared_ptr<texture> tex) : tex(tex) {}
		diffuse_light(const color& emit) : tex(make_shared<solid_color>(emit)) {}

		color emitted(double u, double v, const vec3& p) const override {
			return tex->value(u, v, p);
		}

	private:
		shared_ptr<texture> tex;
};

class isotropic : public material {
public:
	isotropic(const color& albedo) : tex(make_shared<solid_color>(albedo)) {}
	isotropic(shared_ptr<texture> tex) : tex(tex) {}

	bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered)
		const override {
		scattered = ray(rec.p, random_unit_vector(), r_in.time());
		attenuation = tex->value(rec.u, rec.v, rec.p);
		return true;
	}

private:
	shared_ptr<texture> tex;
};

#endif