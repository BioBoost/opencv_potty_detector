#include "web_camera.h"

namespace BiosOpenCV {

  WebCamera::WebCamera(void)
  {
    if (!captureDevice.open(0)) {
      throw std::exception();
    }
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
