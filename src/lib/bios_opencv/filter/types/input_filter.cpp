#include "input_filter.h"

namespace BiosOpenCV {

  InputFilter::InputFilter(const cv::Mat& original)
    : original(original) {

  }

  const cv::Mat& InputFilter::get_original(void) {
    return original;
  }

};
