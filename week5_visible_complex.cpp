#include "rtweekend.h"
#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "material.h"

#include <iostream>
#include <fstream>
#include <memory>
#include <ctime>

Vec3 ray_color(const Ray& r, const Hittable& world, int depth) {
    HitRecord rec;

    if (depth <= 0)
        return Vec3(0, 0, 0);

    if (world.hit(r, 0.001f, infinity, rec)) {
        Ray scattered;
        Vec3 attenuation;
        if (rec.mat_ptr && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * ray_color(scattered, world, depth-1);
        }
        return Vec3(0, 0, 0);
    }

    Vec3 unit_direction = r.direction().unit();
    float t = 0.5f * (unit_direction.y + 1.0f);
    return (1.0f - t) * Vec3(1.0f, 1.0f, 1.0f) + t * Vec3(0.5f, 0.7f, 1.0f);
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    
    std::cout << "Creating visible complex scene..." << std::endl;

    const float aspect_ratio = 16.0f / 9.0f;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 10;
    const int max_depth = 20;

    HittableList world;

    try {
        auto ground_material = std::make_shared<Lambertian>(Vec3(0.5f, 0.5f, 0.5f));
        world.add(std::make_shared<Sphere>(Vec3(0, -1000, 0), 1000, ground_material.get()));

        int sphere_count = 0;
        for (int a = -4; a <= 4; a++) {
            for (int b = -4; b <= 4; b++) {
                if (abs(a) + abs(b) > 6) continue;
                
                Vec3 center(a * 0.8f + random_float(-0.2f, 0.2f), 0.2f, b * 0.8f + random_float(-0.2f, 0.2f));
                
                if ((center - Vec3(0, 1, 0)).length() > 1.5f && 
                    (center - Vec3(-3, 1, 0)).length() > 1.5f && 
                    (center - Vec3(3, 1, 0)).length() > 1.5f) {
                    
                    float choose_mat = random_float();
                    std::shared_ptr<Material> sphere_material;

                    if (choose_mat < 0.6f) {
                        Vec3 albedo = Vec3(random_float(0.4f, 0.9f), random_float(0.4f, 0.9f), random_float(0.4f, 0.9f));
                        sphere_material = std::make_shared<Lambertian>(albedo);
                    } else if (choose_mat < 0.85f) {
                        Vec3 albedo = Vec3(random_float(0.6f, 1), random_float(0.6f, 1), random_float(0.6f, 1));
                        float fuzz = random_float(0, 0.3f);
                        sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    } else {
                        sphere_material = std::make_shared<Dielectric>(1.5f);
                    }
                    
                    world.add(std::make_shared<Sphere>(center, 0.2f, sphere_material.get()));
                    sphere_count++;
                }
            }
        }

        auto glass_material = std::make_shared<Dielectric>(1.5f);
        world.add(std::make_shared<Sphere>(Vec3(0, 1, 0), 1.0f, glass_material.get()));

        auto red_material = std::make_shared<Lambertian>(Vec3(0.8f, 0.2f, 0.2f));
        world.add(std::make_shared<Sphere>(Vec3(-3, 1, 0), 1.0f, red_material.get()));

        auto metal_material = std::make_shared<Metal>(Vec3(0.9f, 0.9f, 1.0f), 0.0f);
        world.add(std::make_shared<Sphere>(Vec3(3, 1, 0), 1.0f, metal_material.get()));

        std::cout << "Scene created with " << world.objects.size() << " objects" << std::endl;
        std::cout << "Small spheres: " << sphere_count << std::endl;

        Vec3 lookfrom(6, 3, 6);
        Vec3 lookat(0, 0, 0);
        Vec3 vup(0, 1, 0);
        Camera cam(lookfrom, lookat, vup, 40, aspect_ratio);

        std::cout << "Camera at (" << lookfrom.x << ", " << lookfrom.y << ", " << lookfrom.z << ")" << std::endl;

        std::ofstream file("week5_materials_scene.ppm");
        if (!file.is_open()) {
            std::cerr << "ERROR: Could not open output file!" << std::endl;
            return 1;
        }

        file << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        std::cout << "Rendering..." << std::endl;

        for (int j = image_height - 1; j >= 0; --j) {
            if (j % 25 == 0) {
                std::cout << "Scanlines remaining: " << j << std::endl;
            }
            
            for (int i = 0; i < image_width; ++i) {
                Vec3 pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s) {
                    float u = (i + random_float()) / (image_width - 1);
                    float v = (j + random_float()) / (image_height - 1);
                    Ray r = cam.get_ray(u, v);
                    pixel_color = pixel_color + ray_color(r, world, max_depth);
                }
                write_color(file, pixel_color, samples_per_pixel);
            }
        }

        file.close();
        std::cout << "Complex scene render complete!" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
