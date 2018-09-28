//
// Created by zhouhaibo on 2017/9/25.
//

#ifndef FILTERENGINE_SUNRISE_FILTER_H
#define FILTERENGINE_SUNRISE_FILTER_H

#include "filter/base/multi_input_filter.h"

class SunriseFilter : public MultiInputFilter {
public:
    SunriseFilter();

    ~SunriseFilter();

    void init(FilterConfig *filterConfig);
};

#endif //FILTERENGINE_SUNRISE_FILTER_H
