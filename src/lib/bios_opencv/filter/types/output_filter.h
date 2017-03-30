#pragma once

#include "filter.h"

namespace BiosOpenCV {

  class OutputFilter : public Filter {

    private:
      cv::Mat& result;

    public:
      OutputFilter(cv::Mat& result);

    public:
      virtual void execute(void) = 0;

    public:
      cv::Mat& get_result(void);

  };

};
