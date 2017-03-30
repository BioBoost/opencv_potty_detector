#include "blur.h"

namespace BiosOpenCV {

  Blur::Blur(const cv::Mat& original, cv::Mat& result, int kernelSize)
    : ProcessFilter(original, result) {

    this->kernelSize = kernelSize;
  }

  Blur::Blur(cv::Mat& image, int kernelSize)
    : Blur(image, image, kernelSize) {
  }

  void Blur::execute(void) {
    cv::blur(get_original(), get_result(), cv::Size(kernelSize, kernelSize));
  }

};
