//
// Created by zhouhaibo on 2017/9/11.
//

#ifndef FILTERENGINE_AMARO_FILTER_H
#define FILTERENGINE_AMARO_FILTER_H

#include "filter/base/multi_input_filter.h"

class AmaroFilter : public MultiInputFilter {
public:
    AmaroFilter();

    ~AmaroFilter();

    void init(FilterConfig *filterConfig);

};


#endif //FILTERENGINE_AMARO_FILTER_H
