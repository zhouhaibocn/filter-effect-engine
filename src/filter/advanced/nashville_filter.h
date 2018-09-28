//
// Created by zhouhaibo on 2017/9/11.
//

#ifndef FILTERENGINE_NASHVILLE_FILTER_H
#define FILTERENGINE_NASHVILLE_FILTER_H

#include "filter/base/multi_input_filter.h"

class NashvilleFilter : public MultiInputFilter {
public:
    NashvilleFilter();

    ~NashvilleFilter();

    void init(FilterConfig *filterConfig);

};

#endif //FILTERENGINE_NASHVILLE_FILTER_H
