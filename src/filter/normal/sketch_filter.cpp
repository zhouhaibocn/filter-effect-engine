//
// Created by zhouhaibo on 2017/9/25.
//

#include "sketch_filter.h"

static ConstString Sketch_FSH = GLES_SHADER_STRING_PRECISION_H(
        varying vec2 textureCoordinate;
        uniform sampler2D inputImageTexture;

        uniform float texelWidthOffset;
        uniform float texelHeightOffset;

        const float strength = 0.5;

        const highp vec3 W = vec3(0.299,0.587,0.114);


        void main()
        {
            float threshold = 0.0;
            //pic1
            vec4 oralColor = texture2D(inputImageTexture, textureCoordinate);

            vec2 singleStepOffset = vec2(texelWidthOffset, texelHeightOffset);

            //pic2
            vec3 maxValue = vec3(0.,0.,0.);

            for(int i = -2; i<=2; i++)
            {
                for(int j = -2; j<=2; j++)
                {
                    vec4 tempColor = texture2D(inputImageTexture, textureCoordinate+singleStepOffset*vec2(i,j));
                    maxValue.r = max(maxValue.r,tempColor.r);
                    maxValue.g = max(maxValue.g,tempColor.g);
                    maxValue.b = max(maxValue.b,tempColor.b);
                    threshold += dot(tempColor.rgb, W);
                }
            }
            //pic3
            float gray1 = dot(oralColor.rgb, W);

            //pic4
            float gray2 = dot(maxValue, W);

            //pic5
            float contour = gray1 / gray2;

            threshold = threshold / 25.;
            float alpha = max(1.0,gray1>threshold?1.0:(gray1/threshold));

            float result = contour * alpha + (1.0-alpha)*gray1;

            gl_FragColor = vec4(vec3(result,result,result), oralColor.w);
        }
);

SketchFilter::SketchFilter() {
    mWidthOffsetHandle = -1;
    mHeightOffsetHandle = -1;


}

SketchFilter::~SketchFilter() {

}

void SketchFilter::init(FilterConfig *filterConfig) {
    mFragmentShader = Sketch_FSH;
    MultiInputFilter::init(filterConfig);

    mWidthOffsetHandle = glGetUniformLocation(mProgramId, "texelWidthOffset");
    mHeightOffsetHandle = glGetUniformLocation(mProgramId, "texelHeightOffset");
}

void SketchFilter::process(GLuint textureId, int width, int height) {
    internalPreProcess(textureId);

    glUniform1f(mWidthOffsetHandle, 1.0f / width);
    glUniform1f(mHeightOffsetHandle, 1.0f / height);

    internalDraw(width, height);
}