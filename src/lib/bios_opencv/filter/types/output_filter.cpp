#include "output_filter.h"

namespace BiosOpenCV {

  OutputFilter::OutputFilter(cv::Mat& result)
    : result(result) {

  }

  cv::Mat& OutputFilter::get_result(void) {
    return result;
  }

};
