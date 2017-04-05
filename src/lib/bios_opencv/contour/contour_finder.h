#pragma once

#include <opencv2/opencv.hpp>
#include <vector>

namespace BiosOpenCV {

  class ContourFinder {

    private:
      std::vector<std::vector<cv::Point>> contours;
      std::vector<cv::Vec4i> hierarchy;
      std::vector<cv::Rect> boundingRectangles;
      std::vector<cv::Point2f> centers;

      double minimumArea;
      double maximumArea;
      bool drawBoundingRectangles;
      bool drawIndices;

    public:
      ContourFinder(double minimumArea, double maximumArea);

    public:
      void find(const cv::Mat& frame);
      void draw_bounding_rectangles(cv::Mat& frame);
      void draw_blobs(cv::Mat& frame);
      void draw_indices(cv::Mat& frame);

    private:
      void filter_by_size(std::vector<std::vector<cv::Point>> * allContours, std::vector<cv::Vec4i> * allHierarchies);
      void determine_centers(void);
      void print_areas(void);

    public:
      std::vector<cv::Point2f> get_centers(void);
  };

};
