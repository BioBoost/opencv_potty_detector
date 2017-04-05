#include "web_camera.h"

namespace BiosOpenCV {

  WebCamera::WebCamera(int width, int height)
  {
    if (!captureDevice.open(0)) {
      throw std::exception();
    }

    captureDevice.set(cv::CAP_PROP_FRAME_WIDTH, width);
    captureDevice.set(cv::CAP_PROP_FRAME_HEIGHT, height);
  }

  WebCamera::~WebCamera(void) {
    captureDevice.release();
  }

  cv::Mat WebCamera::grab_frame(void) {
    cv::Mat frame;
    captureDevice >> frame;
    return frame;
  }

};
