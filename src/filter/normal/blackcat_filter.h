//
// Created by zhouhaibo on 2017/9/21.
//

#ifndef FILTERENGINE_BLACKCAT_FILTER_H
#define FILTERENGINE_BLACKCAT_FILTER_H

#include "filter/base/multi_input_filter.h"

class BlackcatFilter : public  MultiInputFilter {

public:
    BlackcatFilter();

    ~BlackcatFilter();

    void init(FilterConfig *filterConfig);

};


#endif //FILTERENGINE_BLACKCAT_FILTER_H
