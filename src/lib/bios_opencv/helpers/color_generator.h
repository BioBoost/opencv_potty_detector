#pragma once

#include <opencv2/opencv.hpp>

namespace BiosOpenCV {

  class ColorGenerator
  {
    public:
      static cv::Scalar random(void) {
        cv::Scalar color(rand()&255, rand()&255, rand()&255);
        return color;
      }

      static cv::Scalar magenta(void) {
        cv::Scalar color(255, 0, 255);
        return color;
      }

      static cv::Scalar yellow(void) {
        cv::Scalar color(0, 255, 255);
        return color;
      }

      static cv::Scalar lime(void) {
        cv::Scalar color(0, 255, 63);
        return color;
      }

      static cv::Scalar cyan(void) {
        cv::Scalar color(255, 255, 0);
        return color;
      }

      static cv::Scalar white(void) {
        cv::Scalar color(255, 255, 255);
        return color;
      }
  };

};
