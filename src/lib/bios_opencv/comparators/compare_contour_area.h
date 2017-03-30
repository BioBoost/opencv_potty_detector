//Based on: http://stackoverflow.com/questions/1723066/c-stl-custom-sorting-one-vector-based-on-contents-of-another

#pragma once

#include <vector>

namespace BiosOpenCV {

  struct CompareContourArea : std::binary_function<size_t, size_t, bool>
  {
    const std::vector<double> & _areas;

    CompareContourArea(const std::vector<double> & areas)
      : _areas(areas) {
    }

    bool operator()(size_t left, size_t right) const {
      return _areas[left] > _areas[right];
    }

  };

};
