#include "gaussian_blur.h"

namespace BiosOpenCV {

  GaussianBlur::GaussianBlur(const cv::Mat& original, cv::Mat& result, double blurFactor, int kernelSize)
    : ProcessFilter(original, result) {
    this->kernelSize = kernelSize;
    this->blurFactor = blurFactor;
  }

  GaussianBlur::GaussianBlur(cv::Mat& image, double blurFactor, int kernelSize)
    : GaussianBlur(image, image, blurFactor, kernelSize) {
  }

  void GaussianBlur::execute(void) {
    cv::GaussianBlur(get_original(), get_result(), cv::Size(kernelSize, kernelSize), blurFactor, blurFactor);
  }

};
