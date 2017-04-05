#pragma once

#include "frame_grabber.h"

namespace BiosOpenCV {

  class WebCamera : public FrameGrabber
  {
    private:
      cv::VideoCapture captureDevice;

    public:
      WebCamera(void);
      virtual ~WebCamera(void);

    public:
      virtual cv::Mat grab_frame(void);

  };

};
