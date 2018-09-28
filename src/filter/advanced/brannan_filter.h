//
// Created by zhouhaibo on 2017/9/11.
//

#ifndef FILTERENGINE_BRANNAN_FILTER_H
#define FILTERENGINE_BRANNAN_FILTER_H

#include "filter/base/multi_input_filter.h"

class BrannanFilter : public MultiInputFilter {
public:
    BrannanFilter();

    ~BrannanFilter();

    void init(FilterConfig *filterConfig);
};

#endif //FILTERENGINE_BRANNAN_FILTER_H
