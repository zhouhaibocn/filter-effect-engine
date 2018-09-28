//
// Created by zhouhaibo on 2017/9/11.
//

#ifndef FILTERENGINE_VALENCIA_FILTER_H
#define FILTERENGINE_VALENCIA_FILTER_H

#include "filter/base/multi_input_filter.h"

class ValenciaFilter : public MultiInputFilter {
public:
    ValenciaFilter();

    ~ValenciaFilter();

    void init(FilterConfig *filterConfig);

};

#endif //FILTERENGINE_VALENCIA_FILTER_H
