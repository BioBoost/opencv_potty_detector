#pragma once

#include "input_filter.h"
#include "output_filter.h"

namespace BiosOpenCV {

  class ProcessFilter : public Filter {

    private:
      const cv::Mat& original;
      cv::Mat& result;

    public:
      ProcessFilter(const cv::Mat& original, cv::Mat& result);

    public:
      virtual void execute(void) = 0;

    public:
      const cv::Mat& get_original(void);
      cv::Mat& get_result(void);

  };

};
