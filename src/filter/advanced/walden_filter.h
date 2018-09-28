//
// Created by zhouhaibo on 2017/9/11.
//

#ifndef FILTERENGINE_WALDEN_FILTER_H
#define FILTERENGINE_WALDEN_FILTER_H

#include "filter/base/multi_input_filter.h"

class WaldenFilter : public MultiInputFilter {
public:
    WaldenFilter();

    ~WaldenFilter();

    void init(FilterConfig *filterConfig);

};

#endif //FILTERENGINE_WALDEN_FILTER_H
