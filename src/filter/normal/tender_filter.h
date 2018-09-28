//
// Created by zhouhaibo on 2017/9/25.
//

#ifndef FILTERENGINE_TENDER_FILTER_H
#define FILTERENGINE_TENDER_FILTER_H

#include "filter/base/multi_input_filter.h"

class TenderFilter : public  MultiInputFilter {

public:
    TenderFilter();

    ~TenderFilter();

    void init(FilterConfig *filterConfig);

};

#endif //FILTERENGINE_TENDER_FILTER_H
