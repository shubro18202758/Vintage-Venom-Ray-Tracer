CXX = dpcpp
CXXFLAGS = -std=c++17 -O3

# Targets
all: raytracer_cpu raytracer_sycl

raytracer_cpu: main.cpp
	g++ $(CXXFLAGS) -o raytracer_cpu main.cpp

raytracer_sycl: sycl_raytracer.cpp
	$(CXX) $(CXXFLAGS) -o raytracer_sycl sycl_raytracer.cpp

clean:
	rm -f raytracer_cpu raytracer_sycl output.ppm

run_cpu: raytracer_cpu
	./raytracer_cpu > output_cpu.ppm

run_sycl: raytracer_sycl
	./raytracer_sycl

.PHONY: all clean run_cpu run_sycl
