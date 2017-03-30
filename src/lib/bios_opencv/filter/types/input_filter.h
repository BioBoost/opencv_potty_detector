#pragma once

#include "filter.h"

namespace BiosOpenCV {

  class InputFilter : public Filter {

    private:
      const cv::Mat& original;

    public:
      InputFilter(const cv::Mat& original);

    public:
      virtual void execute(void) = 0;

    public:
      const cv::Mat& get_original(void);

  };

};
