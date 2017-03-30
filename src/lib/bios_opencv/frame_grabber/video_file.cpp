#include "video_file.h"

namespace BiosOpenCV {

  VideoFile::VideoFile(std::string filename)
  {
    if (!videoFile.open(cv::String(filename.c_str()))) {
      throw std::exception();
    }
  }

  VideoFile::~VideoFile(void) {
    videoFile.release();
  }

  cv::Mat VideoFile::grab_frame(void) {
    cv::Mat frame;
    videoFile >> frame;
    return frame;
  }

};
