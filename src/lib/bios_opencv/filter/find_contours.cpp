#include "find_contours.h"
#include <string>

namespace BiosOpenCV {

  FindContours::FindContours(const cv::Mat& original, cv::Mat& result, double minimumArea, double maximumArea)
    : ProcessFilter(original, result), contourFinder(minimumArea, maximumArea) {

  }

  void FindContours::execute(void) {
    contourFinder.find(get_original());

    if (get_result().empty()) {
      throw std::runtime_error("Result frame of find contours should not be empty");
    }

    contourFinder.draw_bounding_rectangles(get_result());
    contourFinder.draw_blobs(get_result());
    contourFinder.draw_indices(get_result());
  }

  std::vector<cv::Point2f> FindContours::get_centers(void) {
    return contourFinder.get_centers();
  }

};
