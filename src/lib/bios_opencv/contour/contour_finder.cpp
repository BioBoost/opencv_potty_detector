#include "contour_finder.h"
#include "../comparators/compare_contour_area.h"
#include "../helpers/color_generator.h"

namespace BiosOpenCV {

  ContourFinder::ContourFinder(double minimumArea, double maximumArea) {
    this->minimumArea = minimumArea;
    this->maximumArea = maximumArea;
  }

  void ContourFinder::find(const cv::Mat& frame) {
    cv::Mat processFrame;
    frame.copyTo(processFrame);

    std::vector<std::vector<cv::Point>> allContours;
    std::vector<cv::Vec4i> allHierarchies;

    cv::findContours(processFrame, allContours, allHierarchies, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    std::cout << "Found total contours: " << allContours.size() << std::endl;
    filter_by_size(&allContours, &allHierarchies);
    determine_centers();
    std::cout << "Remaining contours after filtering: " << contours.size() << std::endl;
    print_areas();
  }

  void ContourFinder::filter_by_size(std::vector<std::vector<cv::Point>> * allContours,
    std::vector<cv::Vec4i> * allHierarchies) {

    std::vector<size_t> indicesOfContoursTokeep;
    std::vector<double> areasOfContoursToKeep;

    for (size_t i = 0; i < allContours->size(); i++) {
      double area = cv::contourArea(cv::Mat((*allContours)[i]));
      std::cout << "Area = " << area;
      if (area <= maximumArea && area >= minimumArea) {
        std::cout << " <= kept" << std::endl;
        indicesOfContoursTokeep.push_back(i);
        areasOfContoursToKeep.push_back(area);
      } else {
          std::cout << " <= ditched" << std::endl;
      }
    }

    // Sort by size
    if (indicesOfContoursTokeep.size() > 1) {
      std::sort(indicesOfContoursTokeep.begin(), indicesOfContoursTokeep.end(),
        CompareContourArea(areasOfContoursToKeep));
    }

    contours.clear();
    hierarchy.clear();
    boundingRectangles.clear();

    for (size_t i = 0; i < indicesOfContoursTokeep.size(); i++) {
      contours.push_back((*allContours)[indicesOfContoursTokeep[i]]);
      hierarchy.push_back((*allHierarchies)[indicesOfContoursTokeep[i]]);
      boundingRectangles.push_back(cv::boundingRect(contours[i]));
    }
  }

  void ContourFinder::draw_bounding_rectangles(cv::Mat& frame) {
    for (size_t i = 0; i < boundingRectangles.size(); i++) {
      int thickness = 1;
      cv::rectangle(frame, boundingRectangles[i], ColorGenerator::magenta(), thickness);
    }
  }

  void ContourFinder::draw_blobs(cv::Mat& frame) {
    int thickness = -1;     // Negative draws them filled
    for(size_t i = 0; i < contours.size(); i++) {
      cv::drawContours(frame, contours, i, ColorGenerator::white(), thickness, 8, hierarchy);
    }
  }

  void ContourFinder::draw_indices(cv::Mat& frame) {
    char buffer[5];
    double scale = 0.5;
    for(size_t i = 0; i < contours.size(); i++) {
      sprintf(buffer, "%zu", i);
      cv::putText(frame, buffer, centers[i], cv::FONT_HERSHEY_PLAIN, scale, ColorGenerator::cyan(), 1);
    }
  }

  void ContourFinder::determine_centers(void) {
      // Moments
      std::vector<cv::Moments> contourMoments(contours.size());
      for (size_t i = 0; i < contours.size(); i++) {
        contourMoments[i] = cv::moments(contours[i], false);
      }

      // Mass centers
      centers.clear();
      for (size_t i = 0; i < contours.size(); i++) {
        centers.push_back(cv::Point2f(contourMoments[i].m10/contourMoments[i].m00,
          contourMoments[i].m01/contourMoments[i].m00));
      }
  }

  void ContourFinder::print_areas(void) {
    for (size_t i = 0; i < contours.size(); i++) {
      double area = cv::contourArea(cv::Mat(contours[i]));
      std::cout << "Area [" << i << "] = " << area << " pixels" << std::endl;
    }
  }

};
