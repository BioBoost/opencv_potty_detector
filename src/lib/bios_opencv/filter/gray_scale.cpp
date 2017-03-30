#include "gray_scale.h"

namespace BiosOpenCV {

  GrayScale::GrayScale(const cv::Mat& original, cv::Mat& result)
    : ProcessFilter(original, result) {

  }

  GrayScale::GrayScale(cv::Mat& image)
    : GrayScale(image, image) {
  }

  void GrayScale::execute(void) {
    cv::cvtColor(get_original(), get_result(), cv::COLOR_BGR2GRAY);
  }

};
