#include "match_template.h"

namespace BiosOpenCV {

  MatchTemplate::MatchTemplate(const cv::Mat& original, cv::Mat& result, const cv::Mat& templateImage)
    : ProcessFilter(original, result), templateMatcher(templateImage) {

  }

  MatchTemplate::MatchTemplate(cv::Mat& image, const cv::Mat& templateImage)
    : MatchTemplate(image, image, templateImage) {
  }

  void MatchTemplate::execute(void) {

    templateMatcher.match(get_original());

    if (get_result().empty()) {
      throw std::runtime_error("Result frame of match template should not be empty");
    }

    templateMatcher.draw(get_result());
  }

};
