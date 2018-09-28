//
// Created by zhouhaibo on 2017/9/25.
//

#include "nostalgia_filter.h"


static ConstString Nostalgia_FSH = GLES_SHADER_STRING_PRECISION_H(
        varying vec2 textureCoordinate;
        uniform sampler2D inputImageTexture;
        uniform sampler2D inputImageTexture1;
        uniform sampler2D inputImageTexture2;

        uniform float texelWidthOffset;
        uniform float texelHeightOffset;

        const float blurSize = 1.0;

        vec4 OverlayBlendingVec4(vec4 down, vec4 up, float fAlpha)
        {
            if ( down.r < 0.5 )
            {
                up.r = up.r * down.r * 2.0;
            }
            else
            {
                up.r = 1.0 - ( ( 1.0 - down.r) * ( 1.0 - up.r ) * 2.0 );
            }
            if ( down.g < 0.5 )
            {
                up.g = up.g * down.g * 2.0;
            }
            else
            {
                up.g = 1.0 - ( ( 1.0 - down.g) * ( 1.0 - up.g ) * 2.0 );
            }

            if ( down.b < 0.5 )
            {
                up.b = up.b * down.b * 2.0;
            }
            else
            {
                up.b = 1.0 - ( ( 1.0 - down.b) * ( 1.0 - up.b ) * 2.0 );
            }

            down = ( up - down ) * fAlpha + down;

            return down;
        }

        void main()
        {
            float xCoordinate = textureCoordinate.x;
            float yCoordinate = textureCoordinate.y;

            vec4 textureColor = texture2D( inputImageTexture, vec2(xCoordinate, yCoordinate));
            highp vec2 firstOffset = vec2(1.3846153846 * texelWidthOffset, 1.3846153846 * texelHeightOffset) * blurSize;
            highp vec2 secondOffset = vec2(3.2307692308 * texelWidthOffset, 3.2307692308 * texelHeightOffset) * blurSize;

            highp vec2 centerTextureCoordinate = vec2(xCoordinate, yCoordinate);
            highp vec2 oneStepLeftTextureCoordinate = vec2(xCoordinate, yCoordinate) - firstOffset;
            highp vec2 twoStepsLeftTextureCoordinate = vec2(xCoordinate, yCoordinate) - secondOffset;
            highp vec2 oneStepRightTextureCoordinate = vec2(xCoordinate, yCoordinate) + firstOffset;
            highp vec2 twoStepsRightTextureCoordinate = vec2(xCoordinate, yCoordinate) + secondOffset;

            lowp vec4 fragmentColor = texture2D(inputImageTexture, vec2(centerTextureCoordinate.x, centerTextureCoordinate.y)) * 0.2270270270;
            fragmentColor += texture2D(inputImageTexture, vec2(oneStepLeftTextureCoordinate.x, oneStepLeftTextureCoordinate.y)) * 0.3162162162;
            fragmentColor += texture2D(inputImageTexture, vec2(oneStepRightTextureCoordinate.x, oneStepRightTextureCoordinate.y)) * 0.3162162162;
            fragmentColor += texture2D(inputImageTexture, vec2(twoStepsLeftTextureCoordinate.x, twoStepsLeftTextureCoordinate.y)) * 0.0702702703;
            fragmentColor += texture2D(inputImageTexture, vec2(twoStepsRightTextureCoordinate.x, twoStepsRightTextureCoordinate.y)) * 0.0702702703;

            lowp vec4 blurColor = fragmentColor;

            // step1 ScreenBlending
            blurColor = 1.0 - ((1.0 - textureColor) * (1.0 - blurColor));
            blurColor =     clamp(blurColor, 0.0, 1.0);
            textureColor = (blurColor - textureColor) * 0.7 + textureColor;
            textureColor =  clamp(textureColor, 0.0, 1.0);

            // step2 OverlayBlending
            textureColor = OverlayBlendingVec4(textureColor, vec4(0.0, 0.0, 0.0, 1.0), 0.3);
            textureColor = clamp(textureColor, vec4(0.0, 0.0, 0.0, 1.0), vec4(1.0, 1.0, 1.0, 1.0));

            // step3 curve
            highp float redCurveValue = texture2D(inputImageTexture1, vec2(textureColor.r, 0.0)).r;
            highp float greenCurveValue = texture2D(inputImageTexture1, vec2(textureColor.g, 0.0)).g;
            highp float blueCurveValue = texture2D(inputImageTexture1, vec2(textureColor.b, 0.0)).b;

            // step4 curve
            redCurveValue = texture2D(inputImageTexture1, vec2(redCurveValue, 1.0)).r;
            greenCurveValue = texture2D(inputImageTexture1, vec2(greenCurveValue, 1.0)).r;
            blueCurveValue = texture2D(inputImageTexture1, vec2(blueCurveValue, 1.0)).r;

            // step5 level
            redCurveValue = texture2D(inputImageTexture1, vec2(redCurveValue, 1.0)).g;
            greenCurveValue = texture2D(inputImageTexture1, vec2(greenCurveValue, 1.0)).g;
            blueCurveValue = texture2D(inputImageTexture1, vec2(blueCurveValue, 1.0)).g;

            // step6 curve
            redCurveValue = texture2D(inputImageTexture2, vec2(redCurveValue, 1.0)).r;
            greenCurveValue = texture2D(inputImageTexture2, vec2(greenCurveValue, 1.0)).g;
            blueCurveValue = texture2D(inputImageTexture2, vec2(blueCurveValue, 1.0)).b;

            // step7 curve
            redCurveValue = texture2D(inputImageTexture1, vec2(redCurveValue, 1.0)).b;
            greenCurveValue = texture2D(inputImageTexture1, vec2(greenCurveValue, 1.0)).b;

            blueCurveValue = texture2D(inputImageTexture1, vec2(blueCurveValue, 1.0)).b;

            lowp vec4 BCSColor = vec4(redCurveValue, greenCurveValue, blueCurveValue, 1.0);
            gl_FragColor =  vec4(BCSColor.r,BCSColor.g,BCSColor.b,1.0);
        }
);

NostalgiaFilter::NostalgiaFilter() {
    mWidthOffsetHandle = -1;
    mHeightOffsetHandle = -1;


}

NostalgiaFilter::~NostalgiaFilter() {

}

void NostalgiaFilter::init(FilterConfig *filterConfig) {
    mFragmentShader = Nostalgia_FSH;
    MultiInputFilter::init(filterConfig);

    mWidthOffsetHandle = glGetUniformLocation(mProgramId, "texelWidthOffset");
    mHeightOffsetHandle = glGetUniformLocation(mProgramId, "texelHeightOffset");
}

void NostalgiaFilter::process(GLuint textureId, int width, int height) {
    internalPreProcess(textureId);

    glUniform1f(mWidthOffsetHandle, 1.0f / width);
    glUniform1f(mHeightOffsetHandle, 1.0f / height);

    internalDraw(width, height);
}