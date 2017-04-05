#include "template_matcher.h"
#include "../helpers/color_generator.h"

namespace BiosOpenCV {

  TemplateMatcher::TemplateMatcher(const cv::Mat& templateImage)
    : templateImage(templateImage) {

  }

  void TemplateMatcher::match(const cv::Mat& frame) {
    cv::Mat result;

    int result_cols =  frame.cols - templateImage.cols + 1;
    int result_rows = frame.rows - templateImage.rows + 1;

    result.create(result_rows, result_cols, CV_32FC1);

    cv::matchTemplate(frame, templateImage, result, cv::TM_SQDIFF);       //CV_TM_CCORR_NORMED

    cv::normalize(result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
    double minVal; double maxVal; cv::Point minLoc; cv::Point maxLoc;

    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());
    // if( match_method  == TM_SQDIFF || match_method == TM_SQDIFF_NORMED )
    //   { matchLocation = minLoc; }
    // else
    //   { matchLocation = maxLoc; }
    matchLocation = minLoc;
    std::cout << "Match score: " << minVal << std::endl;
  }

  void TemplateMatcher::draw(cv::Mat& frame) {
    cv::rectangle(frame, matchLocation, cv::Point(matchLocation.x + templateImage.cols, matchLocation.y + templateImage.rows), ColorGenerator::yellow(), 2, 8, 0);
  }

  cv::Point TemplateMatcher::get_match_location(void) {
    return matchLocation;
  }

  cv::Point TemplateMatcher::get_match_center(void) {
    return matchLocation;
  }
};
