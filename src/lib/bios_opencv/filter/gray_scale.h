#pragma once

#include "types/process_filter.h"

namespace BiosOpenCV {

  class GrayScale : public ProcessFilter {

    public:
      GrayScale(const cv::Mat& original, cv::Mat& result);
      GrayScale(cv::Mat& image);

    public:
      virtual void execute(void);
  };

};
