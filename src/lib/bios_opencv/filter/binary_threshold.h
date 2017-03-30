#pragma once

#include "types/process_filter.h"

namespace BiosOpenCV {

  class BinaryThreshold : public ProcessFilter {

    private:
      static const int OUTPUT_VALUE = 255;

    private:
      int threshold;

    public:
      BinaryThreshold(const cv::Mat& original, cv::Mat& result, int threshold=200);
      BinaryThreshold(cv::Mat& image, int threshold=200);

    public:
      virtual void execute(void);
  };

};
