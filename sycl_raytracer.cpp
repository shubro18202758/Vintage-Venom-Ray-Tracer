#include <sycl/sycl.hpp>
#include <iostream>
#include <fstream>
#include <vector>

using namespace sycl;

// SYCL-compatible vector class
struct vec3_sycl {
    double e[3];

    vec3_sycl() : e{0,0,0} {}
    vec3_sycl(double e0, double e1, double e2) : e{e0, e1, e2} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    vec3_sycl operator+(const vec3_sycl &v) const {
        return vec3_sycl(e[0] + v.e[0], e[1] + v.e[1], e[2] + v.e[2]);
    }

    vec3_sycl operator-(const vec3_sycl &v) const {
        return vec3_sycl(e[0] - v.e[0], e[1] - v.e[1], e[2] - v.e[2]);
    }

    vec3_sycl operator*(double t) const {
        return vec3_sycl(t*e[0], t*e[1], t*e[2]);
    }

    vec3_sycl operator/(double t) const {
        return vec3_sycl(e[0]/t, e[1]/t, e[2]/t);
    }

    double length() const {
        return sycl::sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
    }

    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }
};

inline double dot(const vec3_sycl &u, const vec3_sycl &v) {
    return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

inline vec3_sycl operator*(double t, const vec3_sycl &v) {
    return vec3_sycl(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3_sycl unit_vector(vec3_sycl v) {
    return v / v.length();
}

// SYCL-compatible ray class
struct ray_sycl {
    vec3_sycl orig;
    vec3_sycl dir;

    ray_sycl() {}
    ray_sycl(const vec3_sycl& origin, const vec3_sycl& direction)
        : orig(origin), dir(direction) {}

    vec3_sycl origin() const  { return orig; }
    vec3_sycl direction() const { return dir; }

    vec3_sycl at(double t) const {
        return orig + t*dir;
    }
};

// SYCL-compatible sphere class
struct sphere_sycl {
    vec3_sycl center;
    double radius;

    sphere_sycl() {}
    sphere_sycl(vec3_sycl cen, double r) : center(cen), radius(r) {}

    bool hit(const ray_sycl& r, double t_min, double t_max, vec3_sycl& normal, double& t_hit) const {
        vec3_sycl oc = r.origin() - center;
        auto a = r.direction().length_squared();
        auto half_b = dot(oc, r.direction());
        auto c = oc.length_squared() - radius*radius;

        auto discriminant = half_b*half_b - a*c;
        if (discriminant < 0) return false;
        auto sqrtd = sycl::sqrt(discriminant);

        auto root = (-half_b - sqrtd) / a;
        if (root < t_min || t_max < root) {
            root = (-half_b + sqrtd) / a;
            if (root < t_min || t_max < root)
                return false;
        }

        t_hit = root;
        vec3_sycl hit_point = r.at(t_hit);
        vec3_sycl outward_normal = (hit_point - center) / radius;
        
        // Determine front face
        bool front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : (outward_normal * -1.0);

        return true;
    }
};

// Ray color function for SYCL kernel
vec3_sycl ray_color_sycl(const ray_sycl& r, const sphere_sycl* spheres, int num_spheres) {
    double closest_t = 1e30;
    bool hit_anything = false;
    vec3_sycl final_normal;
    
    for (int i = 0; i < num_spheres; i++) {
        vec3_sycl normal;
        double t_hit;
        if (spheres[i].hit(r, 0.001, closest_t, normal, t_hit)) {
            hit_anything = true;
            closest_t = t_hit;
            final_normal = normal;
        }
    }
    
    if (hit_anything) {
        return 0.5 * (final_normal + vec3_sycl(1,1,1));
    }
    
    vec3_sycl unit_direction = unit_vector(r.direction());
    double t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0-t) * vec3_sycl(1.0, 1.0, 1.0) + t * vec3_sycl(0.5, 0.7, 1.0);
}

int main() {
    // Image dimensions
    const int image_width = 800;
    const int image_height = 400;
    const double aspect_ratio = double(image_width) / double(image_height);
    
    // Camera setup
    const double viewport_height = 2.0;
    const double viewport_width = aspect_ratio * viewport_height;
    const double focal_length = 1.0;
    
    const vec3_sycl origin(0, 0, 0);
    const vec3_sycl horizontal(viewport_width, 0, 0);
    const vec3_sycl vertical(0, viewport_height, 0);
    const vec3_sycl lower_left_corner = origin - horizontal/2 - vertical/2 - vec3_sycl(0, 0, focal_length);
    
    // Create world with spheres - Fixed: Use array instead of vector
    sphere_sycl host_spheres[2];
    host_spheres[0] = sphere_sycl(vec3_sycl(0, 0, -1), 0.5);
    host_spheres[1] = sphere_sycl(vec3_sycl(0, -100.5, -1), 100);
    const int num_spheres = 2;
    
    // Output image buffer
    std::vector<vec3_sycl> image_data(image_width * image_height);
    
    try {
        // Create SYCL queue - Fixed: Use modern SYCL 2020 syntax
        queue q(gpu_selector_v);
        std::cout << "Running on device: " << q.get_device().get_info<info::device::name>() << std::endl;
        
        // Create buffers - Fixed: Use array instead of vector
        buffer<sphere_sycl, 1> spheres_buf(host_spheres, range<1>(num_spheres));
        buffer<vec3_sycl, 1> image_buf(image_data.data(), range<1>(image_data.size()));
        
        // Submit kernel
        q.submit([&](handler& h) {
            auto spheres_acc = spheres_buf.get_access<access::mode::read>(h);
            auto image_acc = image_buf.get_access<access::mode::write>(h);
            
            h.parallel_for<class raytracer_kernel>(
                range<2>(image_width, image_height),
                [=](id<2> idx) {
                    int i = idx[0];
                    int j = idx[1];
                    
                    double u = double(i) / (image_width - 1);
                    double v = double(j) / (image_height - 1);
                    
                    vec3_sycl ray_dir = lower_left_corner + u * horizontal + v * vertical - origin;
                    ray_sycl r(origin, ray_dir);
                    
                    // Fixed: Use get_multi_ptr() instead of deprecated get_pointer()
                    vec3_sycl color = ray_color_sycl(r, spheres_acc.get_multi_ptr<access::decorated::no>().get(), num_spheres);
                    
                    int pixel_idx = (image_height - 1 - j) * image_width + i;
                    image_acc[pixel_idx] = color;
                }
            );
        });
        
        q.wait();
        
    } catch (exception const& e) {
        std::cout << "SYCL exception caught: " << e.what() << std::endl;
        return 1;
    }
    
    // Write PPM file
    std::ofstream file("output.ppm");
    file << "P3\n" << image_width << " " << image_height << "\n255\n";
    
    for (const auto& pixel : image_data) {
        int r = static_cast<int>(255.999 * pixel.x());
        int g = static_cast<int>(255.999 * pixel.y());
        int b = static_cast<int>(255.999 * pixel.z());
        
        // Clamp values
        r = (r > 255) ? 255 : (r < 0) ? 0 : r;
        g = (g > 255) ? 255 : (g < 0) ? 0 : g;
        b = (b > 255) ? 255 : (b < 0) ? 0 : b;
        
        file << r << " " << g << " " << b << "\n";
    }
    
    file.close();
    std::cout << "Image saved as output.ppm" << std::endl;
    
    return 0;
}
