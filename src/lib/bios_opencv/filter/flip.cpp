#include "flip.h"

namespace BiosOpenCV {

  Flip::Flip(const cv::Mat& original, cv::Mat& result, FlipDirection direction)
    : ProcessFilter(original, result) {

    this->direction = direction;
  }

  Flip::Flip(cv::Mat& image, FlipDirection direction)
    : Flip(image, image, direction) {
  }

  void Flip::execute(void) {
    cv::flip(get_original(), get_result(), direction);
  }

};
;
