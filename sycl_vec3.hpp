#ifndef SYCL_VEC3_H
#define SYCL_VEC3_H

#include <CL/sycl.hpp>

struct sycl_vec3 {
    double e[3];

    sycl_vec3() : e{0,0,0} {}
    sycl_vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    sycl_vec3 operator-() const { return sycl_vec3(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }

    sycl_vec3 operator+(const sycl_vec3 &v) const {
        return sycl_vec3(e[0] + v.e[0], e[1] + v.e[1], e[2] + v.e[2]);
    }

    sycl_vec3 operator-(const sycl_vec3 &v) const {
        return sycl_vec3(e[0] - v.e[0], e[1] - v.e[1], e[2] - v.e[2]);
    }

    sycl_vec3 operator*(double t) const {
        return sycl_vec3(t*e[0], t*e[1], t*e[2]);
    }

    sycl_vec3 operator/(double t) const {
        return sycl_vec3(e[0]/t, e[1]/t, e[2]/t);
    }

    double length() const {
        return cl::sycl::sqrt(length_squared());
    }

    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }
};

inline double dot(const sycl_vec3 &u, const sycl_vec3 &v) {
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline sycl_vec3 operator*(double t, const sycl_vec3 &v) {
    return sycl_vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline sycl_vec3 unit_vector(sycl_vec3 v) {
    return v / v.length();
}

#endif
