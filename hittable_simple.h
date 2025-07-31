#ifndef HITTABLE_SIMPLE_H
#define HITTABLE_SIMPLE_H

#include "ray.h"
#include "vec3.h"

struct HitRecordSimple {
    float t;
    Vec3 p;
    Vec3 normal;
    bool front_face;

    inline void set_face_normal(const Ray& r, const Vec3& outward_normal) {
        front_face = r.direction().dot(outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class HittableSimple {
public:
    virtual bool hit(const Ray& r, float t_min, float t_max, HitRecordSimple& rec) const = 0;
    virtual ~HittableSimple() = default;
};

#endif
