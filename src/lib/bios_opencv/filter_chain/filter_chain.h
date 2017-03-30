#pragma once

#include "../filter/types/filter.h"

namespace BiosOpenCV {

  class FilterChain {

    private:
      std::vector<Filter*> filters;

    public:
      ~FilterChain(void);

    public:
      void add(Filter * filter);
      void execute(void);

  };

};
