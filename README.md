# Vintage-Venom-Ray-Tracer
Gpu Based Ray Tracer...

🧪 Week 3: Ray Tracing Core, SYCL Fundamentals & GPU Acceleration — Here is a Journal of what I have learnt...
This week marked a significant step forward: I not only deepened my understanding of ray tracing by exploring complex scenes and surface interactions, but also took my first leap into parallel programming with SYCL to utilize GPU acceleration. Here’s a tabular type breakdown of what I tackled:

🔬 Ray Tracing in One Weekend — Chapters 4 to 6.8
I advanced through major milestones in the book:
- 🟦 Chapter 4: Rays & Camera Basics
I implemented a basic ray class and learned to generate rays based on viewport dimensions, direction, and a virtual camera.
- 🔵 Chapter 5: Adding a Sphere
I wrote logic for ray-sphere intersection and created my first ray-traced image. Seeing the theoretical math produce a renderable result was extremely rewarding.
- 🟩 Chapter 6: Surface Normals & Scene Composition
I added surface normal shading, abstracted sphere logic using a Hittable interface, and supported scenes with multiple objects. I also explored:
- Detecting front vs. back face hits
- Cleaner, modularized code for geometry
- Basic scene utility functions and constants
This was the week where things began to feel like a real renderer taking shape.

⚙️ Diving into SYCL
To parallelize rendering, I learned the fundamentals of SYCL, focusing on Intel’s DPC++ ecosystem. I worked through both written tutorials and select video resources.
Key Concepts I Covered:
i) SYCL’s queue, device, and buffer abstractions
ii) Launching parallel tasks using parallel_for
iii) Managing memory safely with sycl::buffer and sycl::accessor
iv) Device selection strategies and the SYCL memory model
It was fascinating to see how SYCL abstracts the complexity of heterogeneous computing into a unified model.

⚡ Porting Sphere Renderer to SYCL...(kinda a hell go-through btw)
I rewrote my CPU-based sphere renderer to run on a SYCL device:
- Refactored the ray-sphere intersection logic into a SYCL kernel
- Used SYCL buffers to manage the output pixel array in device memory
- Generated a .ppm image using parallel pixel computation on the GPU
The GPU speedup was noticeable even at this basic stage—and a great demonstration of how ray tracing fits naturally with data-parallel workloads.

🚀 Takeaway -~~ :)
This week was all about depth and acceleration. I strengthened my mathematical and architectural foundation for ray tracing while simultaneously introducing GPU acceleration using modern, vendor-neutral tools. It’s exciting to see real-time rendering performance ramp up through parallelism.


