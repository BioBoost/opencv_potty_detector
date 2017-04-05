#pragma once

#include "types/process_filter.h"
#include "../contour/contour_finder.h"

namespace BiosOpenCV {

  class FindContours : public ProcessFilter {

    private:
      ContourFinder contourFinder;

    public:
      FindContours(const cv::Mat& original, cv::Mat& result, double minimumArea=3000, double maximumArea=15000);

    public:
      virtual void execute(void);

    public:
      std::vector<cv::Point2f> get_centers(void);
  };

};
