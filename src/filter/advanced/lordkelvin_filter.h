//
// Created by zhouhaibo on 2017/9/11.
//

#ifndef FILTERENGINE_LORDKELVIN_FILTER_H
#define FILTERENGINE_LORDKELVIN_FILTER_H

#include "filter/base/multi_input_filter.h"

class LordkelvinFilter : public MultiInputFilter {
public:
    LordkelvinFilter();

    ~LordkelvinFilter();

    void init(FilterConfig *filterConfig);

};


#endif //FILTERENGINE_LORDKELVIN_FILTER_H
