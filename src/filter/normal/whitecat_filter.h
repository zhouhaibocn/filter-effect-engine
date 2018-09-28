//
// Created by zhouhaibo on 2017/9/21.
//

#ifndef FILTERENGINE_WHITECAT_FILTER_H
#define FILTERENGINE_WHITECAT_FILTER_H

#include "filter/base/multi_input_filter.h"

class WhitecatFilter : public  MultiInputFilter {

public:
    WhitecatFilter();

    ~WhitecatFilter();

    void init(FilterConfig *filterConfig);

};


#endif //FILTERENGINE_WHITECAT_FILTER_H
