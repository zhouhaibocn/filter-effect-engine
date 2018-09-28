//
// Created by zhouhaibo on 2017/9/11.
//

#ifndef FILTERENGINE_INKWELL_FILTER_H
#define FILTERENGINE_INKWELL_FILTER_H

#include "filter/base/multi_input_filter.h"

class InkwellFilter : public MultiInputFilter {
public:
    InkwellFilter();

    ~InkwellFilter();

    void init(FilterConfig *filterConfig);

};


#endif //FILTERENGINE_INKWELL_FILTER_H
