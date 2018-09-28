//
// Created by zhouhaibo on 2017/9/25.
//

#include "crayon_filter.h"

static ConstString Crayon_FSH = GLES_SHADER_STRING_PRECISION_H(
        varying vec2 textureCoordinate;
        uniform sampler2D inputImageTexture;

        uniform float texelWidthOffset;
        uniform float texelHeightOffset;

        const float strength = 0.5;

        const vec3 W = vec3(0.299,0.587,0.114);

        const mat3 rgb2yiqMatrix = mat3(
                0.299, 0.587, 0.114,
                0.596,-0.275,-0.321,
                0.212,-0.523, 0.311);

        const mat3 yiq2rgbMatrix = mat3(
                1.0, 0.956, 0.621,
                1.0,-0.272,-1.703,
                1.0,-1.106, 0.0);


        void main()
        {
            vec4 oralColor = texture2D(inputImageTexture, textureCoordinate);

            vec2 singleStepOffset = vec2(texelWidthOffset, texelHeightOffset);

            vec3 maxValue = vec3(0.,0.,0.);

            for(int i = -2; i<=2; i++)
            {
                for(int j = -2; j<=2; j++)
                {
                    vec4 tempColor = texture2D(inputImageTexture, textureCoordinate+singleStepOffset*vec2(i,j));
                    maxValue.r = max(maxValue.r,tempColor.r);
                    maxValue.g = max(maxValue.g,tempColor.g);
                    maxValue.b = max(maxValue.b,tempColor.b);
                }
            }

            vec3 textureColor = oralColor.rgb / maxValue;

            float gray = dot(textureColor, W);
            float k = 0.223529;
            float alpha = min(gray,k)/k;

            textureColor = textureColor * alpha + (1.-alpha)*oralColor.rgb;

            vec3 yiqColor = textureColor * rgb2yiqMatrix;

            yiqColor.r = max(0.0,min(1.0,pow(gray,strength)));

            textureColor = yiqColor * yiq2rgbMatrix;

            gl_FragColor = vec4(textureColor, oralColor.w);
        }
);

CrayonFilter::CrayonFilter() {
    mWidthOffsetHandle = -1;
    mHeightOffsetHandle = -1;


}

CrayonFilter::~CrayonFilter() {

}

void CrayonFilter::init(FilterConfig *filterConfig) {
    mFragmentShader = Crayon_FSH;
    MultiInputFilter::init(filterConfig);

    mWidthOffsetHandle = glGetUniformLocation(mProgramId, "texelWidthOffset");
    mHeightOffsetHandle = glGetUniformLocation(mProgramId, "texelHeightOffset");
}

void CrayonFilter::process(GLuint textureId, int width, int height) {
    internalPreProcess(textureId);

    glUniform1f(mWidthOffsetHandle, 1.0f / width);
    glUniform1f(mHeightOffsetHandle, 1.0f / height);

    internalDraw(width, height);
}