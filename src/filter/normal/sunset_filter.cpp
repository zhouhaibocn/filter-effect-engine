//
// Created by zhouhaibo on 2017/9/25.
//

#include "sunset_filter.h"


static ConstString Sunset_FSH = GLES_SHADER_STRING_PRECISION_H(
        varying vec2 textureCoordinate;
        uniform sampler2D inputImageTexture;
        uniform sampler2D inputImageTexture1;
        uniform sampler2D inputImageTexture2;
        uniform sampler2D inputImageTexture3;

        void main()
        {
            float GreyVal;
            lowp vec4 textureColor;
            lowp vec4 textureColorOri;
            float xCoordinate = textureCoordinate.x;
            float yCoordinate = textureCoordinate.y;

            highp float redCurveValue;
            highp float greenCurveValue;
            highp float blueCurveValue;

            vec4 grey1Color;
            vec4 grey2Color;

            textureColor = texture2D( inputImageTexture, vec2(xCoordinate, yCoordinate));
            grey1Color = texture2D(inputImageTexture3, vec2(xCoordinate, yCoordinate));
            grey2Color = texture2D(inputImageTexture2, vec2(xCoordinate, yCoordinate));

            // step1 normal blending with original
            redCurveValue = texture2D(inputImageTexture1, vec2(textureColor.r, 0.0)).r;
            greenCurveValue = texture2D(inputImageTexture1, vec2(textureColor.g, 0.0)).g;
            blueCurveValue = texture2D(inputImageTexture1, vec2(textureColor.b, 0.0)).b;

            textureColorOri = vec4(redCurveValue, greenCurveValue, blueCurveValue, 1.0);
            textureColor = (textureColorOri - textureColor) * grey1Color.r + textureColor;

            redCurveValue = texture2D(inputImageTexture1, vec2(textureColor.r, 0.0)).a;
            greenCurveValue = texture2D(inputImageTexture1, vec2(textureColor.g, 0.0)).a;
            blueCurveValue = texture2D(inputImageTexture1, vec2(textureColor.b, 0.0)).a;

            //textureColor = vec4(redCurveValue, greenCurveValue, blueCurveValue, 1.0);

            // step3 60% opacity  ExclusionBlending
            textureColor = vec4(redCurveValue, greenCurveValue, blueCurveValue, 1.0);
            mediump vec4 textureColor2 = vec4(0.08627, 0.03529, 0.15294, 1.0);
            textureColor2 = textureColor + textureColor2 - (2.0 * textureColor2 * textureColor);

            textureColor = (textureColor2 - textureColor) * 0.6784 + textureColor;


            mediump vec4 overlay = vec4(0.6431, 0.5882, 0.5803, 1.0);
            mediump vec4 base = textureColor;

            // overlay blending
            mediump float ra;
            if (base.r < 0.5) {
                ra = overlay.r * base.r * 2.0;
            } else {
                ra = 1.0 - ((1.0 - base.r) * (1.0 - overlay.r) * 2.0);
            }

            mediump float ga;
            if (base.g < 0.5) {
                ga = overlay.g * base.g * 2.0;
            } else {
                ga = 1.0 - ((1.0 - base.g) * (1.0 - overlay.g) * 2.0);
            }

            mediump float ba;
            if (base.b < 0.5) {
                ba = overlay.b * base.b * 2.0;
            } else {
                ba = 1.0 - ((1.0 - base.b) * (1.0 - overlay.b) * 2.0);
            }

            textureColor = vec4(ra, ga, ba, 1.0);
            base = (textureColor - base) + base;

            // again overlay blending
            overlay = vec4(0.0, 0.0, 0.0, 1.0);

            // overlay blending
            if (base.r < 0.5) {
                ra = overlay.r * base.r * 2.0;
            } else {
                ra = 1.0 - ((1.0 - base.r) * (1.0 - overlay.r) * 2.0);
            }

            if (base.g < 0.5) {
                ga = overlay.g * base.g * 2.0;
            } else {
                ga = 1.0 - ((1.0 - base.g) * (1.0 - overlay.g) * 2.0);
            }

            if (base.b < 0.5) {
                ba = overlay.b * base.b * 2.0;
            } else {
                ba = 1.0 - ((1.0 - base.b) * (1.0 - overlay.b) * 2.0);
            }

            textureColor = vec4(ra, ga, ba, 1.0);
            textureColor = (textureColor - base) * (grey2Color * 0.549) + base;

            gl_FragColor = vec4(textureColor.r, textureColor.g, textureColor.b, 1.0);
        }
);

SunsetFilter::SunsetFilter() {

}

SunsetFilter::~SunsetFilter() {

}

void SunsetFilter::init(FilterConfig *filterConfig) {
    mFragmentShader = Sunset_FSH;
    MultiInputFilter::init(filterConfig);
}