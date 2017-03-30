#include "grab_frame.h"

namespace BiosOpenCV {

  GrabFrame::GrabFrame(cv::Mat& result, FrameGrabber * frame_grabber)
    : OutputFilter(result) {
    this->frame_grabber = frame_grabber;
  }

  void GrabFrame::execute(void) {
    cv::Mat frame = frame_grabber->grab_frame();
    frame.copyTo(get_result());
  }

};
