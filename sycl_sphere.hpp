#ifndef SYCL_SPHERE_H
#define SYCL_SPHERE_H

#include "sycl_ray.hpp"
#include "sycl_vec3.hpp"

struct sycl_sphere {
    sycl_vec3 center;
    double radius;

    sycl_sphere() {}
    sycl_sphere(sycl_vec3 cen, double r) : center(cen), radius(r) {}

    bool hit(const sycl_ray& r, double t_min, double t_max, sycl_vec3& normal, double& t_hit) const {
        sycl_vec3 oc = r.origin() - center;
        auto a = r.direction().length_squared();
        auto half_b = dot(oc, r.direction());
        auto c = oc.length_squared() - radius*radius;

        auto discriminant = half_b*half_b - a*c;
        if (discriminant < 0) return false;
        auto sqrtd = cl::sycl::sqrt(discriminant);

        auto root = (-half_b - sqrtd) / a;
        if (root < t_min || t_max < root) {
            root = (-half_b + sqrtd) / a;
            if (root < t_min || t_max < root)
                return false;
        }

        t_hit = root;
        sycl_vec3 hit_point = r.at(t_hit);
        sycl_vec3 outward_normal = (hit_point - center) / radius;
        
        // Determine front face
        bool front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : (outward_normal * -1.0);

        return true;
    }
};

#endif
