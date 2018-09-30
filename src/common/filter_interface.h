//
// Created by zhouhaibo on 2017/9/11.
//

#ifndef FILTERENGINE_FILTER_INTERFACE_H
#define FILTERENGINE_FILTER_INTERFACE_H

#include "common.h"
#include "utils/gl_utils.h"

class FilterInterface {

public:
    FilterInterface();

    virtual ~FilterInterface();

    virtual void init();

    virtual void setParam(float params);

    virtual void process(GLuint textureId, int width, int height) = 0;

    virtual void destroy();
};


#endif //FILTERENGINE_FILTER_INTERFACE_H
