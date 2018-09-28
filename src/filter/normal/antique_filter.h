//
// Created by zhouhaibo on 2017/9/21.
//

#ifndef FILTERENGINE_ANTIQUE_FILTER_H
#define FILTERENGINE_ANTIQUE_FILTER_H

#include "filter/base/multi_input_filter.h"

class AntiqueFilter : public MultiInputFilter {

public:
    AntiqueFilter();

    ~AntiqueFilter();

    void init(FilterConfig *filterConfig);
};


#endif //FILTERENGINE_ANTIQUE_FILTER_H
