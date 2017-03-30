#pragma once

#include <opencv2/opencv.hpp>

namespace BiosOpenCV {

  class Filter {

    public:
      virtual ~Filter(void);

    public:
      virtual void execute(void) = 0;

  };

};
