//
// Created by zhouhaibo on 2017/9/11.
//

#ifndef FILTERENGINE_EARLYBIRD_FILTER_H
#define FILTERENGINE_EARLYBIRD_FILTER_H

#include "filter/base/multi_input_filter.h"

class EarlybirdFilter : public MultiInputFilter {
public:
    EarlybirdFilter();

    ~EarlybirdFilter();

    void init(FilterConfig *filterConfig);

};


#endif //FILTERENGINE_EARLYBIRD_FILTER_H
