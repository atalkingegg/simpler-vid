#include <iostream>
#include <chrono>
#include <ctime>
#include "LibCamera.h"

#define MAX_FPS 60

int main()
{
    auto start_time = std::chrono::system_clock::now();
    auto end_time = std::chrono::system_clock::now();
    int frame_count = 0;
    int elapsed_milliseconds;
    LibCamera cam;

// 4056x3040, 2048x2048, 2028x2828, 1920x1920 == 10-11 FPS
// 1920x1080, 1920x1280, 2028x1080  == 51 FPS
// 2028x1520, 2028x1440, 1520x1520, 1024x1024, ..., 640x480 = 40-41 FPS

    int width = 2028;
    int height = 1520;

    int ret = cam.initCamera(width, height, formats::RGB888, 4, 0);
    ControlList controls_;
    int64_t frame_time = 1000000 / MAX_FPS;

    controls_.set(libcamera::controls::FrameDurationLimits, { frame_time, frame_time });
    controls_.set(libcamera::controls::Brightness, 0.0); // -1.0 to 1.0
    controls_.set(libcamera::controls::Contrast, 1.0); // 0.0 to 15.99
    controls_.set(libcamera::controls::AnalogueGain, 1.0);
    controls_.set(libcamera::controls::ExposureTime, 40000);
    float rb_gains[] = { 1.2, 1.2 };
    controls_.set(libcamera::controls::ColourGains, rb_gains);

    cam.set(controls_);

    if (!ret)
    {
        bool flag;
        LibcameraOutData frameData;
        cam.startCamera();
        for (;;)
	{
            flag = cam.readFrame(&frameData);
            if (!flag)
                continue;

            frame_count++;
	    end_time = std::chrono::system_clock::now();
	    elapsed_milliseconds = std::chrono::duration_cast<std::chrono::milliseconds> (end_time - start_time).count();
            if (elapsed_milliseconds >= 1000)
	    {
                printf("fps: %d\n", frame_count);
                frame_count = 0;
	        start_time = end_time;
            }
            cam.returnFrameBuffer(frameData);
        }
        cam.stopCamera();
    }
    cam.closeCamera();
    return 0;
}
