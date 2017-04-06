#include "template_matcher.h"
#include "../helpers/color_generator.h"

namespace BiosOpenCV {

  TemplateMatcher::TemplateMatcher(const cv::Mat& templateImage, double threshold)
    : templateImage(templateImage) {
      this->threshold = threshold;
      isMatchFound = false;
  }

  void TemplateMatcher::match(const cv::Mat& frame) {
    cv::Mat result(frame.rows-templateImage.rows+1, frame.cols-templateImage.cols+1, CV_32FC1);

    cv::matchTemplate(frame, templateImage, result, cv::TM_CCOEFF_NORMED);

    double minVal; double maxVal; cv::Point minLoc; cv::Point maxLoc;
    cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());

    isMatchFound = (maxVal >= threshold);
    matchLocation = maxLoc;

  #if defined(SHOW_DEBUG)
    std::cout << "Match score: " << maxVal << std::endl;
  #endif
  }

  bool TemplateMatcher::is_match_found(void) {
    return isMatchFound;
  }

  void TemplateMatcher::draw(cv::Mat& frame) {
    if (isMatchFound) {
      cv::rectangle(frame, matchLocation, cv::Point(matchLocation.x + templateImage.cols, matchLocation.y + templateImage.rows), ColorGenerator::yellow(), 2, 8, 0);
    }
  }

  cv::Point TemplateMatcher::get_match_location(void) {
    return matchLocation;
  }

  cv::Point TemplateMatcher::get_match_center(void) {
    return matchLocation;
  }
};
