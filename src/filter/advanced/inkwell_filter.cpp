//
// Created by zhouhaibo on 2017/9/11.
//

#include "inkwell_filter.h"

static ConstString Inkwell_FSH = GLES_SHADER_STRING_PRECISION_H(
    varying vec2 textureCoordinate;
    uniform sampler2D inputImageTexture;
    uniform sampler2D inputImageTexture1;

    void main() {
        vec3 texel = texture2D(inputImageTexture, textureCoordinate).rgb;
        texel = vec3(dot(vec3(0.3, 0.6, 0.1), texel));
        texel = vec3(texture2D(inputImageTexture1, vec2(texel.r, .16666)).r);
        gl_FragColor = vec4(texel, 1.0);
    }
);


InkwellFilter::InkwellFilter() {

}

InkwellFilter::~InkwellFilter() {

}

void InkwellFilter::init(FilterConfig *filterConfig) {
    mFragmentShader = Inkwell_FSH;
    MultiInputFilter::init(filterConfig);
}