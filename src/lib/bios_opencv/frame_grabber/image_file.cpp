#include "image_file.h"

namespace BiosOpenCV {

  ImageFile::ImageFile(std::string filename)
  {
    this->filename = filename;
  }

  cv::Mat ImageFile::grab_frame(void) {
    return cv::imread(cv::String(filename.c_str()));
  }

};
