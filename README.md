# Vintage-Venom-Ray-Tracer
Gpu Based Ray Tracer...

📘 Week 1: Vec3, Makefiles & Mathematical Foundations — Here's what have I learnt...
In the first week of diving into ray tracing, I laid the groundwork by focusing on essential math concepts, building my first utility class, and understanding the basics of project compilation.

🧠 Math Behind Ray Tracing
I explored the fundamental role vector math plays in ray tracing. I studied how rays are represented mathematically and how vectors help simulate physical behavior like reflection and refraction. Concepts such as the dot product, cross product, and normalization really clicked for me this week. These aren’t just formulas—they’re the math that powers how light moves and interacts in a rendered scene.

🔧 Building the Vec3 Class
I implemented a custom Vec3 class in C++ to represent 3D vectors. It includes:
i) A constructor to initialize vector components
ii) Operator overloads for common operations: +, -, *, /, indexing [], and unary -
iii) Useful methods like unit(), length(), dot(), cross(), reflect(), and refract()
Writing these from scratch gave me a deeper appreciation for how abstract math translates into usable code.

🛠️ Makefile – Automating the Build
I created a basic Makefile that compiles my vec3.h and main.cpp files into an executable. It supports:
Make for building the project & make clean for cleaning up object files
Learning to automate builds using Make gave me a glimpse of how professional projects manage complexity.

🎨 First Rendered Output (.ppm)
I wrapped up the week by generating my first image file using the .ppm format, applying simple color interpolation to create a vertical gradient. Although I didn’t use the Vec3 class for this part, it was satisfying to see my code produce visual output.

🏁 Takeaway -~~ :)
This week gave me a strong foundation in both the math and tooling behind ray tracing. I feel more confident now stepping into topics like ray-object intersections, materials, and rendering loops.



