#include "binary_threshold.h"

namespace BiosOpenCV {

  BinaryThreshold::BinaryThreshold(const cv::Mat& original, cv::Mat& result, int threshold)
    : ProcessFilter(original, result) {
    this->threshold = threshold;
  }

  BinaryThreshold::BinaryThreshold(cv::Mat& image, int threshold)
    : BinaryThreshold(image, image, threshold) {
  }

  void BinaryThreshold::execute(void) {
    cv::threshold(get_original(), get_result(), threshold, OUTPUT_VALUE, cv::THRESH_BINARY);
  }

};
