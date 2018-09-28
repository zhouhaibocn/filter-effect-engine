//
// Created by zhouhaibo on 2017/9/11.
//

#ifndef FILTERENGINE_TOASTER_FILTER_H
#define FILTERENGINE_TOASTER_FILTER_H

#include "filter/base/multi_input_filter.h"

class ToasterFilter : public MultiInputFilter {
public:
    ToasterFilter();

    ~ToasterFilter();

    void init(FilterConfig *filterConfig);

};


#endif //FILTERENGINE_TOASTER_FILTER_H
