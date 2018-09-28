//
// Created by zhouhaibo on 2017/9/11.
//

#ifndef FILTERENGINE_HUDSON_FILTER_H
#define FILTERENGINE_HUDSON_FILTER_H

#include "filter/base/multi_input_filter.h"

class HudsonFilter : public MultiInputFilter {
public:
    HudsonFilter();

    ~HudsonFilter();

    void init(FilterConfig *filterConfig);

};


#endif //FILTERENGINE_HUDSON_FILTER_H
