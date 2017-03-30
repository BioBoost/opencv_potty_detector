#pragma once

#include "types/output_filter.h"
#include "../frame_grabber/frame_grabber.h"

namespace BiosOpenCV {

  class GrabFrame : public OutputFilter {
    private:
      FrameGrabber * frame_grabber;

    public:
      GrabFrame(cv::Mat& result, FrameGrabber * frame_grabber);

    public:
      virtual void execute(void);
  };

};
