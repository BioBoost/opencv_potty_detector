#include "display.h"

namespace BiosOpenCV {

  Display::Display(const cv::Mat& original, std::string windowTitle)
    : InputFilter(original) {
      this->windowTitle = windowTitle;
  }

  void Display::execute(void) {
    cv::imshow(windowTitle, get_original());
    cv::waitKey(10);
  }

};
