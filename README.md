# Common Headers and Utilities

This directory contains shared header files and utility scripts used by both Week 3 and Week 5 implementations.

## Header Files

### Core Ray Tracing Headers
- **`vec3.h`** - 3D vector mathematics and operations
- **`ray.h`** - Ray class definition and basic ray operations
- **`camera.h`** - Camera class for view transformations
- **`color.h`** - Color utilities and gamma correction
- **`rtweekend.h`** - Common constants, utilities, and random number generation

### Geometry and Scene Headers
- **`hittable.h`** - Abstract base class for ray-hittable objects
- **`hittable_list.h`** - Container for managing multiple hittable objects
- **`sphere.h`** - Sphere geometry implementation
- **`sphere_simple.h`** - Simplified sphere for basic implementations
- **`hittable_simple.h`** - Simplified hittable interface

### Materials System (Week 5)
- **`material.h`** - Material base class and implementations (Lambertian, Metal, Dielectric)

## Utility Scripts

### Image Processing
- **`convert_to_bmp.py`** - Convert PPM images to BMP format
- **`ppm_viewer.py`** - Display PPM images in terminal with ASCII art representation

## Usage

Include the common headers in your ray tracer implementations:

```cpp
#include "../common/rtweekend.h"
#include "../common/camera.h"
#include "../common/color.h"
#include "../common/hittable_list.h"
#include "../common/sphere.h"
#include "../common/material.h"  // Week 5 only
```

## Building with Common Headers

When compiling from week3 or week5 directories:

```bash
# Include common directory in compilation
g++ -std=c++17 -O2 -I../common your_raytracer.cpp -o your_raytracer.exe
```

## Key Components

### Vec3 Class
- 3D vector operations (add, subtract, multiply, dot product, cross product)
- Point and color representation
- Utility functions for ray tracing mathematics

### Ray Class
- Ray representation with origin and direction
- Point-along-ray calculation: `point_at_parameter(t)`

### Camera Class
- View transformation setup
- Ray generation for each pixel
- Field of view and aspect ratio management

### Material System
- **Lambertian**: Diffuse reflection for matte surfaces
- **Metal**: Specular reflection with controllable fuzziness  
- **Dielectric**: Refraction and reflection for glass-like materials

### Utilities
- Random number generation
- Mathematical constants (π, infinity)
- Color space conversion and gamma correction

These components provide the foundation for both the basic Week 3 implementation and the advanced Week 5 materials system.
