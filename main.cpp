#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

#include "LibCamera.h"

using namespace cv;

int main() {
    time_t start_time = time(0);
    int frame_count = 0;
    LibCamera cam;

// 1920x1080 works, 2028x1080 does not.
// 1024x1024 works, 1440x1440 works, 1520x1520 does not, 1264x1264 does not.
// 3040x3040 works, 4056x3040 does not. 800x600 works, 800x800 works.
// 2048x2048 works, 2028x2028 does not.
    int width = 1024;
    int height = 1024;

    char key;
    int ret = cam.initCamera(width, height, formats::RGB888, 4, 0);
    ControlList controls_;
    int64_t frame_time = 1000000 / 30;
	controls_.set(libcamera::controls::FrameDurationLimits, { frame_time, frame_time });
	controls_.set(libcamera::controls::Brightness, 0.0); // -1.0 to 1.0
	controls_.set(libcamera::controls::Contrast, 1.0); // 0.0 to 15.99
	controls_.set(libcamera::controls::AnalogueGain, 1.0);
	controls_.set(libcamera::controls::ExposureTime, 40000);
	float rb_gains[] = { 1.2, 1.2 };
	controls_.set(libcamera::controls::ColourGains, rb_gains);

    cam.set(controls_);

    if (!ret) {
        bool flag;
        LibcameraOutData frameData;
        cam.startCamera();
        for (;;) {
            flag = cam.readFrame(&frameData);
            if (!flag)
                continue;
            Mat im(height, width, CV_8UC3, frameData.imageData);

            imshow("libcamera-demo", im);
            key = waitKey(1);
            if (key == 'q')
                break;

            frame_count++;
            if ((time(0) - start_time) >= 1){
                printf("fps: %d\n", frame_count);
                frame_count = 0;
                start_time = time(0);
            }
            cam.returnFrameBuffer(frameData);
        }
        destroyAllWindows();
        cam.stopCamera();
    }
    cam.closeCamera();
    return 0;
}
