//
// Created by zhouhaibo on 2017/9/11.
//

#ifndef FILTERENGINE_HEFE_FILTER_H
#define FILTERENGINE_HEFE_FILTER_H

#include "filter/base/multi_input_filter.h"

class HefeFilter : public MultiInputFilter {
public:
    HefeFilter();

    ~HefeFilter();

    void init(FilterConfig *filterConfig);

};


#endif //FILTERENGINE_HEFE_FILTER_H
