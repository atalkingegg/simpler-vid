# simpler-vid
Some Arducam derived code to test out some libcamera video features.

# The No-OpenCV libcamera video demo
Demonstrates how fast a camera can go without display or image processing getting in the way.

# The Arducam C++ libcamera opencv demo
Based on the C++ code found here...

https://forum.arducam.com/t/how-to-use-code-to-access-libcamera-c-python/2028

* replaced plane.fd.fd() with plane.fd.get() to get it to compile.
* now with Makefile rather than cmake.

Resolutions 640x480 up to 2028x1520 run at 41 FPS.

Some resolution variations around 1920x1080 run at 51 FPS!

Anything above 2028x1520 runs at 11 FPS.

Many of the modes show skew when viewed using OpenCV, so somewhere a stride is being ignored.

# Getting Started
git clone https://github.com/atalkingegg/simpler-vid.git

cd simpler-vid

make

arducam-demo

nocv-demo
