//
// Created by zhouhaibo on 2017/9/19.
//

#ifndef FILTERENGINE_DEFAULT_DRAWER_H
#define FILTERENGINE_DEFAULT_DRAWER_H

#include "common/filter_interface.h"

class DefaultDrawer : public FilterInterface {
private:
    ConstString mVertexShader;
    ConstString mFragmentShader;
    GLuint mProgramId;
    GLint mVertexCoords;;
    GLint mTextureCoords;
    GLint mTextureHandle;

    // VAO
    GLuint mVAOId;

public:
    DefaultDrawer();

    ~DefaultDrawer();

    void init();

    void process(GLuint textureId, int width, int height);

    void destroy();
};



#endif //FILTERENGINE_DEFAULT_DRAWER_H
