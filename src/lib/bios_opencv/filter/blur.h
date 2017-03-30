#pragma once

#include "types/process_filter.h"

namespace BiosOpenCV {

  class Blur : public ProcessFilter {

    private:
      int kernelSize;

    public:
      Blur(const cv::Mat& original, cv::Mat& result, int kernelSize=5);
      Blur(cv::Mat& image, int kernelSize=5);

    public:
      virtual void execute(void);
  };

};
