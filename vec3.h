// vec3.h
#pragma once
#include <cmath>
#include <iostream>

class Vec3 {
public:
    float x, y, z;

    // Constructor
    Vec3(float x_ = 0, float y_ = 0, float z_ = 0) : x(x_), y(y_), z(z_) {}

    // Operator overloads
    Vec3 operator+(const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
    Vec3 operator-(const Vec3& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
    Vec3 operator*(float s) const { return Vec3(x * s, y * s, z * s); }
    Vec3 operator/(float s) const { return Vec3(x / s, y / s, z / s); }
    Vec3 operator-() const { return Vec3(-x, -y, -z); }

    // Indexing
    float& operator[](int i) { return *((&x) + i); }
    const float& operator[](int i) const { return *((&x) + i); }

    // Methods
    float length() const { return std::sqrt(x * x + y * y + z * z); }
    Vec3 unit() const { float len = length(); return Vec3(x / len, y / len, z / len); }
    float dot(const Vec3& v) const { return x * v.x + y * v.y + z * v.z; }
    Vec3 cross(const Vec3& v) const {
        return Vec3(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        );
    }
    Vec3 reflect(const Vec3& normal) const {
        return *this - normal * 2.0f * this->dot(normal);
    }
    Vec3 refract(const Vec3& normal, float eta) const {
        float cosi = std::fmax(-1.0f, std::fmin(1.0f, this->dot(normal)));
        float etai = 1, etat = eta;
        Vec3 n = normal;
        if (cosi < 0) { cosi = -cosi; }
        else { std::swap(etai, etat); n = -normal; }
        float etaRatio = etai / etat;
        float k = 1 - etaRatio * etaRatio * (1 - cosi * cosi);
        return k < 0 ? Vec3(0,0,0) : *this * etaRatio + n * (etaRatio * cosi - std::sqrt(k));
    }
};

// Scalar multiplication from left
inline Vec3 operator*(float s, const Vec3& v) { return v * s; }

// For easy printing
inline std::ostream& operator<<(std::ostream& out, const Vec3& v) {
    return out << v.x << " " << v.y << " " << v.z;
}
