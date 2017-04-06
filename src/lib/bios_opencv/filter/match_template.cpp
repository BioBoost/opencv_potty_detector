#include "match_template.h"

namespace BiosOpenCV {

  MatchTemplate::MatchTemplate(const cv::Mat& original, cv::Mat& result, const cv::Mat& templateImage, double threshold)
    : ProcessFilter(original, result), templateMatcher(templateImage, threshold) {

  }

  MatchTemplate::MatchTemplate(cv::Mat& image, const cv::Mat& templateImage, double threshold)
    : MatchTemplate(image, image, templateImage, threshold) {
  }

  void MatchTemplate::execute(void) {

    templateMatcher.match(get_original());

    if (get_result().empty()) {
      throw std::runtime_error("Result frame of match template should not be empty");
    }

    templateMatcher.draw(get_result());
  }

  cv::Point MatchTemplate::get_match_center(void) {
    return templateMatcher.get_match_center();
  }

  bool MatchTemplate::is_match_found(void) {
    return templateMatcher.is_match_found();
  }

};
