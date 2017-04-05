#pragma once

#include "frame_grabber.h"

namespace BiosOpenCV {

  class WebCamera : public FrameGrabber
  {
    private:
      cv::VideoCapture captureDevice;

    public:
      WebCamera(int width=640, int height=480);
      virtual ~WebCamera(void);

    public:
      virtual cv::Mat grab_frame(void);

  };

};
