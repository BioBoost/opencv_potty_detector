#pragma once

#include <opencv2/opencv.hpp>

namespace BiosOpenCV {

  class TemplateMatcher {

    private:
      const cv::Mat& templateImage;
      cv::Point matchLocation;

    public:
      TemplateMatcher(const cv::Mat& templateImage);

    public:
      void match(const cv::Mat& frame);
      void draw(cv::Mat& frame);

    public:
      cv::Point get_match_location(void);
      cv::Point get_match_center(void);

  };

};
