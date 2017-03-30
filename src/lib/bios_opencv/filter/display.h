#pragma once

#include "types/input_filter.h"

namespace BiosOpenCV {

  class Display : public InputFilter {

    private:
      std::string windowTitle;

    public:
      Display(const cv::Mat& original, std::string windowTitle);

    public:
      virtual void execute(void);
  };

};
