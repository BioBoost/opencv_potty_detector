#pragma once

#include "types/process_filter.h"

namespace BiosOpenCV {

  enum FlipDirection { HORIZONTAL = 0, VERTICAL = 1, BOTH = -1 };

  class Flip : public ProcessFilter {

    private:
      FlipDirection direction;

    public:
      Flip(const cv::Mat& original, cv::Mat& result, FlipDirection direction=HORIZONTAL);
      Flip(cv::Mat& image, FlipDirection direction=HORIZONTAL);

    public:
      virtual void execute(void);
  };

};
