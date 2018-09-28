//
// Created by zhouhaibo on 2017/9/21.
//

#ifndef FILTERENGINE_CONFIG_H
#define FILTERENGINE_CONFIG_H

#include "common/common.h"

typedef enum {
    Type_None,
    Type_Bin_Data,
    Type_Png_Data
} FilterDataType;

typedef struct {
    FilterDataType type;
    char name[1024];
} FilterData;

typedef struct  {
    uint8_t type;
    uint8_t num;
    FilterData *data;
} FilterConfig;

void parsingFilterConfig(ConstString filterZipPath, FilterConfig *filterConfig);


#endif //FILTERENGINE_CONFIG_H
