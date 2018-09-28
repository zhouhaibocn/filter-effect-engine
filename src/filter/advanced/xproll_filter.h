//
// Created by zhouhaibo on 2017/9/11.
//

#ifndef FILTERENGINE_XPROLL_FILTER_H
#define FILTERENGINE_XPROLL_FILTER_H

#include "filter/base/multi_input_filter.h"

class XprollFilter : public MultiInputFilter {
public:
    XprollFilter();

    ~XprollFilter();

    void init(FilterConfig *filterConfig);

};

#endif //FILTERENGINE_XPROLL_FILTER_H
