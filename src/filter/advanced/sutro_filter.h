//
// Created by zhouhaibo on 2017/9/11.
//

#ifndef FILTERENGINE_SUTRO_FILTER_H
#define FILTERENGINE_SUTRO_FILTER_H

#include "filter/base/multi_input_filter.h"

class SutroFilter : public MultiInputFilter {
public:
    SutroFilter();

    ~SutroFilter();

    void init(FilterConfig *filterConfig);

};

#endif //FILTERENGINE_SUTRO_FILTER_H
