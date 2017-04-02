#pragma once

#include "frame_grabber.h"
#include <string>

namespace BiosOpenCV {

  class ImageFile : public FrameGrabber
  {
    private:
      std::string filename;

    public:
      ImageFile(std::string filename);

    public:
      virtual cv::Mat grab_frame(void);

  };

};
