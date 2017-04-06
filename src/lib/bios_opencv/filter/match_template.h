#pragma once

#include "types/process_filter.h"
#include "../template/template_matcher.h"

namespace BiosOpenCV {

  class MatchTemplate : public ProcessFilter {

    private:
      TemplateMatcher templateMatcher;

    public:
      MatchTemplate(const cv::Mat& original, cv::Mat& result, const cv::Mat& templateImage, double threshold=0.75);
      MatchTemplate(cv::Mat& image, const cv::Mat& templateImage, double threshold=0.75);

    public:
      virtual void execute(void);

    public:
      cv::Point get_match_center(void);
      bool is_match_found(void);
  };

};
