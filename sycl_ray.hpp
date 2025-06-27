#ifndef SYCL_RAY_H
#define SYCL_RAY_H

#include "sycl_vec3.hpp"

struct sycl_ray {
    sycl_vec3 orig;
    sycl_vec3 dir;

    sycl_ray() {}
    sycl_ray(const sycl_vec3& origin, const sycl_vec3& direction)
        : orig(origin), dir(direction) {}

    sycl_vec3 origin() const  { return orig; }
    sycl_vec3 direction() const { return dir; }

    sycl_vec3 at(double t) const {
        return orig + t*dir;
    }
};

#endif
