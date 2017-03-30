#include "process_filter.h"

namespace BiosOpenCV {

  ProcessFilter::ProcessFilter(const cv::Mat& original, cv::Mat& result)
    : original(original), result(result) {

  }

  const cv::Mat& ProcessFilter::get_original(void) {
    return original;
  }

  cv::Mat& ProcessFilter::get_result(void) {
    return result;
  }

};
