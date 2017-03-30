#pragma once

#include <opencv2/opencv.hpp>

namespace BiosOpenCV {

  class FrameGrabber
  {
    public:
      virtual cv::Mat grab_frame(void) = 0;
  };

};
