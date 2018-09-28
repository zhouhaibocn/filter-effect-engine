//
// Created by zhouhaibo on 2017/9/11.
//

#include "I1977_filter.h"

static ConstString I1977_FSH = GLES_SHADER_STRING_PRECISION_H(
    varying vec2 textureCoordinate;
    uniform sampler2D inputImageTexture;
    uniform sampler2D inputImageTexture1;

    void main() {
        vec3 texel = texture2D(inputImageTexture, textureCoordinate).rgb;
        texel = vec3(texture2D(inputImageTexture1, vec2(texel.r, .16666)).r,
                     texture2D(inputImageTexture1, vec2(texel.g, .5)).g,
                     texture2D(inputImageTexture1, vec2(texel.b, .83333)).b);

        gl_FragColor = vec4(texel, 1.0);
    }
);

I1977Filter::I1977Filter() {

}

I1977Filter::~I1977Filter() {

}

void I1977Filter::init(FilterConfig *filterConfig) {
    mFragmentShader = I1977_FSH;
    MultiInputFilter::init(filterConfig);
}