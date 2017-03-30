#include "filter_chain.h"

namespace BiosOpenCV {

  FilterChain::~FilterChain(void) {
    for(unsigned int i = 0; i < filters.size(); i++) {
      delete filters[i];
    }
    filters.clear();
  }

  void FilterChain::add(Filter * filter) {
    this->filters.push_back(filter);
  }

  void FilterChain::execute(void) {
    for (unsigned int i = 0; i < filters.size(); i++) {
      filters[i]->execute();
    }
  }

};
