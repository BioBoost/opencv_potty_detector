#pragma once

#include "types/process_filter.h"

namespace BiosOpenCV {

  class GaussianBlur : public ProcessFilter {
    private:
      int kernelSize;
      int blurFactor;

    public:
      GaussianBlur(const cv::Mat& original, cv::Mat& result, double blurFactor=5, int kernelSize=5);
      GaussianBlur(cv::Mat& image, double blurFactor=5, int kernelSize=5);

    public:
      virtual void execute(void);
  };

};
