//
// Created by zhouhaibo on 2017/9/20.
//

#ifndef FILTERENGINE_MULTI_INPUT_FILTER_H
#define FILTERENGINE_MULTI_INPUT_FILTER_H

#include "common/filter_interface.h"
#include "utils/parse_config.h"

//enum MultiInputTypes {
//    One_Input_Type,
//    Two_Input_Type,
//    Three_Input_Type,
//    Four_Input_Type,
//    Five_Input_Type,
//    Six_Input_Type
//};

class MultiInputFilter : public FilterInterface {
protected:
    bool mIsInitialized;
    ConstString mVertexShader;
    ConstString mFragmentShader;
    GLuint mProgramId;
    GLint mVertexCoords;;
    GLint mTextureCoords;
    GLint mTextureHandle;

    int mInputImageNum;
    GLint *mInputImageHandle;
    GLuint *mInputTexture;

    // for test
//    unsigned char * rgbaBuf;
//    int mLength;

public:

    MultiInputFilter();

    virtual ~MultiInputFilter();

    virtual void init(FilterConfig *filterConfig);

    virtual void process(GLuint textureId, int width, int height);

    virtual void destroy();

//    // for test
//    virtual void getResult(unsigned char *buffer);

protected:
    void internalPreProcess(GLuint textureId);

    void internalDraw(int width, int height);
};


#endif //FILTERENGINE_MULTI_INPUT_FILTER_H
