//
// Created by zhouhaibo on 2017/9/11.
//

#ifndef FILTERENGINE_1977_FLITER_H
#define FILTERENGINE_1977_FLITER_H

#include "filter/base/multi_input_filter.h"

class I1977Filter : public MultiInputFilter {
public:
    I1977Filter();

    ~I1977Filter();

    void init(FilterConfig *filterConfig);

};


#endif //FILTERENGINE_1977_FLITER_H
