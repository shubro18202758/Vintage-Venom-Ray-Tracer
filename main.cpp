// main.cpp
#include <iostream>
#include <fstream>

int main() {
    const int width = 256;
    const int height = 256;

    std::ofstream ofs("output.ppm");
    ofs << "P3\n" << width << " " << height << "\n255\n";

    for (int j = height - 1; j >= 0; --j) {
        for (int i = 0; i < width; ++i) {
            float r = float(i) / (width - 1);
            float g = float(j) / (height - 1);
            float b = 0.25f;
            int ir = static_cast<int>(255.99 * r);
            int ig = static_cast<int>(255.99 * g);
            int ib = static_cast<int>(255.99 * b);
            ofs << ir << " " << ig << " " << ib << "\n";
        }
    }
    ofs.close();
    std::cout << "Wrote output.ppm\n";
    return 0;
}
