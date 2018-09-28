//
// Created by zhouhaibo on 2017/9/11.
//

#ifndef FILTERENGINE_RISE_FILTER_H
#define FILTERENGINE_RISE_FILTER_H

#include "filter/base/multi_input_filter.h"

class RiseFilter : public MultiInputFilter {
public:
    RiseFilter();

    ~RiseFilter();

    void init(FilterConfig *filterConfig);

};


#endif //FILTERENGINE_RISE_FILTER_H
