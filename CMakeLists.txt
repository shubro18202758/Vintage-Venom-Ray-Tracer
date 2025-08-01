cmake_minimum_required(VERSION 3.16)
project(RayTracingSYCL)

set(CMAKE_CXX_STANDARD 17)

# Find SYCL
find_package(IntelSYCL REQUIRED)

# CPU version
add_executable(raytracer_cpu main.cpp)

# SYCL GPU version
add_executable(raytracer_sycl sycl_raytracer.cpp)
add_sycl_to_target(TARGET raytracer_sycl SOURCES sycl_raytracer.cpp)
